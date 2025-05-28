/**
 * @file huesped.h
 * @brief Declaración de la clase Huesped que representa a un huésped del sistema de reservas.
 */

#ifndef HUESPED_H
#define HUESPED_H

#include "reserva.h"

/**
 * @class Huesped
 * @brief Representa a un huésped con historial de reservas, puntuación y antigüedad.
 */
class Huesped
{
private:
    unsigned char documentoHuesped[11];   /**< Documento del huésped (10 dígitos + nulo). */
    float puntuacion;                     /**< Puntuación promedio del huésped. */
    unsigned char antiguedadMeses;        /**< Antigüedad del huésped en meses. */
    unsigned char cantidadReservas;       /**< Número de reservas activas. */
    unsigned char tamReservas;            /**< Tamaño del arreglo de reservas. */
    Reserva **reservas;                   /**< Arreglo dinámico de punteros a reservas. */

public:

    /**
     * @brief Constructor de la clase Huesped.
     * @param documentoHuesped Arreglo de 10 caracteres con el documento del huésped.
     * @param p Puntuación inicial.
     * @param aM Antigüedad en meses.
     * @param cReservas Cantidad inicial de reservas.
     * @param rH Arreglo de punteros a reservas.
     */
    Huesped(unsigned char (&documentoHuesped)[11], float p, unsigned char aM, unsigned char cReservas, Reserva **rH);

    /**
     * @brief Obtiene el arreglo de reservas del huésped.
     * @return Arreglo de punteros a reservas.
     */
    Reserva **getReservas() const;

    /**
     * @brief Agrega una nueva reserva al arreglo de reservas.
     * @param reserva Puntero a la nueva reserva.
     * @param iteraciones Referencia para contar las iteraciones realizadas.
     */
    void agregarReserva(Reserva *reserva, unsigned int &iteraciones);

    /**
     * @brief Elimina una reserva del arreglo de reservas.
     * @param codigoReserva Código identificador de la reserva a eliminar.
     * @param iteraciones Referencia para contar las iteraciones realizadas.
     */
    void eliminarReserva(unsigned int codigoReserva, unsigned int &iteraciones);

    /**
     * @brief Obtiene el documento del huésped.
     * @return Puntero al arreglo de caracteres del documento.
     */
    unsigned char *getDocumento();

    /**
     * @brief Obtiene la puntuación del huésped.
     * @return Puntuación como número flotante.
     */
    float getPuntuacion();

    /**
     * @brief Obtiene la antigüedad del huésped en meses.
     * @return Número de meses de antigüedad.
     */
    unsigned char getAntiguedadMeses();

    /**
     * @brief Obtiene la cantidad de reservas activas.
     * @return Número de reservas.
     */
    unsigned char getCantidadReservas() const;

    /**
     * @brief Calcula el tamaño en bytes que ocupa el huésped en memoria.
     * @return Tamaño total en bytes.
     */
    size_t tamanio();
};

#endif // HUESPED_H
