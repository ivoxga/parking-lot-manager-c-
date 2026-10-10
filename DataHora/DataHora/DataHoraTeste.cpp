#include "DataHora.hpp"
#include <iostream>

int main() {

    DataHora dataHora1(2024, 12, 16, 17, 30);
    cout << "Data-Hora 1: " << dataHora1.getDataHora() << endl;
    dataHora1.setData(2024,12, 25);
    dataHora1.setHoras(18);
    cout << "Data-Hora 1 atualizada: " << dataHora1.getDataHora() << endl;

    DataHora dataHora2(2024, 12, 16, 19);
    cout << "Data-Hora 2: " << dataHora2.getDataHora() << endl << endl;

	// Operadores
	cout << "DataHora1 == DataHora2: " << (dataHora1 == dataHora2 ? "Sim" : "Nao") << endl;
	cout << "DataHora1 >= DataHora2: " << (dataHora1 >= dataHora2 ? "Sim" : "Nao") << endl;
	cout << "DataHora1 != DataHora2: " << (dataHora1 != dataHora2 ? "Sim" : "Nao") << endl;
	cout << "DataHora1 - DataHora2:  " << (dataHora1 - dataHora2) << endl;

	// Calcula a diferença de dias
	cout << "Diferenca de dias entre DataHora1 e DataHora2: " << dataHora1.difDeDias(dataHora2) << endl << endl;

	// Calcula quantos minutos faltam para o fim do dia a partir da hora e minuto atuais
	cout << "Minutos ate o fim do dia: " << dataHora1.minutosAteFimDoDia() << endl;

	// Calcula os minutos desde o início do dia
	cout << "Minutos desde o inicio do dia: " << dataHora1.minutosDesdeInicioDoDia() << endl;

	// Converte minutos para o formato DataHora(DD, MM, AAAA, HH, MM)
	cout << "Converte 1440 minutos para DataHora: " << dataHora1.converteParaFormatoHora(1440).getDataHora() << endl << endl;

    // ERROS
	cout << "ERROS" << endl;
    // ERRO: Data invalida
    try 
    {
        dataHora1.setData(2024, 23, 9);
        cout << "Data e Hora Atualizada: " << dataHora1.getDataHora() << endl;
	}
	catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl;
	}

    // ERRO: Hora invalida
    try 
    {
        dataHora1.setHoras(24);
        cout << "Data e Hora Atualizada: " << dataHora1.getDataHora() << endl;
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl;
    }

    return 0;
}
