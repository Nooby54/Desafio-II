#include "huesped.h"
#include "miscelaneos.h"

Huesped::Huesped(unsigned char (&dH)[11], float p, unsigned char aM, unsigned char cReservas, Reserva **rH) : puntuacion(p), antiguedadMeses(aM), cantidadReservas(cReservas), reservas(rH)
{
    tamReservas = cantidadReservas;
    memcpy(documentoHuesped, dH, 11 * sizeof(char));
}

Reserva **Huesped::getReservas() const
{
    return reservas;
}

void Huesped::agregarReserva(Reserva *reserva, unsigned int &iteraciones)
{
    /**
 * Agrega una nueva reserva al arreglo de reservas del huésped.
 * Si el arreglo está lleno, se redimensiona para ampliar su capacidad.
 *
 * @param reserva Puntero a la reserva que se agregará.
 * @param iteraciones Referencia a un contador de iteraciones para medir operaciones.
 */
    if (this->cantidadReservas == this->tamReservas)
    {
        redimensionarArreglo<Reserva>(this->reservas, this->tamReservas, this->tamReservas + 6, iteraciones);
        this->tamReservas += 6;
    }
    this->reservas[this->cantidadReservas] = reserva;
    this->cantidadReservas++;
}

void Huesped::eliminarReserva(unsigned int codigoReserva, unsigned int &iteraciones)
{
    /**
 * Elimina una reserva del huésped según su código identificador.
 * Se desplazan las reservas restantes para mantener el arreglo compacto.
 *
 * @param codigoReserva Código identificador de la reserva a eliminar.
 * @param iteraciones Referencia a un contador para medir operaciones realizadas.
 */
    unsigned char k = 0;
    for (unsigned int i = 0; i < cantidadReservas; i++)
    {
        iteraciones++;
        if (reservas[i]->getCodigoIdentificador() == codigoReserva)
        {
            reservas[i] = nullptr;
        }
        else
        {
            reservas[k] = reservas[i];
            k++;
        }
    }
    cantidadReservas = k;
}

unsigned char *Huesped::getDocumento()
{
    return documentoHuesped;
}

float Huesped::getPuntuacion()
{
    return puntuacion;
}

unsigned char Huesped::getAntiguedadMeses()
{
    return antiguedadMeses;
}

unsigned char Huesped::getCantidadReservas() const
{
    return cantidadReservas;
}

size_t Huesped::tamanio()
{
    /**
 * Calcula un estimado del tamaño en bytes que ocupa el objeto Huesped en memoria.
 * Considera campos básicos, punteros y arreglo dinámico de reservas.
 *
 * @return Tamaño aproximado en bytes del objeto.
 */
    size_t tamanio = (sizeof(char)*11) + sizeof(puntuacion) + sizeof(antiguedadMeses) + sizeof(cantidadReservas) +
                     sizeof(tamReservas) + sizeof(reservas) + (sizeof(Reserva*) * tamReservas);
    return tamanio;
}
