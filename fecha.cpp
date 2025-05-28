#include "fecha.h"

using namespace std;

Fecha::Fecha(const Fecha &otra) : dia(otra.dia), mes(otra.mes), anio(otra.anio) {}

Fecha::Fecha(unsigned char d, unsigned char m, unsigned short int a)
    : dia(d), mes(m), anio(a) {}

Fecha::~Fecha() {}

Fecha Fecha::calcularFecha(unsigned short int dias, unsigned int &iteraciones)
{
    /**
 * @brief Calcula una nueva fecha sumando una cantidad de días a la fecha actual.
 *
 * Crea una copia del objeto actual, le suma la cantidad de días especificada,
 * y devuelve la nueva fecha resultante.
 *
 * @param dias Cantidad de días que se desea sumar a la fecha actual.
 * @param iteraciones Referencia a una variable usada para contar operaciones (útil para métricas).
 *                    Se incrementa en la cantidad de días sumados.
 * @return Una nueva instancia de Fecha con la suma aplicada.
 */
    Fecha nuevaFecha = *this;
    iteraciones+=dias;
    nuevaFecha += dias;

    return nuevaFecha;
}

Fecha Fecha::calcularFecha()
{
    /**
 * @brief Calcula la fecha resultante de sumar un año a la fecha actual.
 *
 * Este método devuelve una nueva instancia de Fecha cuya fecha es un año
 * posterior a la del objeto actual. El objeto original no se modifica.
 *
 * @return Una nueva instancia de Fecha con el año incrementado en uno.
 */
    Fecha fechaMaxima = *this;
    fechaMaxima.anio+=1;

    return fechaMaxima;
}

unsigned char Fecha::obtenerDiasMes() const
{
    /**
 * @brief Retorna la cantidad de días del mes actual.
 *
 * Calcula cuántos días tiene el mes almacenado en el objeto actual,
 * considerando si el año es bisiesto en el caso de febrero.
 *
 * @return Cantidad de días del mes (28, 29, 30 o 31).
 */
    switch (mes)
    {
    case 2:
        return ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

string Fecha::obtenerDiaSemana() const
{
    /**
 * @brief Calcula el día de la semana correspondiente a la fecha.
 *
 * Usa la fórmula de Zeller para determinar el día de la semana,
 * donde el resultado es un índice que corresponde a un día
 * entre sábado y viernes.
 *
 * @return string con el nombre del día de la semana en español.
 */
    int a = anio, m = mes, d = dia;
    if (m < 3)
    {
        m += 12;
        a--;
    }
    int k = a % 100;
    int j = a / 100;
    int h = (d + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;

    string diasSemana[] = {"Sabado", "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};
    return diasSemana[h];
}

string Fecha::imprimirFecha() const
{
    /**
 * @brief Devuelve la fecha en formato legible con nombre del día y mes.
 *
 * El formato resultante es: "DíaSemana, Día de Mes del Año".
 * Ejemplo: "Lunes, 28 de Mayo del 2025".
 *
 * @return string con la fecha formateada.
 */
    static string nombresMes[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                                  "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    string nombreDia = obtenerDiaSemana();

    return nombreDia + ", " + to_string(dia) + " de " + nombresMes[mes - 1] + " del " + to_string(anio);
}

unsigned char Fecha::getDia() const { return dia; }
unsigned short int Fecha::getAnio() const { return anio; }
unsigned char Fecha::getMes() const { return mes; }

Fecha &Fecha::operator+=(unsigned char dias)
{
    /**
 * @brief Incrementa la fecha sumando una cantidad de días.
 *
 * La operación ajusta el día, mes y año correctamente si se supera
 * el número de días del mes actual, manejando el paso a meses y años siguientes.
 *
 * @param dias Cantidad de días a sumar (unsigned char).
 * @return Fecha& Referencia a la fecha actualizada.
 */
    dia += dias;

    while (true)
    {
        unsigned char diasMes = obtenerDiasMes();
        if (dia <= diasMes)
            break;

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

Fecha &Fecha::operator-=(unsigned char dias)
{
    /**
 * @brief Decrementa la fecha restando una cantidad de días.
 *
 * Ajusta día, mes y año correctamente si se resta más días de los que hay
 * en el mes actual, retrocediendo a meses y años anteriores según corresponda.
 *
 * @param dias Cantidad de días a restar (unsigned char).
 * @return Fecha& Referencia a la fecha actualizada.
 */
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

Fecha &Fecha::operator=(const Fecha &otra)
{
    /**
 * @brief Operador de asignación para copiar los valores de otra fecha.
 *
 * Copia día, mes y año de la fecha proporcionada a la instancia actual,
 * asegurando que no se copie a sí misma.
 *
 * @param otra Referencia a la fecha fuente para copiar.
 * @return Fecha& Referencia a la fecha actualizada.
 */

    if (this != &otra)
    {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;
}

Fecha &Fecha::operator--() { return (*this -= 1); } // Resta un día a la fecha (pre-decremento)
Fecha &Fecha::operator++() { return (*this += 1); } // Suma un día a la fecha (pre-incremento)

bool Fecha::operator==(const Fecha &otra) const
{
    /**
 * @brief Compara si dos fechas son iguales.
 *
 * Dos fechas son iguales si tienen el mismo día, mes y año.
 *
 * @param otra Fecha con la cual se compara.
 * @return true Si las fechas son iguales.
 * @return false En caso contrario.
 */
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

bool Fecha::operator<(const Fecha &otra) const
{
    /**
 * @brief Compara si la fecha actual es menor que otra fecha.
 *
 * La comparación se realiza primero por año, luego por mes y finalmente por día.
 *
 * @param otra Fecha con la cual se compara.
 * @return true Si la fecha actual es anterior a la fecha "otra".
 * @return false En caso contrario.
 */
    return (anio < otra.anio) || (anio == otra.anio && mes < otra.mes) || (anio == otra.anio && mes == otra.mes && dia < otra.dia);
}

bool Fecha::operator>=(const Fecha &otra) const
{
    /**
 * @brief Compara si la fecha actual es mayor o igual que otra fecha.
 *
 * Implementado como la negación de la comparación menor.
 *
 * @param otra Fecha con la cual se compara.
 * @return true Si la fecha actual es igual o posterior a la fecha "otra".
 * @return false En caso contrario.
 */

    return !(*this < otra);
}

bool Fecha::operator<=(const Fecha &otra) const
{
    /**
 * @brief Compara si la fecha actual es menor o igual que otra fecha.
 *
 *
 * @param otra Fecha con la cual se compara.
 * @return true Si la fecha actual es anterior o igual a la fecha "otra".
 * @return false En caso contrario.
 */
    return (*this < otra || *this == otra);
}
