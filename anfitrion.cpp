#include "anfitrion.h"
#include "alojamiento.h"
#include "huesped.h"

#include<iostream>
using namespace std;

Anfitrion::Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, unsigned char cAl, Alojamiento **alojamientos)
    : puntuacion(p), antiguedadMeses(antiguedad), cantidadAlojamientos(cAl), alojamientos(alojamientos)
{
    memcpy(documentoAnfitrion, documento, 11*sizeof(char));
}

Anfitrion::~Anfitrion() {}

unsigned char *Anfitrion::getDocumento() { return documentoAnfitrion; }
float Anfitrion::getPuntuacion() const { return puntuacion; }
unsigned char Anfitrion::getAntiguedadMeses() const { return antiguedadMeses; }
unsigned char Anfitrion::getCantidadAlojamientos() const { return cantidadAlojamientos; }
Alojamiento **Anfitrion::getAlojamientos() const { return alojamientos; }
void Anfitrion::setAlojamientos(Alojamiento **nuevosAlojamientos)
{
    alojamientos = nuevosAlojamientos;
}

void Anfitrion::consultarReservas(Fecha fechaInicio, Fecha fechaFin, unsigned int &iteraciones)
{
    /**
 * @brief Consulta y muestra reservas dentro de un rango de fechas.
 *
 * Recorre todos los alojamientos del anfitrión y sus reservas vigentes.
 * Si la fecha de entrada de una reserva está entre `fechaInicio` y `fechaFin`, se imprime la información detallada.
 *
 * @param fechaInicio Fecha de inicio del rango de búsqueda.
 * @param fechaFin Fecha de fin del rango de búsqueda.
 * @param iteraciones Variable de conteo para medir el número de iteraciones realizadas (útil para análisis de eficiencia).
 */

    // Recorre todos los alojamientos del anfitrión
    for (unsigned int i = 0; i < cantidadAlojamientos; i++)
    {
        iteraciones++;
        for (unsigned char r = 0; r < this->alojamientos[i]->getCantidadReservas(); r++)
        {
            iteraciones++;
            Reserva *reserva = this->alojamientos[i]->getReservasVigentes()[r];
            if (reserva->getFechaEntrada() >= fechaInicio && reserva->getFechaEntrada() <= fechaFin)
            {
                cout << "------------------------\n";
                cout << "Reserva #" << reserva->getCodigoIdentificador() << "\n";

                // Alojamiento
                Alojamiento *a = reserva->getAlojamientoReserva();
                if (a != nullptr)
                {
                    cout << "  Alojamiento: " << a->getNombreAlojamiento() << "\n";
                }
                else
                {
                    cout << "  Alojamiento: No asignado\n";
                }

                // Huésped
                Huesped *h = reserva->getHuesped();
                if (h != nullptr)
                {
                    cout << "  Huesped: ";
                    unsigned char *docHuesped = h->getDocumento();
                    for (int j = 0; j < 11; ++j)
                    {
                        cout << docHuesped[j];
                    }
                    cout << "\n";
                }
                else
                {
                    cout << "  Huesped: [no asignado aun]\n";
                }

                // Fechas
                cout << "  Fecha de Entrada: " << reserva->getFechaEntrada().imprimirFecha() << "\n";
                cout << "  Fecha de Salida : " << reserva->getFechaSalida().imprimirFecha() << "\n";
                cout << "  Fecha de Pago   : " << reserva->getFechaPago().imprimirFecha() << "\n";

                // Otros datos
                cout << "  Duracion        : " << static_cast<int>(reserva->getDuracion()) << " noches\n";
                cout << "  Monto           : $" << reserva->getMonto() << "\n";
                cout << "  Metodo de Pago  : " << (reserva->getMetodoPago() ? "Tarjeta" : "Efectivo") << "\n";
                cout << "  Anotaciones     : " << reserva->getAnotaciones() << "\n";
                cout << "------------------------\n\n";
            }
        }
    }
}

size_t Anfitrion::tamanio()
{
    /**
 * @brief Calcula el tamaño aproximado en memoria del objeto Anfitrion.
 *
 * Suma el tamaño de todos los atributos del anfitrión, incluyendo el arreglo de punteros a alojamientos.
 * Este cálculo es útil para propósitos de serialización o análisis de uso de memoria.
 *
 * @return Tamaño en bytes del objeto.
 */
    size_t tamanio = (sizeof(char)*11) + sizeof(puntuacion) + sizeof(antiguedadMeses) +
                     sizeof(cantidadAlojamientos) + sizeof(alojamientos) +
                     (sizeof(Alojamiento*)*cantidadAlojamientos);
    return tamanio;
}
