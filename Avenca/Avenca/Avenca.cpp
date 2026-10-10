#include "Avenca.hpp"

// Construtor
Avenca::Avenca(string nome, string& nif, DataHora dataAss , int mesesAssinados)
	: nome_(nome), nif_(nif), dataAss_(dataAss), mesesAssinados_(mesesAssinados) {
}

// Setteres
void Avenca::setNome(string nome) { nome_ = nome; }
void Avenca::setNif(string& nif) { nif_ = nif; }
void Avenca::setMesesAssinados(int mesesAssinados) { mesesAssinados_ = mesesAssinados; }

// Getteres
string Avenca::getNome() const { return nome_; }
string Avenca::getNif() const { return nif_; }
int Avenca::getMesesAssinados() const { return mesesAssinados_; }


// Método Auxiliar
// Adicionar registo à avença
void Avenca::adicionarRegisto(RegistoES& registo) {
	for (const RegistoES& r : registos_) {
		if (r.getNif() == registo.getNif())
			throw invalid_argument("NIF ja tem avenca associada!");
	}
	registos_.push_back(registo);
}
// Verificar se a avença está paga
bool Avenca::estaPago(DataHora dh) const {
	int mesAssinatura = dataAss_.getMes();
	int anoAssinatura = dataAss_.getAno();

	// Calcular o mês e ano final da assinatura
	int mesesTotais = mesesAssinados_;
	int mesFinal = (mesAssinatura + mesesTotais - 1) % 12;
	int anosExtras = (mesAssinatura + mesesTotais - 1) / 12;
	int anoFinal = anoAssinatura + anosExtras;

	// Verificar se o mês e ano estão no intervalo
	if (dh.getAno() < anoAssinatura || dh.getAno() > anoFinal) 
		return false;
	
	if (dh.getAno() == anoAssinatura && dh.getMes() < mesAssinatura)
		return false;

	if (dh.getAno() == anoFinal && dh.getMes() > mesFinal)
		return false;

	return true;
}

// Operador
// Comparar avenças pelo NIF
bool Avenca::operator==(const Avenca& a) const {
	return nif_ == a.nif_;
}

// Imprimir Avença
string Avenca::toString() const {
	ostringstream oss;
	oss << "- Nome:                " << nome_ << endl;
	oss << "- NIF:                 " << nif_ << endl;
	oss << "- Meses assinados:     " << mesesAssinados_ << endl;
	
	for (const RegistoES& r : registos_) {
		oss << "- Matricula:           " << r.getViatura().getMatricula() << endl;
		oss << "- Entrada:             " << r.getDataHoraEntrada().getDataHora() << endl;
		oss	<< "- Saida:               " << (r.getDataHoraSaida().getHora() == -1 ? 
			"- Ainda estacionado" : r.getDataHoraSaida().getDataHora()) << endl;
	}

	return oss.str();
}