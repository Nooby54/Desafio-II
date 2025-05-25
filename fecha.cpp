#include "fecha.h"

#include <iostream>

using namespace std;


Fecha::Fecha(const Fecha& otra) : dia(otra.dia), mes(otra.mes), anio(otra.anio) {}

Fecha::Fecha(unsigned char d, unsigned char m, unsigned short int a)
    : dia(d), mes(m), anio(a) {}


Fecha::~Fecha() {}


Fecha Fecha::calcularFechaDias(const Fecha& fechaBase, unsigned short int dias) 
{
    Fecha nuevaFecha = fechaBase;

    if (dias > 0)
        nuevaFecha += dias;
    else if (dias < 0)
        nuevaFecha -= -dias;

    return nuevaFecha;
}




unsigned char Fecha::obtenerDiasMes() const
{
    switch (mes)
    {
    case 2: return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) ? 29 : 28;
    case 4: case 6: case 9: case 11: return 30;
    default: return 31;
    }
}


string Fecha::obtenerDiaSemana() const
{
    int a = anio, m = mes, d = dia;
    if (m < 3) { m += 12; a--; }
    int k = a % 100;
    int j = a / 100;
    int h = (d + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;

    string diasSemana[] = {"Sabado", "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};
    return diasSemana[h];
}

string Fecha::imprimirFecha() const
{
    static string nombresMes[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                                       "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    string nombreDia = obtenerDiaSemana();

    return nombreDia + ", " + to_string(dia) + " de " + nombresMes[mes - 1] + " del " + to_string(anio);
}




unsigned char Fecha::getDia() const { return dia; }
unsigned short int Fecha::getAnio() const { return anio; }
unsigned char Fecha::getMes() const { return mes; }


Fecha& Fecha::operator+=(unsigned char dias)
{
    dia += dias;

    while (true)
    {
        unsigned char diasMes = obtenerDiasMes();
        if (dia <= diasMes) break;

        dia -= diasMes;
        mes++;
        if (mes > 12)
        {
            mes = 1;
            anio++;
        }
    }
    return *this;
}


Fecha& Fecha::operator-=(unsigned char dias)
{
    while (dias >= dia)
    {
        dias -= dia;
        mes--;

        if (mes < 1)
        {
            mes = 12;
            anio--;
        }

        dia = obtenerDiasMes();
    }

    dia -= dias;
    return *this;
}


Fecha& Fecha::operator=(const Fecha& otra)
{
    if (this != &otra)
    {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;
}


Fecha& Fecha::operator--() { return (*this -= 1); }
Fecha& Fecha::operator++() { return (*this += 1); }


bool Fecha::operator==(const Fecha& otra) const
{
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

bool Fecha::operator<(const Fecha& otra) const
{
    return (anio < otra.anio) || (anio == otra.anio && mes < otra.mes) || (anio == otra.anio && mes == otra.mes && dia < otra.dia);
}

bool Fecha::operator>=(const Fecha& otra) const
{
    return !(*this < otra);
}

bool Fecha::operator<=(const Fecha& otra) const
{
    return (*this < otra || *this == otra);
}
