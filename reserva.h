/**
 * @file reserva.h
 * @brief Declaración de la clase Reserva que representa una reserva hecha por un huésped en un alojamiento.
 */


#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
using namespace std;

class Huesped;
class Alojamiento;


/**
 * @class Reserva
 * @brief Representa una reserva con fechas, monto, huésped y alojamiento asociados.
 */
class Reserva
{
private:
    string anotaciones;               /**< Notas o comentarios sobre la reserva. */
    Fecha fechaEntrada;               /**< Fecha de inicio de la reserva. */
    Fecha fechaSalida;                /**< Fecha de finalización de la reserva. */
    Fecha fechaPago;                  /**< Fecha en la que se realizó el pago. */
    unsigned int monto;               /**< Monto total de la reserva. */
    Huesped *huespedReserva;         /**< Puntero al huésped que realizó la reserva. */
    Alojamiento *alojamientoReserva; /**< Puntero al alojamiento reservado. */
    unsigned int codigoReserva;      /**< Código identificador único de la reserva. */
    unsigned char duracion;           /**< Duración de la reserva en días. */
    bool metodoDePago;                /**< Método de pago (true/false según el sistema definido). */

public:

    /**
     * @brief Constructor de la clase Reserva.
     * @param notas Anotaciones o comentarios de la reserva.
     * @param fEntrada Fecha de entrada (inicio de la reserva).
     * @param fSalida Fecha de salida (fin de la reserva).
     * @param fPago Fecha en la que se realizó el pago.
     * @param m Monto total de la reserva.
     * @param hReserva Puntero al huésped que realiza la reserva.
     * @param aReserva Puntero al alojamiento reservado.
     * @param cReserva Código identificador único de la reserva.
     * @param d Duración de la reserva en días.
     * @param mPago Método de pago utilizado.
     */
    Reserva(string notas,
            Fecha &fEntrada,
            Fecha &fSalida,
            Fecha &fPago,
            unsigned int m,
            Huesped *hReserva,
            Alojamiento *aReserva,
            unsigned int cReserva,
            unsigned char d,
            bool mPago);


    /**
     * @brief Obtiene las anotaciones de la reserva.
     * @return Cadena con las anotaciones.
     */
    string getAnotaciones() const;

    /**
     * @brief Obtiene la fecha de entrada de la reserva.
     * @return Objeto Fecha con la fecha de inicio.
     */
    Fecha getFechaEntrada() const;


    /**
     * @brief Obtiene la fecha de salida de la reserva.
     * @return Objeto Fecha con la fecha de fin.
     */
    Fecha getFechaSalida() const;

    /**
     * @brief Obtiene la fecha en que se realizó el pago.
     * @return Objeto Fecha con la fecha de pago.
     */
    Fecha getFechaPago() const;

    /**
     * @brief Obtiene el monto total de la reserva.
     * @return Monto en valor entero sin signo.
     */
    unsigned int getMonto() const;

    /**
     * @brief Obtiene el puntero al huésped asociado a la reserva.
     * @return Puntero a Huesped.
     */
    Huesped *getHuesped() const;

    /**
     * @brief Establece el huésped asociado a la reserva.
     * @param huesped Puntero a un objeto Huesped.
     */
    void setHuesped(Huesped *huesped);

    /**
     * @brief Obtiene el puntero al alojamiento reservado.
     * @return Puntero a Alojamiento.
     */
    Alojamiento *getAlojamientoReserva() const;

    /**
     * @brief Obtiene el código identificador único de la reserva.
     * @return Código entero sin signo.
     */
    unsigned int getCodigoIdentificador() const;

    /**
     * @brief Obtiene la duración de la reserva en días.
     * @return Duración en número de días.
     */
    unsigned char getDuracion() const;

    /**
     * @brief Obtiene el método de pago usado para la reserva.
     * @return Booleano indicando el método de pago.
     */
    bool getMetodoPago() const;

    /**
     * @brief Destructor de la clase Reserva.
     */
    ~Reserva();

    /**
     * @brief Calcula el tamaño en bytes que ocupa la reserva en memoria.
     * @return Tamaño total en bytes.
     */
    size_t tamanio();
};

#endif // RESERVA_H
