/**
 * @file anfitrion.h
 * @brief Declaración de la clase Anfitrion, que representa a un anfitrión en el sistema de alojamiento.
 */

#ifndef ANFITRION_H
#define ANFITRION_H

#include "fecha.h"

/**
 * @class Anfitrion
 * @brief Representa un anfitrión que gestiona uno o más alojamientos.
 *
 * Contiene información personal y de gestión de alojamientos, como el documento identificador,
 * la puntuación que ha recibido, su antigüedad en la plataforma y los alojamientos registrados.
 */

class Alojamiento;

class Anfitrion
{
private:
    unsigned char documentoAnfitrion[11];     /**< Documento del anfitrión (10 dígitos + nulo). */
    float puntuacion;                         /**< Puntuación promedio otorgada al anfitrión. */
    unsigned char antiguedadMeses;            /**< Antigüedad del anfitrión en meses. */
    unsigned char cantidadAlojamientos;       /**< Número de alojamientos registrados. */
    Alojamiento **alojamientos;               /**< Puntero al arreglo de alojamientos del anfitrión. */

public:

    /**
     * @brief Constructor de la clase Anfitrion.
     *
     * @param documento Documento identificador (10 dígitos).
     * @param p Puntuación inicial.
     * @param antiguedad Antigüedad en meses.
     * @param cAl Cantidad de alojamientos registrados.
     * @param alojamientos Puntero a los alojamientos registrados.
     */
    Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, unsigned char cAl, Alojamiento **alojamientos);

    /**
     * @brief Destructor de la clase Anfitrion.
     *
     * Libera la memoria asociada a los alojamientos si aplica.
     */
    ~Anfitrion();

    /// @return Puntero al documento identificador del anfitrión.
    unsigned char *getDocumento();

    /// @return Puntuación del anfitrión.
    float getPuntuacion() const;

    /// @return Antigüedad del anfitrión en meses.
    unsigned char getAntiguedadMeses() const;

    /// @return Cantidad de alojamientos gestionados por el anfitrión.
    unsigned char getCantidadAlojamientos() const;

    /// @return Puntero al arreglo de alojamientos del anfitrión.
    Alojamiento **getAlojamientos() const;

    /**
     * @brief Establece un nuevo arreglo de alojamientos para el anfitrión.
     * @param nuevosAlojamientos Puntero al nuevo arreglo de alojamientos.
     */
    void setAlojamientos(Alojamiento **nuevosAlojamientos);

    /**
     * @brief Consulta las reservas de todos los alojamientos del anfitrión en un rango de fechas.
     *
     * @param fechaInicio Fecha de inicio del intervalo.
     * @param fechaFin Fecha de fin del intervalo.
     * @param iteraciones Referencia a un contador de iteraciones para análisis de complejidad.
     */
    void consultarReservas(Fecha fechaInicio, Fecha fechaFin, unsigned int &iteraciones);

    /**
     * @brief Calcula el tamaño en memoria del objeto Anfitrion.
     *
     * @return Tamaño aproximado en bytes.
     */
    size_t tamanio();
};

#endif // ANFITRION_H
