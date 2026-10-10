#include "Data.hpp"

// Construtor Padrão
Data::Data()
    : ano_(0), mes_(0), dia_(0) {
}

// Construtor
Data::Data(int ano, int mes, int dia)
    : ano_(ano), mes_(mes), dia_(dia) {
    if (!dValida()) {
        if (ano != 0)
            throw invalid_argument("Data invalida!");
    }
}

// Setter
void Data::setData(int ano, int mes, int dia) {
    ano_ = ano;
    mes_ = mes;
    dia_ = dia;
    
    if (!dValida())
        throw invalid_argument("Data invalida!");
}

// Getters
int Data::getAno() const { return ano_; }
int Data::getMes() const { return mes_; }
int Data::getDia() const { return dia_; }

// Operadores
// Calcula a diferença de dias
int Data::operator-(const Data& outra) const {
    return dia_ - outra.dia_;
}
// Verifica se de > ds = true
bool Data::operator>(const Data& outra) const {
    if (ano_ > outra.ano_) {
        return true;
    }
    else if (ano_ == outra.ano_) {
        if (mes_ > outra.mes_) {
            return true;
        }
        else if (mes_ == outra.mes_) {
            return dia_ > outra.dia_;
        }
    }
    return false;
}
// Verifica se de >= ds = true
bool Data::operator>=(const Data& outra) const {
    if ((ano_ >= outra.ano_) && (mes_ >= outra.mes_) && (dia_ >= outra.dia_))
        return true;
 
    else 
        return false;
}
// Verifica se de == ds = true
bool Data::operator==(const Data& outra) const {
    if ((ano_ == outra.ano_) && (mes_ == outra.mes_) && (dia_ == outra.dia_))
        return true;

    else
        return false;
}
// Verifica se de != ds = true
bool Data::operator!=(const Data& outra) const {
	if ((ano_ != outra.ano_) || (mes_ != outra.mes_) || (dia_ != outra.dia_))
		return true;
	else
		return false;
}

// Métodos Auxiliares
// Verifica se o ano é bissexto
bool Data::dBissexto(int ano) const {
    return (ano % 4 == 0 && ano % 100 != 0)
        || (ano % 400 == 0);
}
// Verifica se a Data é válida
bool Data::dValida() const {
    if (mes_ < 1 || mes_ > 12 || dia_ < 1 || dia_ > 31)
        return false;

    // fevereiro
    if (mes_ == 2)   
        return dia_ <= (dBissexto(ano_) ? 29 : 28);

    // abril, junho, setembro, novembro } 30 dias
    if (mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) 
        return dia_ <= 30;

    return true;
}

// Imprimir Data no formato "DD/MM/AAAA"
string Data::toString() const {
    ostringstream oss;
    oss << getDia() << "/" << getMes() << "/" << getAno();
    return oss.str();
}