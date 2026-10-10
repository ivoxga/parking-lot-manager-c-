#include "RegistoES.hpp"

// Construtor Padrão
RegistoES::RegistoES()
    : m_(Viatura()),
    dhe_(DataHora()),
    dhs_(DataHora()),
    dha_(DataHora()),
    pago_(false),
    estacionado_(false),
    valorPago_(0.0),
    nif_("") {
}

// Construtores
RegistoES::RegistoES(Viatura m, DataHora dhe, string nif)
    : m_(Viatura(m)),
	dhe_(DataHora(dhe)),
    dhs_(DataHora()),
    dha_(DataHora()),
    pago_(false),
    estacionado_(true),
    valorPago_(0.0),
    nif_(nif) {
}

// Setters
void RegistoES::setRegistoE(Viatura m, DataHora dhe) {
    m_  = m;
    dhe_ = dhe;
}
void RegistoES::setRegistoES(Viatura m, DataHora dhe, DataHora dhs) {
    m_  = m;
    dhe_ = dhe;
    dhs_ = dhs;
}
void RegistoES::setRegistoAtual(const DataHora dha){
	if (dha >= dhe_)
		dha_ = dha;
	else
		throw invalid_argument("Hora e/ou data atual menor que hora e/ou data de entrada!");
}
void RegistoES::setPago(bool p) {
	pago_ = p;
}
void RegistoES::setEstacionado(bool e) {
	estacionado_ = e;
}
void RegistoES::setValorPago(double vp) {
	valorPago_ = vp;
}
void RegistoES::setNif(string nif) {
	nif_ = nif;
}

// Getters
Viatura     RegistoES::getViatura()         const { return m_; }
DataHora    RegistoES::getDataHoraEntrada() const { return dhe_; }
DataHora    RegistoES::getDataHoraSaida()   const { return dhs_; }
DataHora    RegistoES::getDataHoraAtual()   const { return dha_; }
bool        RegistoES::getPago()            const { return pago_; }
bool        RegistoES::getEstacionado()     const { return estacionado_; }
double      RegistoES::getValorPago()       const { return valorPago_; }
string      RegistoES::getNif()             const { return nif_; }

// Métodos auxiliares
// Regista saida e calcula tempo de estacionamento 
int RegistoES::registaSaida(DataHora dhs) {
	if (dhs >= dhe_) {
		if (dhs_ != DataHora())
            throw invalid_argument("Hora e/ou data de saida ja registada!");

		dhs_ = dhs;
		estacionado_ = false;
		pago_ = true;

        return minutosEstacionamento(m_);
	}
	else
		throw invalid_argument("Hora ou data de saida invalida!");
}
// Calcula o tempo de estacionamento com horas atuais 
double RegistoES::minutosEstacionamento(Viatura m, DataHora dha) const {
    return dha - dhe_;
}
// Calcula o tempo de estacionamento se a viatura tiver hora e data de saida
double RegistoES::minutosEstacionamento(Viatura m) const {
	return dhs_ - dhe_;
}
// Calcula os dias de estacionamento
int RegistoES::diasEstacionamento(const DataHora dhe, const DataHora dhs) const {
    return dhs.difDeDias(dhe);
}
// Verifica se está estacionado
bool RegistoES::verificaEstacionament() const {
    return estacionado_ == true;
}
// Verifica se está pago
bool RegistoES::verificaPagamento() const {
	return pago_ == true;
}

// Imprimir Registo 
string RegistoES::toString() const {
    ostringstream oss;
    oss << fixed << setprecision(2);
    oss << "- NIF:               " << nif_ << endl;
    oss << "- Matricula:         " << m_.getMatricula() << endl;
    oss << "- Entrada:           " << dhe_.getDataHora() << endl;

    // Saída
    if (dhs_ != DataHora()) {
        oss << "- Saida:             " << dhs_.getDataHora() << endl;
        oss << "- Tempo estacionado: " << minutosEstacionamento(m_) << " mins" << endl;
		oss << "- Valor pago:        " << valorPago_ << " EUR" << endl;
    }
    // Hora e data atuais
    else if (dha_ != DataHora()){
        oss << "- Saida nao registada." << endl;
        oss << "- Data-Hora Atual:   " << dha_.getDataHora() << endl;
        oss << "- Tempo estacionado: " << minutosEstacionamento(m_, dha_) << " mins" << endl;
    }

    // Estado de pagamento e estacionamento
    oss << "- Estacionado:       " << (estacionado_ ? "Sim" : "Nao") << endl;
    oss << "- Pago:              " << (pago_ ? "Sim" : "Nao") << endl;

    return oss.str();
}