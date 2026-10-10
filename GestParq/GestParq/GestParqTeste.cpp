#include "GestParq.hpp"

using namespace std;

int main() {
    GestParq gestor(Parque("Inicial", 100)); // Inicializar o gestor com um parque inicial
    bool continuar = true;

    while (continuar) {
        // Mostrar o menu
        cout << "=============== MENU ===============" << endl;
        cout << "1. Inserir um novo parque numa cidade" << endl;
        cout << "2. Listar parques de uma cidade" << endl;
        cout << "3. Registar a entrada de um veiculo" << endl;
        cout << "4. Registar a saida de um veiculo" << endl;
        cout << "5. Localizar veiculo estacionado" << endl;
        cout << "6. Listar historico de uma viatura" << endl;
        cout << "0. Sair" << endl;
        cout << "====================================" << endl;
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;

        // Verificar se a entrada é válida
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcao invalida! Insira um numero." << endl;
            continue;
        }

        switch (opcao) {
        case 1: { // Inserir um novo parque numa cidade
            string cidade;
            int capacidade;
            cout << "Insira o nome da cidade: ";
            cin >> cidade;
            cout << "Insira a capacidade do parque: ";
            cin >> capacidade;
            try {
                gestor = GestParq(Parque(cidade, capacidade));
                cout << "Parque adicionado com sucesso!" << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 2: { // Listar parques de uma cidade
            string cidade;
            cout << "Insira o nome da cidade: ";
            cin >> cidade;
            try {
                cout << gestor.parquesDaCidade(cidade) << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 3: { // Registar a entrada de um veículo
            string matricula, idParque;
            cout << "Insira o ID do parque: ";
            cin >> idParque;
            cout << "Insira a matricula do veiculo: ";
            cin >> matricula;

            Viatura viatura(matricula); // Apenas a matrícula é fornecida
            DataHora entrada; // Assumindo que DataHora inicializa com a hora atual
            RegistoES registo(viatura, entrada);

            try {
                if (gestor.registarEntrada(registo, idParque)) {
                    cout << "Entrada registada com sucesso!" << endl;
                }
                else {
                    cout << "Erro ao registar a entrada. Parque lotado ou outro problema." << endl;
                }
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 4: { // Registar a saída de um veículo
            string matricula, idParque;
            cout << "Insira o ID do parque: ";
            cin >> idParque;
            cout << "Insira a matricula do veiculo: ";
            cin >> matricula;

            DataHora saida; // Assumindo que DataHora inicializa com a hora atual
			RegistoES registo(Viatura("AA-00-22"), DataHora(2021, 5, 20, 10), "123456789");

            try {
                double valorPago = gestor.registarSaida(registo, idParque);
                cout << "Saida registada com sucesso! Valor a pagar: " << valorPago << " EUR" << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 5: { // Localizar veículo estacionado
            string matricula;
            cout << "Insira a matricula do veiculo: ";
            cin >> matricula;
            try {
                cout << gestor.cidadeEstacionamento(matricula) << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 6: { // Listar histórico de uma viatura
            string matricula;
            cout << "Insira a matricula do veiculo: ";
            cin >> matricula;
            try {
                cout << gestor.historicoViatura(matricula) << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 0: { // Sair
            continuar = false;
            cout << "A sair do programa..." << endl;
            break;
        }
        default:
            cout << "Opcao invalida! Escolha uma opcao entre 0 e 6." << endl;
            break;
        }
    }

    return 0;
}
