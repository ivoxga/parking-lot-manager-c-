#include "Hora.hpp"

int main() {
	
	Hora hora1(10, 30);
	cout << "Hora1: " << hora1.toString() << endl;
	
	Hora hora2(11);
	cout << "Hora2: " << hora2.toString() << endl << endl;

	// Operações
	cout << "Diferenca entre as horas: " << hora2 - hora1 << " minutos" << endl;
	cout << "Soma das horas:           " << hora1 + hora2 << " minutos" << endl;
	cout << "Hora1 > Hora2:            " << (hora1 > hora2 ? "Sim" : "Nao") << endl;
	cout << "Hora1 == Hora2:           " << (hora1 == hora2 ? "Sim" : "Nao") << endl;
	cout << "Hora1 != Hora2:           " << (hora1 != hora2 ? "Sim" : "Nao") << endl;
	cout << "Hora1 >= Hora2:           " << (hora1 >= hora2 ? "Sim" : "Nao") << endl << endl;

	// ERRO: Hora inválida
	try 
	{
		Hora hora2(25);
		cout << hora2.toString() << endl;
	}
	catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
	}

	// ERRO: Atualização da Hora inválida
	try 
	{
		hora1.setHoras(16, 65);
		cout << hora1.toString() << endl;
	}
	catch (invalid_argument& e)
	{
		cerr << e.what() << endl;
	}
	
	return 0;
}