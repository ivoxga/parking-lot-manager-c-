
#include "Parque.hpp"

using namespace std;

int main() {
    // Parque
    Parque p("Barcelos", 3);

    // Viaturas
    Viatura v1("00-AA-11");
    Viatura v2("11-BB-22");
    Viatura v3("22-CC-33");

    // Data-Horas
    DataHora dh1(2024, 11, 26, 0);
    DataHora dh2(2024, 11, 26, 7, 30);
    DataHora dh3(2024, 11, 26, 8);
    DataHora dh11(2024, 11, 27, 10);

    // NIFs
    string nif1 = "123456789";
    string nif2 = "987654321";

    // Nomes
    string n1 = "Joao";
    string n2 = "Maria";

    // Registos
    RegistoES r1(v1, dh1, nif1);
    RegistoES r2(v2, dh1, nif2);
    RegistoES r3(v3, dh2);

    // Avenças
    Avenca a1(n1, nif1, dh1, 1);
    Avenca a2(n2, nif2, dh1, 2);

    p.setAvenca(&a1);
    p.setAvenca(&a2);

    // Informações do parque
    cout << "*** Parque criado ***" << endl;
    cout << "- ID:       " << p.getIdParque() << endl;
    cout << "- Cidade:   " << p.getCidade() << endl;
    cout << "- Lotacao:  " << p.getLotacao() << endl;
    cout << "- Ocupacao: " << p.ocupacao() << endl;
    cout << "- Livres:   " << p.lugaresLivres() << endl << endl;

    // Listar avenças do parque
    cout << "*** Listar avenças ***" << endl;
    cout << p.listarAvencas();

    // Registar nas avenças
    a1.adicionarRegisto(r1);

    // Informações de um cliente por NIF
    cout << "*** Informacoes de um cliente por NIF ***" << endl;
    cout << p.infoClientePorNIF(nif1);

    // ENTRA viatura 1
    p.estaciona(v1, dh1);
    cout << "*** Entra ***" << endl;
    cout << p.getRegisto("00-AA-11").toString() << endl;

    // SAI viatura 1
    cout << "*** Sai ***" << endl;
    double valor = p.saida("00-AA-11", dh11);
    cout << p.ultimoRegisto("00-AA-11");

    // ENTRA viatura 2
    p.estaciona(v2, dh1);
    cout << "*** Entra ***" << endl;
    cout << p.getRegisto("11-BB-22").toString() << endl;

    // SAI viatura 2
    cout << "*** Sai ***" << endl;
    double valor2 = p.saida("11-BB-22", dh11);
    cout << p.ultimoRegisto("11-BB-22");

    // ENTRA viatura 3
    p.estaciona(v3, dh2);
    cout << "*** Entra ***" << endl;
    cout << p.getRegisto("22-CC-33").toString() << endl;

    // Quanto falta receber dos carros estacionados no parque até à hora atual
    double faltaPagar = p.valorFaltaPagar(dh3);
    cout << "*** Falta Receber ***" << endl;
    cout << "- Data-Hora atual:    " << dh3.getDataHora() << endl;
    cout << "- Ocupacao:           " << p.ocupacao() << endl;
    cout << "- Falta receber:      " << faltaPagar << " EUR" << endl << endl;

    // Histórico de parqueamento de uma viatura
    cout << "*** Todos os registos do parque ***" << endl;
    cout << p.historicoParque();

    // Total pago e tempo de estacionamento de uma viatura
    DataHora tempTotal;
    cout << "*** Total pago e estacionamento de uma viatura ***" << endl;
    cout << "- Viatura: " << v1.getMatricula() << endl;
    tempTotal = p.tempoTotalDeEstacionamento("00-AA-11");
    cout << "- Horas:   " << tempTotal.getDataHora() << endl;
    cout << "- Valor:   " << p.valorTotalPago("00-AA-11") << " EUR" << endl << endl;

    // Histórico de registos de uma viatura
    cout << "*** Histórico de uma viatura ***" << endl;
    cout << p.historicoViatura("00-AA-11");

    // Verificar se viatura está no parque
    cout << "*** Verificar se viatura está no parque ***" << endl;
    cout << (p.estaEstacionado(p.getRegisto("22-CC-33")) ? "Esta" : "Nao esta") << endl << endl;

    // Dinheiro total feito pelo parque
    cout << "*** Total pagamentos recebidos pelo parque ***" << endl;
    double total = p.valorTotalParque();
    cout << "- Total: " << total << " EUR" << endl << endl;

    // Testes de erro
    cout << "*** Erros ***" << endl;
    // ERRO: Regista hora de saida antes da entrada
    try 
    {
        p.estaciona(v3, dh2);
        p.saida("30-CD-60", dh1);
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Registar entrada de uma viatura já estacionada
    try 
    {
        p.estaciona(v2, dh1);
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Hora invalida
    try 
    {
        DataHora dh8(2024, 11, 26, 25);
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Data invalida
    try 
    {
        DataHora dh8(2024, 11, 31, 20);
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Registo não existente
    try 
    {
        p.getRegisto("22-EE-22");
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Parque lotado
    try 
    {
        Parque p2("Barcelos", 2);
        p2.estaciona(v1, dh1);
        p2.estaciona(v2, dh1);
        p2.estaciona(v3, dh1);
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Parque sem registos
    try 
    {
        Parque p2("Barcelos", 2);
        cout << p2.historicoParque();
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Matricula sem histórico no parque
    try 
    {
        cout << p.historicoViatura("22-ED-22");
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Matricula sem histórico no parque
    try 
    {
        cout << p.ultimoRegisto("22-ED-22");
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // EERO: Avença duplicada
    try 
    {
        p.setAvenca(&a1);
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }
    // ERRO: Avença não existente
    try 
    {
        Parque p11("Barcelos");
        cout << p11.listarAvencas();
    }
    catch (const invalid_argument& e) 
    {
        cerr << e.what() << endl << endl;
    }

    return 0;
}
