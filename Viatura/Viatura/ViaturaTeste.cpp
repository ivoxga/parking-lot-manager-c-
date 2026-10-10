#include "Viatura.hpp"

int main() {

	Viatura v1("AA-00-BB");
	cout << v1.toString() << endl;

	Viatura v2("CC-11-DD");
	cout << v2.toString() << endl;

	if (v1 == v2)
		cout << "Sao iguais" << endl;
	else
		cout << "Sao diferentes" << endl;

	return 0;
}