// DataTest.cpp
#include "Data.hpp"

int main() {
    
	Data data1(2024, 1, 1);
	cout << "Data1: " << data1.toString() << endl;

	Data data2(2024, 1, 31);
	cout << "Data2: " << data2.toString() << endl << endl;

	// Operações
	cout << "Diferenca de dias: " << data2 - data1 << endl;
	cout << "Data1 > Data2:     " << (data1 > data2 ? "Sim" : "Nao") << endl;
	cout << "Data1 >= Data2:    " << (data1 >= data2 ? "Sim" : "Nao") << endl;
	cout << "Data1 == Data2:    " << (data1 == data2 ? "Sim" : "Nao") << endl;
	cout << "Data1 != Data2:    " << (data1 != data2 ? "Sim" : "Nao") << endl << endl;

	// ERRO: Data inválida
	try 
	{
		Data data2(2024, 13, 30);
		cout << data2.toString() << endl;
	}
	catch (const invalid_argument& e)
	{
		cerr << e.what() << endl;
	}

	// ERRO: Atualização da Data inválida
	try 
	{
		data1.setData(2024, 2, 30);
		cout << data1.toString() << endl;
	}
	catch (const invalid_argument& e) 
	{
		cerr << e.what() << endl;
	}
	
    return 0;
}