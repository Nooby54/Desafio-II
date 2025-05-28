/**
 * @file fecha.h
 * @brief Declaración de la clase Fecha que gestiona operaciones y comparaciones entre fechas.
 */

#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

/**
 * @class Fecha
 * @brief Representa una fecha con día, mes y año, e incluye operaciones y validaciones sobre fechas.
 */

class Fecha
{
private:
    unsigned char dia;                  /**< Día de la fecha. */
    unsigned char mes;                  /**< Mes de la fecha. */
    unsigned short int anio;            /**< Año de la fecha. */


    /**
     * @brief Obtiene el número de días del mes actual considerando el año (para años bisiestos).
     * @return Días del mes actual.
     */
    unsigned char obtenerDiasMes() const;

public:

    /**
     * @brief Constructor por copia.
     * @param otra Referencia a otra instancia de Fecha.
     */
    Fecha(const Fecha &otra);

    /**
     * @brief Constructor con parámetros.
     * @param d Día.
     * @param m Mes.
     * @param a Año.
     */
    Fecha(unsigned char d, unsigned char m, unsigned short int a);


    /**
     * @brief Destructor de la clase Fecha.
     */
    ~Fecha();

    /**
     * @brief Calcula una nueva fecha a partir de la actual sumando una cantidad de días.
     * @param dias Cantidad de días a sumar.
     * @param iteraciones Referencia a un contador para registrar iteraciones realizadas.
     * @return Nueva fecha calculada.
     */
    Fecha calcularFecha(unsigned short int dias, unsigned int &iteraciones);

    /**
     * @brief Calcula una nueva fecha sumando un día.
     * @return Nueva fecha con un día adicional.
     */
    Fecha calcularFecha();

    /**
     * @brief Devuelve el nombre del día de la semana correspondiente a la fecha.
     * @return Nombre del día (por ejemplo, "Lunes", "Martes", etc.).
     */
    string obtenerDiaSemana() const;

    /**
     * @brief Devuelve la fecha como cadena con formato dd/mm/aaaa.
     * @return Cadena con la fecha formateada.
     */
    string imprimirFecha() const;

    /// @return Día de la fecha.
    unsigned char getDia() const;

    /// @return Año de la fecha.
    unsigned short int getAnio() const;

    /// @return Mes de la fecha.
    unsigned char getMes() const;

    /**
     * @brief Resta una cantidad de días a la fecha actual.
     * @param dias Días a restar.
     * @return Referencia a la fecha modificada.
     */
    Fecha &operator-=(unsigned char dias);

    /**
     * @brief Suma una cantidad de días a la fecha actual.
     * @param dias Días a sumar.
     * @return Referencia a la fecha modificada.
     */
    Fecha &operator+=(unsigned char dias);

    /**
     * @brief Asigna una fecha a otra.
     * @param otra Fecha fuente.
     * @return Referencia a la fecha actual.
     */
    Fecha &operator=(const Fecha &otra);

    /**
     * @brief Operador de pre-decremento (resta un día).
     * @return Referencia a la fecha modificada.
     */
    Fecha &operator--();

    /**
     * @brief Operador de pre-incremento (suma un día).
     * @return Referencia a la fecha modificada.
     */
    Fecha &operator++();

    /**
     * @brief Compara si dos fechas son iguales.
     * @param otra Fecha a comparar.
     * @return true si las fechas son iguales.
     */
    bool operator==(const Fecha &otra) const;

    /**
     * @brief Compara si la fecha actual es menor que otra.
     * @param otra Fecha a comparar.
     * @return true si la fecha actual es menor.
     */
    bool operator<(const Fecha &otra) const;

    /**
     * @brief Compara si la fecha actual es mayor o igual a otra.
     * @param otra Fecha a comparar.
     * @return true si la fecha actual es mayor o igual.
     */
    bool operator>=(const Fecha &otra) const;

    /**
     * @brief Compara si la fecha actual es menor o igual a otra.
     * @param otra Fecha a comparar.
     * @return true si la fecha actual es menor o igual.
     */
    bool operator<=(const Fecha &otra) const;
};

#endif // FECHA_H
