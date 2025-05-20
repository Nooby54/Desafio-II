#ifndef FECHA_H
#define FECHA_H

#include <string>
class Fecha
{
private:
    unsigned char dia;
    unsigned char mes;
    unsigned short int anio;

    unsigned char obtenerDiasMes() const
    {
        switch (mes)
        {
        case 2: return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
        }
    }

public:

    Fecha(unsigned char d, unsigned char m, unsigned short int a)
        : dia(d), mes(m), anio(a) {}
    ~Fecha(){}


    std::string obtenerDiaSemana()const
    {
        int a = anio, m = mes, d = dia;
        if (m < 3) { m += 12; a--; }
        int k = a % 100;
        int j = a / 100;
        int h = (d + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;

        std::string diasSemana[] = {"Sábado", "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes"};
        return diasSemana[h];
    }


    unsigned char getDia() const
    {
        return dia;
    }

    unsigned short int getAnio() const
    {
        return anio;
    }
    unsigned char getMes() const
    {
        return mes;
    }
    Fecha& operator-=(unsigned char dias)
    {
        while (dias >= this->dia)
        {
            dias -= this->dia;
            this->mes--;

            if (this->mes < 1)
            {
                this->mes = 12;
                this->anio--;
            }

            this->dia = this->obtenerDiasMes();
        }

        this->dia -= dias;
        return *this;
    }


    Fecha& operator=(const Fecha& otra)
    {
        if (this != &otra)
        {
            this->dia = otra.dia;
            this->mes = otra.mes;
            this->anio = otra.anio;
        }
        return *this;
    }
    Fecha& operator+=(unsigned char dias)
    {
        this->dia += dias;

        while (true)
        {
            unsigned char diasMes = this->obtenerDiasMes();
            if (this->dia <= diasMes) break;

            this->dia -= diasMes;
            this->mes++;
            if (this->mes > 12)
            {
                this->mes = 1;
                this->anio++;
            }
        }
        return *this;
    }
    Fecha& operator--()
    {
        return (*this -= 1);
    }
    Fecha& operator++()
    {
        return (*this += 1);
    }

    bool operator==(const Fecha& otra) const
    {
        return dia == otra.dia && mes == otra.mes && anio == otra.anio;
    }
    bool operator<(const Fecha& otra) const
    {
        return (anio < otra.anio) || (anio == otra.anio && mes < otra.mes) || (anio == otra.anio && mes == otra.mes && dia < otra.dia);
    }
    bool operator>=(const Fecha& otra) const
    {
        return !(*this < otra);
    }
    bool operator<=(const Fecha& otra) const
    {
        return (*this < otra || *this == otra);
    }

};

#endif // FECHA_H
