#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

class Fecha
{
private:
    unsigned char dia;
    unsigned char mes;
    unsigned short int anio;

    unsigned char obtenerDiasMes() const;

public:
    Fecha(const Fecha &otra);
    Fecha(unsigned char d, unsigned char m, unsigned short int a);
    ~Fecha();

    Fecha calcularFecha(unsigned short int dias, unsigned int &iteraciones);
    Fecha calcularFecha();
    string obtenerDiaSemana() const;
    string imprimirFecha() const;

    unsigned char getDia() const;
    unsigned short int getAnio() const;
    unsigned char getMes() const;

    Fecha &operator-=(unsigned char dias);
    Fecha &operator+=(unsigned char dias);
    Fecha &operator=(const Fecha &otra);
    Fecha &operator--();
    Fecha &operator++();

    bool operator==(const Fecha &otra) const;
    bool operator<(const Fecha &otra) const;
    bool operator>=(const Fecha &otra) const;
    bool operator<=(const Fecha &otra) const;
};

#endif // FECHA_H
