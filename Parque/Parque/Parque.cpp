#include "Parque.hpp"

// Construtor
Parque::Parque(string cidade , int lotacao, string idparque)
    : cidade_(cidade), lotacao_(lotacao), idparque_(idparque) {
    // cria um parque com 100 lugares "vazios"    
    for (int i = 0; i < lotacao_; i++) {
        viatura_[i] = RegistoES();
    }
}

// Setters
void Parque::setIdParque(string idparque) {
    idparque_ = idparque;
}
void Parque::setCidade(string cidade) {
	cidade_ = cidade;
}
void Parque::setLotacao(int lotacao) {
    lotacao_ = lotacao;
}

// Getters
int         Parque::getLotacao()    const { return lotacao_;  }
string      Parque::getIdParque()   const { return idparque_; }
string      Parque::getCidade()     const { return cidade_;   }
RegistoES   Parque::getRegisto(string matricula) const {
    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() == matricula)
            return viatura_[i];
    }
    throw invalid_argument("Registo nao encontrado!");
}

// Métodos Auxiliares
// Regista entrada de uma viatura 
bool Parque::estaciona(Viatura v, DataHora dhe) {
    if (ocupacao() == lotacao_)
        throw invalid_argument("Parque lotado!");
    
    RegistoES r(v, dhe);

    if (estaEstacionado(r))
        throw invalid_argument("Viatura ja esta parqueada!");

    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() == "") {
            viatura_[i] = r;
            registos_.push_back(r);     // adiciona ao histórico
            return true;
        }
    }
    return false;
}
// Regista a saida de uma viatura e devolve valor a pagar
double Parque::saida(string matricula, DataHora dhs) {
    double total = 0.0;

    // Se tiver avença paga
    if (temAvencaPaga(matricula, dhs)) {
        for (int i = 0; i < lotacao_; i++) {
            if (viatura_[i].getViatura().getMatricula() == matricula) {
                viatura_[i].registaSaida(dhs);
                registos_.push_back(viatura_[i]);
                viatura_[i] = RegistoES();
				return 0.0;
            }
        }
    }

	// Se não tiver avença paga
    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() == matricula) {
            viatura_[i].registaSaida(dhs);      // regista a saida da viatura
            total = valorAPagar(viatura_[i]);   // devolve o valor a pagar
			viatura_[i].setValorPago(total);	// regista o valor pago
            registos_.push_back(viatura_[i]);   // adiciona o registo no histórico
            viatura_[i] = RegistoES();
            break;
        }
    }
    return total;
}
// Valor a pagar por uma viatura
double Parque::valorAPagar(RegistoES r) {
    double minutos;
    double total = 0.0;
    int dias;

	// Atribui o tempo de estacionamento
    if (r.getDataHoraSaida().getHora() == -1)
        minutos = r.minutosEstacionamento(r.getViatura().getMatricula(), r.getDataHoraAtual());
    else
        minutos = r.minutosEstacionamento(r.getViatura().getMatricula());

	// Atribui o número de dias de estacionamento
    if (r.getDataHoraSaida().getDia() == 0)
		dias = r.diasEstacionamento(r.getDataHoraEntrada(), r.getDataHoraAtual());
    else
        dias = r.diasEstacionamento(r.getDataHoraEntrada(), r.getDataHoraSaida());
        

    // Se entra e sai no mesmo dia
    if (dias == 0)
        return calcularPrecoMesmoDia(r, minutos);

    // Se sai num dia diferente ao de entrada
    else {
        // Calcula preço dos dias completos
        for (int i = 1; i <= dias; ++i) {
            total += calcularPrecoDiaCompleto();    // calcula o custo de 24 horas
            minutos -= 1440.0;                      // remove 24 horas aos minutos
        }

		// Calcula preço do tempo estacionado no ultimo dia
        if (minutos > 0) {
            double minutosUltimoDia = r.getDataHoraSaida().minutosDesdeInicioDoDia();
            total += calcularPrecoMesmoDia(r, minutosUltimoDia);
        }
    }
    return total;
}
// Calcula o preço a pagar de um dia
double Parque::calcularPrecoMesmoDia(RegistoES r, double minutos) {
    int hora = r.getDataHoraEntrada().getHora();
    double mins = r.getDataHoraEntrada().getMinuto();
    double total = 0.0;

    while (minutos > 0) {
		// 00h-8h
        if (hora < 8) {
			double minutosAte8h = min(minutos, (8 - hora) * 60 - mins);   // min (mins que faltam calcular, mins que faltam para chegar às 8h)
            total += (minutosAte8h / 15) * 0.2;
            minutos -= minutosAte8h;
            hora = 8;
            mins = 0;
        }

		// 8h-20h
        else if (hora >= 8 && hora < 20) {
			double minutosAte20h = min(minutos, (20 - hora) * 60 - mins);   // min (mins que faltam calcular, mins que faltam para chegar às 20h)
            if (minutosAte20h > 60.0) {
                total += (60.0 / 15) * 0.2;             // 1ª hora
                minutosAte20h -= 60.0;
				minutos -= 60.0;
                total += (minutosAte20h / 15) * 0.3;    // depois da 1ª hora
            }

            else
                total += (minutosAte20h / 15) * 0.2;

            minutos -= minutosAte20h;
            hora = 20;
            mins = 0;
        }

		// 20h-00h
        else {
			double minutosAte00h = min(minutos, (24 - hora) * 60 - mins);   // min (mins que faltam calcular, mins que faltam para chegar às 00h)
            total += (minutosAte00h / 15) * 0.2;
            minutos -= minutosAte00h;
            hora = 0;
            mins = 0;
        }
    }
    return total;
}
// Calcula o preço de um dia completo
double Parque::calcularPrecoDiaCompleto() {
    double total = 0.0;
    // 00h-8h
    total += (8.0 * 60 / 15) * 0.2;
    // 8h-20h
    total += (60.0 / 15) * 0.2;         // 1ª hora
	total += (11.0 * 60 / 15) * 0.3;    // das 9h-20h
    // 20h-00h
    total += (4.0 * 60 / 15) * 0.2;
    return total;
}
// Regista pagamento da viatura
bool Parque::recebePagamento(string matricula) {
    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() == matricula) {
            viatura_[i].setPago(true);
            return true;
        }
    }
    return false;
}
// Tempo total de estacionamento de uma viatura
DataHora Parque::tempoTotalDeEstacionamento(string matricula) {
    double totalMinutos = 0;
    DataHora dh;
    RegistoES reg;

    for (int i = 0; i < registos_.size(); i++) {
        reg = registos_[i];
        if (reg.getViatura().getMatricula() == matricula && reg.getPago())
            totalMinutos += reg.minutosEstacionamento(matricula);
    }
	// Converte para HH:MM
    return dh.converteParaFormatoHora(totalMinutos);
}
// Valores pagos por uma viatura
double Parque::valorTotalPago(string matricula) {
    double totalPago = 0.0;
    RegistoES reg;

    for (int i = 0; i < registos_.size(); i++) {
        reg = registos_[i];
        if (reg.getViatura().getMatricula() == matricula && reg.getPago())
            totalPago += reg.getValorPago();
    }
    return totalPago;
}
// Valor em falta a pagar pelas viatura estacionadas até hora e data atual
double Parque::valorFaltaPagar(DataHora dha) {
    double total = 0.0;
    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() != "") {
            viatura_[i].setRegistoAtual(dha);
            total += valorAPagar(viatura_[i]);
        }
    }
    return total;
}
// Valor total recebido pelo parque
double Parque::valorTotalParque() const {
    double total = 0.0;
    for (int i = 0; i < registos_.size(); i++) {
        if (registos_[i].getPago())
            total += registos_[i].getValorPago();
    }
    return total;
}
// Número de viaturas estacionadas
int Parque::ocupacao() {
    int ocupacao = 0;
    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() != "")
            ocupacao++;    
    }
    return ocupacao;
}
// Número de lugares livres
int Parque::lugaresLivres() {
    return lotacao_ - ocupacao();
}
// Verificar se uma viatura se encontra no parque
bool Parque::estaEstacionado(RegistoES r) {
    for (int i = 0; i < lotacao_; i++) {
        if (viatura_[i].getViatura().getMatricula() == r.getViatura().getMatricula())
            return true;
    }
    return false;
}
// Adicionar uma avença ao parque
void Parque::setAvenca(Avenca* avenca) {
    avencas_.push_back(avenca);
}
// Verificar se uma viatura tem avença paga
bool Parque::temAvencaPaga(string matricula, DataHora dh) {
    DataHora dataAtual = dh;
    
    for (int i = 0; i < avencas_.size(); i++) {
        for (const RegistoES& registo : avencas_[i]->getRegistos()) {
            if (registo.getViatura().getMatricula() == matricula && avencas_[i]->estaPago(dataAtual)) {
                return true;
            }
        }
    }
    return false;
}

// Imprimir informações do parque
// Imprimir o histórico do parque
string Parque::historicoParque() const{
    ostringstream oss;
    bool encontrou = false;
    
    for (int i = 0; i < registos_.size(); i++) {
        oss << "- ID:                " << idparque_ << endl;
        oss << "- Cidade:            " << cidade_ << endl;
        oss << registos_[i].toString() << endl;
		encontrou = true;
    }
    if (!encontrou)
        throw invalid_argument("Parque sem registos!");

	return oss.str();
}

// Imprimir o histórico de uma viatura
string Parque::historicoViatura(string matricula) const{
    ostringstream oss;
    bool encontrou = false;

    for (int i = 0; i < registos_.size(); i++) {
        if (registos_[i].getViatura().getMatricula() == matricula) {
            oss << "- ID:                " << idparque_ << endl;
            oss << "- Cidade:            " << cidade_ << endl;
            oss << registos_[i].toString() << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        throw invalid_argument("Matricula sem registo!");
    
    return oss.str();
}

// Imprimir o histórico ultimo registo de uma viatura
string Parque::ultimoRegisto(string matricula) const{
    ostringstream oss;
    bool encontrou = false;
    int i = 0;

    while (i < registos_.size()) {
        if (registos_[i].getViatura().getMatricula() == matricula)
            encontrou = true;
        i++;
    }
    if (encontrou == true) {
        i--;
        oss << "- ID:                " << idparque_ << endl;
        oss << "- Cidade:            " << cidade_ << endl;
        oss << registos_[i].toString() << endl;
    }
    else
        throw invalid_argument("Matricula sem registo!");

    return oss.str();
}
// Imprimir avenças do parque
string Parque::listarAvencas() const {
    ostringstream oss;
    if (avencas_.empty())
        throw invalid_argument("Nenhuma avenca registrada neste parque!");
    else {
        for (int i = 0; i < avencas_.size(); i++)
            oss << avencas_[i]->toString() << endl;
    }

    return oss.str();
}
// Imprimir informações de um cliente por NIF
string Parque::infoClientePorNIF(string nif) const {
    ostringstream oss;
    bool encontrouAvenca = false;
	
    for (int i = 0; i < avencas_.size(); i++) {
		if (avencas_[i]->getNif() == nif) {
			oss << avencas_[i]->toString() << endl;
			encontrouAvenca = true;
			break;
		}
	}
	if (!encontrouAvenca)
		throw invalid_argument("NIF nao encontrado!");

    return oss.str();
}