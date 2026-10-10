#pragma once
#include <iostream>
#include <string>

using namespace std;

class Viatura {
private:
	string m_;

public:
	// Construtor Padrão
	Viatura();

	// Construtor
	Viatura(string);

	// Setter
	void setMatricula(string);

	// Gette
	string getMatricula() const;

	// Operador
	bool operator==(const Viatura&) const;	// compara se a matricula é igual a outra

	// Imprimir Matricula
	string toString() const;
};