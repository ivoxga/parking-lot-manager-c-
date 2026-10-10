#pragma once
#include "Data.hpp"
#include "Hora.hpp"
#include <sstream>

using namespace std;

class DataHora : public Hora, public Data {
public:
	// Construtor Padrão
	DataHora();

	// Construtor
	DataHora(int ano, int mes, int dia, int horas, int minutos=0, int segundos=0);

	// Operadores
	bool operator==(const DataHora& outra) const;	// verifica se: DataHora(X) == DataHora(Y)
	bool operator>=(const DataHora& outra) const;	// verifica se: DataHora(X) >= DataHora(Y)
	bool operator!=(const DataHora& outra) const;	// verifica se: DataHora(X) != DataHora(Y)
	int operator-(const DataHora& outra)   const;	// calcula a diferença de dias e horas
	
	// Método Auxiliar
	int difDeDias(const DataHora& outra) const;		// calcula a diferença de dias
	int minutosAteFimDoDia() const;					// calcula quantos minutos faltam para o fim do dia a partir da hora e minuto atuais
	int minutosDesdeInicioDoDia() const;			// calcula os minutos desde o início do dia
	DataHora converteParaFormatoHora(int mins);		// converte minutos para o formato DataHora(DD, MM, AAAA, HH, MM)

	// Imprimir Data e Hora juntas
	string getDataHora() const; 
};