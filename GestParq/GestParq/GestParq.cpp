#include "GestParq.hpp"

// Construtor
GestParq::GestParq(Parque parque) {
    static int idCounter = 0;
    bool cidadeExistente = false;

    for (const auto& p : parques_) {
        if (p.getCidade() == parque.getCidade()) {
            cidadeExistente = true;
            break;
        }
    }

    if (!cidadeExistente)
        parque.setIdParque(to_string(idCounter++));

    parques_.push_back(parque);
}

// Metodos Auxiliares
// Registar entrada de uma viatura num parque específico
bool GestParq::registarEntrada(RegistoES re, string idParque) {
    for (int i = 0; i < parques_.size(); i++) {
        if (parques_[i].getIdParque() == idParque) {
            return parques_[i].estaciona(re.getViatura(), re.getDataHoraEntrada());
        }
    }
	throw invalid_argument("Parque nao encontrado!");
}
// Registrar saída de uma viatura em um parque específico
double GestParq::registarSaida(RegistoES rs, string idParque) {
	for (int i = 0; i < parques_.size(); i++) {
		if (parques_[i].getIdParque() == idParque)
			return parques_[i].saida(rs.getViatura().toString(), rs.getDataHoraSaida());
	}
	throw invalid_argument("Parque nao encontrado!");
}

// Imprimir informações
// Listar parques de uma cidade
string GestParq::parquesDaCidade(string cidade) const {
    ostringstream oss;
    for (int i = 0; i < parques_.size(); i++) {
        if (parques_[i].getCidade() == cidade)
            oss << "Parque: " << parques_[i].getCidade() << ", ID: " << parques_[i].getIdParque() << endl;
    }

    if(oss.str().empty())
		throw invalid_argument("Nenhum parque encontrado na cidade!");
    else
        return oss.str();
}
// Imprimir o historico de uma viatura
string GestParq::historicoViatura(string matricula) const {
    ostringstream oss;
    for (int i = 0; i < parques_.size(); i++)
		oss << parques_[i].historicoViatura(matricula);

    if (oss.str().empty())
        throw invalid_argument("Nenhum historico encontrado para esta matricula!");
    else
        return oss.str();
}
// Mostrar a cidade onde está estacionado uma viatura
string GestParq::cidadeEstacionamento(string matricula) const {
    ostringstream oss;

	// Procurar em todos os parques
    for (int j = 0; j < parques_.size(); j++) {
        const RegistoES& registo = parques_[j].getRegisto(matricula);

		// Se a viatura estiver estacionada retornar a cidade
        if (registo.getViatura().getMatricula() == matricula && registo.getEstacionado()) {
            oss << "Cidade: " << parques_[j].getCidade() << ", Parque: " << parques_[j].getIdParque() << endl;
            return oss.str();
        }
    }

    throw invalid_argument("Viatura nao encontrada!");
}