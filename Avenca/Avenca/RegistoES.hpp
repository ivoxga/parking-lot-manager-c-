#pragma once
#include "Viatura.hpp"
#include "DataHora.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class RegistoES {
private:
	Viatura m_;			// matricula
	DataHora dhe_;		// data e hora de entrada
	DataHora dhs_;		// data e hora de saida
	DataHora dha_;		// data e hora atual
	mutable bool pago_;	// estado de pagamento
	bool estacionado_;	// estado de estacionamento	
	double valorPago_;	// valor a pagar
	string nif_;		// nif do cliente

public:
	// Construtor Padrão
	RegistoES();
	
	// Construtor
	RegistoES(Viatura m, DataHora dhe, string nif = "");

	// Setters
	void setRegistoE(Viatura m, DataHora dhe);
	void setRegistoES(Viatura m, DataHora dhe, DataHora dhs);
	void setRegistoAtual(const DataHora dha);
	void setPago(bool p);
	void setEstacionado(bool e);
	void setValorPago(double vp);
	void setNif(string nif);
	
	// Getters
	Viatura		getViatura()		const;
	DataHora	getDataHoraEntrada()const;
	DataHora	getDataHoraSaida()	const;
	DataHora	getDataHoraAtual()	const;
	bool		getPago()			const;
	bool		getEstacionado()	const;
	double		getValorPago()		const;
	string		getNif()			const;

	// Métodos Auxiliares
	int		registaSaida(DataHora dhs);											// regista saida e devolve minutos estacionados
	int		diasEstacionamento(const DataHora dhe, const DataHora dhs) const;	// calcula dias de estacionamento de uma viatura
	double	minutosEstacionamento(Viatura m) const ;							// calcula tempo de estacionamento em minutos a partir da matricula 
	double	minutosEstacionamento(Viatura m, DataHora dha) const;				// calcula tempo de estacionamento em minutos 
	bool	verificaEstacionament() const;										// verifica se esta estacionado
	bool	verificaPagamento() const;											// verifica se esta pago

	// Imprimir Registo
	string toString () const;
};