#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Hora {
private:
	int h_, m_, s_;

public:
	// Construtor Padrão
	Hora();

	// Construtor
	Hora(int h, int m=0, int s=0);		// minutos e segundos = 0 por defeito	

	// Setter
	void setHoras(int h, int m=0, int s=0);

	// Getters
	int getHora()	  const;
	int getMinuto()	  const;
	int getSegundos() const;

	// Operadores
	double operator-(const Hora& outra)const;		// calcula a diferença de 2 horas e retorna em minutos
	double operator+(const Hora& outra) const;		// soma 2 horas e retorna em minutos
	bool operator>(const Hora& outra) const;		// compara se a hora é maior que outra
	bool operator==(const Hora& outra) const;		// compara se a hora é igual a outra
	bool operator!=(const Hora& outra) const;		// compara se a hora é diferente de outra
	bool operator>=(const Hora& outra) const;		// compara se a hora é maior ou igual a outra

	// Método Auxiliar
	bool verificaHora() const;		// verifica se a hora é válida

	// Imprimir Hora
	string toString() const;
};

// Método para arredondar valores para 2 casas decimais
double arredondar(double valor);