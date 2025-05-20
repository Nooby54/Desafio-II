#ifndef FECHA_H
#define FECHA_H

#include <string>
class Fecha
{
private:
    unsigned char dia;
    unsigned char mes;
    unsigned int anio;

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

    Fecha(unsigned char d, unsigned char m, unsigned int a)
        : dia(d), mes(m), anio(a) {}
    ~Fecha(){}



    Fecha calcularFechaDias(const Fecha& inicio, unsigned char dias)const
    {
        Fecha nuevaFecha = inicio;
        nuevaFecha.dia += dias;

        while (nuevaFecha.dia > obtenerDiasMes(nuevaFecha.mes, nuevaFecha.anio))
        {
            nuevaFecha.dia -= obtenerDiasMes(nuevaFecha.mes, nuevaFecha.anio);
            nuevaFecha.mes++;
            if (nuevaFecha.mes > 12)
            {
                nuevaFecha.mes = 1;
                nuevaFecha.anio++;
            }
        }
        return nuevaFecha;
    }

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


    unsigned char getAnio() const
    {
        return anio;
    }

    Fecha operator=(Fecha& otra) const
    {
        return Fecha(otra.dia, otra.mes, otra.anio);
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
