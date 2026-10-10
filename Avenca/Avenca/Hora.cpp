#include "Hora.hpp"

// Construtor Padrão
Hora::Hora()
	: h_(-1), m_(0), s_(0) {
}

// Construtor
Hora::Hora(int h, int m, int s)
	: h_(h), m_(m), s_(s) {
	if (!verificaHora())
		throw invalid_argument("Hora invalida!");
}

// Setter
void Hora::setHoras(int h, int m, int s) {
	h_ = h;
	m_ = m;
	s_ = s;

	if (!verificaHora())
		throw invalid_argument("Hora invalida!");
}

// Getters
int Hora::getHora()		const { return h_; }
int Hora::getMinuto()	const { return m_; }
int Hora::getSegundos() const { return s_; }

// Operadores
// Calcula a diferença de h2-h1 e retorna em minutos
double Hora::operator-(const Hora& outra) const {
	int segundosH1 = (outra.h_ * 3600) + (outra.m_ * 60) + outra.s_;
	int segundosH2 = (h_ * 3600) + (m_ * 60) + s_;

	double minutosH1 = segundosH1 / 60.0;
	double minutosH2 = segundosH2 / 60.0;

	return minutosH2 - minutosH1;
}
// Soma 2 horas e retorna em minutos
double Hora::operator+(const Hora& outra) const {
	int segundosH1 = (outra.h_ * 3600) + (outra.m_ * 60) + outra.s_;
	int segundosH2 = (h_ * 3600) + (m_ * 60) + s_;

	double minutosH1 = segundosH1 / 60.0;
	double minutosH2 = segundosH2 / 60.0;

	return minutosH1 + minutosH2;
}
// Compara se h2 > h1 
bool Hora::operator>(const Hora& outra) const {
	int segundosH1 = (outra.h_ * 3600) + (outra.m_ * 60) + outra.s_;
	int segundosH2 = (h_ * 3600) + (m_ * 60) + s_;

	int minutosH1 = segundosH1 / 60;
	int minutosH2 = segundosH2 / 60;

	if (minutosH2 > minutosH1)
		return true;

	return false;
}
// Compara se h2 == h1
bool Hora::operator==(const Hora& outra) const {
	if (h_ == outra.h_ && m_ == outra.m_ && s_ == outra.s_)
		return true;
	
	return false;
}
// Compara se h2 != h1
bool Hora::operator!=(const Hora& outra) const {
	if (h_ != outra.h_ || m_ != outra.m_ || s_ != outra.s_)
		return true;
	
	return false;
}
// Compara se h2 >= h1
bool Hora::operator>=(const Hora& outra) const{
	if (h_ >= outra.h_)
		return true;

	else
		return false;
}

// Método Auxiliar
// Verifica se a hora "Hora()" é válida
bool Hora::verificaHora() const {
	if (h_ < 0 || h_ > 23 || m_ < 0 || m_ > 59 || s_ < 0 || s_ > 59)
		return false;
					
	return true;
}

// Imprimir Hora no formato HH:MM:SS
string Hora::toString() const {
	string strHora = to_string(getHora());
	string strMinuto = to_string(getMinuto());
	string strSegundos = to_string(getSegundos());
	return strHora + ":" + strMinuto + ":" + strSegundos;
}

// Método para arredondar valores para 2 casas decimais
double arredondar(double valor) {
	return round(valor * 100) / 100;
}