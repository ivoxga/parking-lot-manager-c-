#pragma once
#include "Parque.hpp"

using namespace std;

class GestParq {
private:
    vector<Parque> parques_; // Coleção de parques

public:
	// Construtor
    GestParq(Parque parque);

	// Metodos Auxiliares
    bool registarEntrada(RegistoES re, string parqueidParque);  // registar entrada de uma viatura num parque
    double registarSaida(RegistoES rs, string parqueidParque);  // registrar saída de uma viatura em um parque específico

	// Imprimir informações
    string parquesDaCidade(string cidade) const;        // parque de uma cidade
	string historicoViatura(string matricula) const;    // historico de um veiculo
	string cidadeEstacionamento(string matricula) const;// mostrar a cidade onde está estacionado uma viatura
};