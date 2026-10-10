#pragma once
#include "RegistoES.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Avenca {
private:
	vector<RegistoES> registos_;	// lista de registos associados à avença
	DataHora dataAss_;				// data de assinatura da avença
	string nome_;					// nome do cliente
	string nif_;					// nif do cliente
	int mesesAssinados_;			// quantidade de meses da assinatura

public:
	// Construtor
	Avenca(string nome, string nif, DataHora dataAss, int mesesAssinados = 1);	// assina avença por 1 mes por defeito
	
	// Setteres
	void setNome(string nome);
	void setNif(string nif);
	void setMesesAssinados(int mesesAssinados);

	// Getteres
	const vector<RegistoES>& getRegistos() const;
	string getNome() const;
	string getNif() const;
	int getMesesAssinados() const;

	// Métodos Auxiliares
	void adicionarRegisto(RegistoES registo);		// adicionar registo
	bool estaPago(DataHora dh) const;				// verificar se a avença está paga

	// Operador
	bool operator==(const Avenca& a) const;			// comparar avenças pelo NIF

	// Imprimir Avença
	string toString() const;
};