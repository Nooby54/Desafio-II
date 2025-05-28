/**
 * @file alojamiento.h
 * @brief Declaración de la clase Alojamiento para el sistema de gestión de reservas.
 */


#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "reserva.h"
#include "anfitrion.h"

using namespace std;

/**
 * @class Alojamiento
 * @brief Representa un alojamiento registrado por un anfitrión en el sistema.
 *
 * Contiene toda la información relevante de un alojamiento, incluyendo su ubicación,
 * tipo, precio por noche, amenidades, y las reservas asociadas a él.
 */

class Alojamiento
{
private:
    string nombreAlojamiento;                  /**< Nombre del alojamiento. */
    unsigned int codigoIdentificador;         /**< Código único del alojamiento. */
    Anfitrion *anfitrionResponsable;          /**< Puntero al anfitrión responsable. */
    string departamento;                      /**< Departamento donde se ubica el alojamiento. */
    string municipio;                         /**< Municipio donde se ubica el alojamiento. */
    bool tipo;                                /**< Tipo del alojamiento (true = casa, false = habitación). */
    string direccion;                         /**< Dirección física del alojamiento. */
    unsigned int precioNoche;                 /**< Precio por noche en moneda local. */
    bool amenidades[5];                       /**< Arreglo que indica las amenidades disponibles (true/false). */
    Reserva **reservasVigentes;               /**< Arreglo de punteros a reservas vigentes. */
    unsigned char cantidadReservas;           /**< Número actual de reservas vigentes. */
    unsigned char tamReservas;                /**< Capacidad del arreglo de reservas. */

public:
    /**
     * @brief Constructor de la clase Alojamiento.
     *
     * @param nombre Nombre del alojamiento.
     * @param codigo Código identificador único.
     * @param anfitrion Puntero al anfitrión responsable.
     * @param depto Departamento del alojamiento.
     * @param mun Municipio del alojamiento.
     * @param tipoAloj Tipo de alojamiento.
     * @param dir Dirección física.
     * @param precio Precio por noche.
     * @param ameni Arreglo con las amenidades disponibles.
     * @param reservas Arreglo inicial de reservas vigentes.
     * @param cantidad Cantidad inicial de reservas.
     */
    Alojamiento(string nombre, unsigned int codigo, Anfitrion *anfitrion,
                string depto, string mun, bool tipoAloj, string dir,
                unsigned int precio, bool ameni[5], Reserva **reservas, unsigned char cantidad);


    /**
     * @brief Destructor de la clase Alojamiento.
     *
     * Libera la memoria ocupada por las reservas vigentes.
     */
    ~Alojamiento();

    /// @return Nombre del alojamiento.
    string getNombreAlojamiento() const;

    /// @return Código identificador del alojamiento.
    unsigned int getCodigoIdentificador() const;

    /// @return Puntero al anfitrión responsable.
    Anfitrion *getAnfitrionRespon() const;

    /**
     * @brief Establece el anfitrión responsable del alojamiento.
     * @param anfitrion Puntero al nuevo anfitrión.
     */
    void setAnfitrionResponsable(Anfitrion *anfitrion);

    /// @return Departamento del alojamiento.
    string getDepartamento() const;

    /// @return Municipio del alojamiento.
    string getMunicipio() const;

    /// @return Tipo del alojamiento
    bool getTipo() const;

    /// @return Dirección del alojamiento.
    string getDireccion() const;

    /// @return Precio por noche del alojamiento.
    unsigned int getPrecioNoche() const;

    /// @return Puntero al arreglo de amenidades del alojamiento.
    bool *getAmenidades();

    /// @return Arreglo de punteros a reservas vigentes.
    Reserva **getReservasVigentes() const;


    /**
     * @brief Elimina una reserva asociada al alojamiento.
     *
     * @param codigoReserva Código de la reserva a eliminar.
     * @param iteraciones Referencia a un contador de iteraciones para fines de análisis de complejidad.
     */
    void eliminarReserva(unsigned int codigoReserva, unsigned int &iteraciones);

    /**
     * @brief Agrega una nueva reserva al alojamiento.
     *
     * @param reserva Puntero a la nueva reserva.
     * @param iteraciones Referencia a un contador de iteraciones para fines de análisis de complejidad.
     */
    void agregarReserva(Reserva *reserva, unsigned int &iteraciones);

    /// @return Cantidad actual de reservas vigentes.
    unsigned char getCantidadReservas() const;

    /**
     * @brief Calcula el tamaño en memoria ocupado por el objeto `Alojamiento`.
     *
     * @return Tamaño aproximado en bytes.
     */
    size_t tamanio();
};

#endif // ALOJAMIENTO_H
