#ifndef FECHA_H
#define FECHA_H

#include <string>

class Fecha
{
private:
    unsigned char dia;
    unsigned char mes;
    unsigned short int anio;

    unsigned char obtenerDiasMes() const;

public:
    Fecha(const Fecha& otra);
    Fecha(unsigned char d, unsigned char m, unsigned short int a);
    ~Fecha();

    std::string obtenerDiaSemana() const;

    unsigned char getDia() const;
    unsigned short int getAnio() const;
    unsigned char getMes() const;

    Fecha& operator-=(unsigned char dias);
    Fecha& operator=(const Fecha& otra);
    Fecha& operator+=(unsigned char dias);
    Fecha& operator--();
    Fecha& operator++();

    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
};

#endif // FECHA_H

