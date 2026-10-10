#include "Avenca.hpp"

int main() {
    vector<Avenca*> avencas;

    // Data e Hora
	auto* dh1 = new DataHora(2025, 1, 3, 10);
	auto* dh2 = new DataHora(2025, 1, 3, 11);
	auto* dh3 = new DataHora(2025, 1, 3, 12);
	auto* dh4 = new DataHora(2025, 2, 3, 13);
	auto* dh5 = new DataHora(2025, 4, 3, 14);

    // NIFs
	auto* nif1 = new string("123456789");
	auto* nif2 = new string("987654321");

	// Viautras
	auto* v1 = new Viatura("AA-00-AA");
	auto* v2 = new Viatura("BB-11-BB");

    // Avenças
    auto* a1 = new Avenca("Joao", *nif1, *dh1, 2);
    auto* a2 = new Avenca("Maria", *nif2, *dh1, 1);

	avencas.push_back(a1);
	avencas.push_back(a2);

    // Lista de Avenças
    cout << "*** Lista de Avencas ***" << endl;
    for (const Avenca* a : avencas)
        cout << a->toString() << endl;

    // Verificar se a avença está paga
    cout << "*** Avenca do Joao ***" << endl;
    cout << "Esta pago em Janeiro 2025? " << (a1->estaPago(*dh3) ? "Sim" : "Nao") << endl;
    cout << "Esta pago em Fevereiro 2025? " << (a1->estaPago(*dh4) ? "Sim" : "Nao") << endl;
    cout << "Esta pago em Abril 2025? " << (a1->estaPago(*dh5) ? "Sim" : "Nao") << endl << endl;

    // Listar avenças com os registos adicionados
    cout << "*** Avencas Apos Adicionar Registos ***" << endl;

    auto* reg1 = new RegistoES(*v1, *dh1, *nif1);
    auto* reg2 = new RegistoES(*v2, *dh1, *nif2);

    a1->adicionarRegisto(*reg1);
    a2->adicionarRegisto(*reg2);
    
    for (const Avenca* a : avencas)
        cout << a->toString() << endl;

	// Comparar avenças pelo NIF
	cout << "*** Comparar Avenças ***" << endl;
	cout << "Avenca1 == Avenca2: " << (*a1 == *a2 ? "Sim" : "Nao") << endl << endl;

    // ERROS
    cout << "*** Erros ***" << endl;
    // ERRO: Tentar adicionar um registo com NIF já associado
    try {
        a1->adicionarRegisto(*reg1);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;
}