#pragma once
#include "DataHora.hpp"
#include "Viatura.hpp"
#include "RegistoES.hpp"
#include "Avenca.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Parque {

private:
	vector<RegistoES> registos_;    // registo de entradas e saidas
	vector<Avenca*> avencas_;		// registo de avenças
	RegistoES viatura_[100];	    // registo de viaturas
	string idparque_;               // identificador do parque
	string cidade_;                 // cidade do parque
	int lotacao_;                   // lotação do parque
    
public:
    // Construtor
    Parque(string cidade, int lotacao=100, string idparque="");       // por omissão assume 100 lugares 

	// Setters
    void setIdParque(string idparque);
	void setCidade(string cidade);
    void setLotacao(int lotacao);
	void setAvenca(Avenca* avenca);

	// Getters
    int         getLotacao()    const;
    string      getIdParque()   const;
	string      getCidade()     const;
    RegistoES   getRegisto(string matricula) const;
    
	// Métodos Auxiliares
    int ocupacao();												// número de viaturas estacionadas
    int lugaresLivres();										// número de lugares livres
	double valorAPagar(RegistoES r);							// valor a pagar por uma viatura
    double saida(string matricula, DataHora dhs);				// regista saida da viatura e devolve valor a pagar
    double valorTotalPago(string matricula);					// valores pagos por uma viatura
    double valorFaltaPagar(DataHora dha);						// valor em falta a pagar por as viatura estacionadas até ha e da
	double valorTotalParque() const;							// valor total do parque
	double calcularPrecoMesmoDia(RegistoES r, double minutos);	// calcula o preço a pagar de um dia
	double calcularPrecoDiaCompleto();							// calcula o preço de um dia completo
	bool estaEstacionado(RegistoES r);							// verdadeiro se viatura se encontra no parque 
    bool estaciona(Viatura v, DataHora dhe);					// regista entrada da viatura
	bool recebePagamento(string matricula);						// regista pagamento da viatura
	bool temAvencaPaga(string matricula, DataHora dh);			// verifica se viatura tem avença paga
    DataHora tempoTotalDeEstacionamento(string matricula);		// tempo total de estacionamento de uma viatura

	// Imprimir informações do parque
	string historicoParque() const;						// imprime historico do parque
	string historicoViatura(string matricula) const;	// imprime historico de uma viatura
	string ultimoRegisto(string matricula) const;		// imprime ultimo registo de uma viatura
	string listarAvencas() const;						// imprime lista de avenças
	string infoClientePorNIF(string nif) const;			// imprime informações de um cliente por NIF
};