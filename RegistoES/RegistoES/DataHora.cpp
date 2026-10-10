#include "DataHora.hpp"

// Construtor padrão
DataHora::DataHora()
    : Data(), Hora() {
}

// Construtor
DataHora::DataHora(int ano, int mes, int dia, int horas, int minutos, int segundos)
    : Data(ano, mes, dia), Hora(horas, minutos, segundos) {
}

// Operadores
// Verifica se DataHora(X) == DataHora(Y)
bool DataHora::operator==(const DataHora& outra) const {
    return Data::operator==(outra) && Hora::operator==(outra);
}
// Verifica se DataHora(X) >= DataHora(Y)
bool DataHora::operator>=(const DataHora& outra) const {
    return Data::operator>=(outra) && Hora::operator>=(outra);
}
// Verifica se DataHora(X) != DataHora(Y)
bool DataHora::operator!=(const DataHora& outra) const {
    return Data::operator!=(outra) && Hora::operator!=(outra);
}
// Calcula a diferença de dias e horas
int DataHora::operator-(const DataHora& outra) const {
    int diffDias = Data::operator-(outra);      // calcula a diferença de dias entre as datas
    int diffMinutos = Hora::operator-(outra);   // calcula a diferença de minutos entre as horas
    return diffDias * 1440 + diffMinutos;
}

// Métodos Auxiliares
// Calcula a diferença de dias
int DataHora::difDeDias(const DataHora& outra) const {
    int diffDias = Data::operator-(outra);
	return diffDias;
}
// Calcula quantos minutos faltam para o fim do dia a partir da hora e minuto atuais
int DataHora::minutosAteFimDoDia() const {
	if (this->getHora() == 0 && this->getMinuto() == 0 && this->getSegundos() == 0)
		return 1440;

    else {
        int minutosRestantes = 60 - this->getMinuto();
        int horasRestantes = 23 - this->getHora();
        return horasRestantes * 60 + minutosRestantes;
    }
}
// Calcula os minutos desde o início do dia
int DataHora::minutosDesdeInicioDoDia() const {
    return this->getHora() * 60 + this->getMinuto();
}
// Converte minutos para o formato DataHora(DD, MM, AAAA, HH, MM)
DataHora DataHora::converteParaFormatoHora(int mins) {
    int dia = 0;
    int mes = 0;
    int ano = 0;

    if (mins >= 1440) {
        while (mins >= 1440) {
            dia++;
            mins -= 1440;

            if (dia > 30) {
                dia = 1;
                mes++;
            }

            if (mes == 12) {
                mes = 0;
                ano++;
            }
        }
        return DataHora(ano, mes, dia, mins / 60, mins % 60);
    }

    else
        return DataHora(ano, mes, dia, mins / 60, mins % 60);
}

// Imprime a Data e a Hora no formato: "DD/MM/AAAA  HH:MM:SS"
string DataHora::getDataHora() const {
	ostringstream oss;
    oss << Data::toString() << "  " << Hora::toString();
	return oss.str();
}