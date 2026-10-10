#pragma once
#include <iostream>
#include <iomanip>  // print: std::stfill std::stw
#include <stdexcept>
#include <sstream>

using namespace std;

class Data {
private:
    int ano_;
    int mes_;
    int dia_;

public:
    // Construtor Padrão
    Data();

    // Construtor
    Data(int ano, int mes, int dia);

    // Setter
    void setData(int ano, int mes, int dia);

    // Getters
    int getAno() const;
    int getMes() const;
    int getDia() const;

    // Operadores
    int  operator-(const Data& outra) const;    // calcula a diferença de dias
	bool operator>(const Data& outra) const;    // verifica se de > ds = true
	bool operator>=(const Data& outra) const;   // verifica se de >= ds = true
	bool operator==(const Data& outra) const;   // verifica se de == ds = true
	bool operator!=(const Data& outra) const;   // verifica se de != ds == true

    // Métodos Auxiliares
	bool dBissexto(int) const;  // verifica se o ano é bissexto
	bool dValida() const;       // verifica se a data é válida

    // Imprimir Data    
    string toString() const;
};