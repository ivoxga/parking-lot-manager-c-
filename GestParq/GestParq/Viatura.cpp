#include "Viatura.hpp"

// Construtor Padrão
Viatura::Viatura()
	: m_("") {
}

// Construtor
Viatura::Viatura(string m)
	: m_(m) {
}

// Setter
void Viatura::setMatricula(string m) {
	m_ = m;
}

// Getter
string Viatura::getMatricula() const { return m_; }

// Operador
// Verifica se a matricula é igual a outra
bool Viatura::operator==(const Viatura& outra) const {
	if (m_ == outra.m_)
		return true;
	
	return false;
}

// Imprimir Matricula
string Viatura::toString() const {
	return getMatricula();
}