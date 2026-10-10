#include "RegistoES.hpp"

using namespace std;

int main() {
    vector<RegistoES> registos;

	// Viaturas
	auto* v1 = new Viatura("10-BB-01");
	auto* v2 = new Viatura("11-EE-11");

	// Data e Hora
	auto* dh1 = new DataHora(2024, 12, 30, 15, 30);
	auto* dh2 = new DataHora(2024, 12, 30, 16, 30);
	auto* dh5 = new DataHora(2024, 12, 30, 18);
	auto* dh6 = new DataHora(2024, 12, 30, 18, 30);

    // NIfs
	auto* nif1 = new string("123456789");
	auto* nif2 = new string("987654321");

    // Entrada
	cout << "*** ENTRADA ***" << endl;
	auto* registo1 = new RegistoES(*v1, *dh1, *nif1);
    registos.push_back(*registo1);

    cout << "Registo de entrada:" << endl;
    cout << registos[0].toString() << endl << endl;

    // Atualização da hora e data atuais
    cout << "*** Data-Hora atual ***" << endl;
    registos[0].setRegistoAtual(*dh2);
    cout << registos[0].toString() << endl << endl;

    cout << "*** Metodos Auxiliares ***" << endl;
    // Minutos estacionamento a partir de uma data e hora atual
    cout << "- Minutos de estacionamento a partir de uma data e hora atual: " << registos[0].minutosEstacionamento(*v1, *dh2) << endl;
    // Verifica se esta pago
    cout << "- Verifica se esta pago: " << (registos[0].verificaPagamento() ? "Sim" : "Nao") << endl;
    // Verifica se esta estacionado
    cout << "- Verifica se esta estacionado: " << (registos[0].verificaEstacionament() ? "Sim" : "Nao") << endl << endl;

	// Saida
    cout << "*** SAIDA ***" << endl;
    registos[0].registaSaida(*dh5);
    cout << registos[0].toString() << endl << endl;

    cout << "*** Metodos Auxiliares ***" << endl;
    // Verifica se esta estacionado
    cout << "- Verifica se esta estacionado: " << (registos[0].verificaEstacionament() ? "Sim" : "Nao") << endl;
    // Verifica se esta pago
    cout << "- Verifica se esta pago: " << (registos[0].verificaPagamento() ? "Sim" : "Nao") << endl << endl;
	// Diferença de dias
	cout << "* Data 1: " << dh1->getDataHora() << "    * Data 2: " << dh2->getDataHora() << endl;
    cout << "- Diferenca de dias: " << registos[0].diasEstacionamento(*dh1, *dh2) << endl << endl;
	// Minutos estacionamento
	cout << "- Minutos de estacionamento: " << registos[0].minutosEstacionamento(*v1) << endl << endl;

    // ERROS
	cout << "*** ERROS ***" << endl;
	// ERRO: Hora= 25:00:00
	try
	{
        auto* dh4 = new DataHora(2024, 12, 30, 25);
		auto* registo2 = new RegistoES(*v2, *dh4, *nif2);
		registos.push_back(*registo2);
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what() << endl << endl;
	}

    // ERRO: Data= 31:11:2024
    try
    {
        auto* dh3 = new DataHora(2024, 11, 31, 17);
		auto* registo2 = new RegistoES(*v2, *dh3, *nif2);
        registos.push_back(*registo2);
    }
    catch (const invalid_argument& e)
    {
        cerr << e.what() << endl << endl;
    }

    // ERRO: Hora saida < Hora entrada
    try
    {        
		auto* registo2 = new RegistoES(*v2, *dh2 , *nif2);
        registos.push_back(*registo2);
        registos[1].registaSaida(*dh1);
    }
    catch (const invalid_argument& e)
    {
        cerr << e.what() << endl << endl;
    }

    // ERRO: Hora entrada > Hora atual
    try
    {
        auto* registo3 = new RegistoES(*v2, *dh2, *nif2);
        registos.push_back(*registo3);
        registos[1].setRegistoAtual(*dh1);
    }
    catch (const invalid_argument& e)
    {
        cerr << e.what() << endl << endl;
    }

	// ERRO: Registar outra saida ao mesmo registo
    // Saida
    registos[1].registaSaida(*dh5);
    try
    {
        registos[1].registaSaida(*dh6);
    }
    catch (const invalid_argument& e)
    {
        cerr << e.what() << endl << endl;
    }

	// Limpar memória
	delete v1;
	delete v2;
	delete dh1;
	delete dh2;
	delete dh5;
	delete dh6;
	delete nif1;
	delete nif2;
	delete registo1;
	//delete registo2;

    return 0;
}
