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

size_t Huesped::tamanio(){
    size_t tamanio = (sizeof(char)*11) + sizeof(puntuacion) + sizeof(antiguedadMeses) + sizeof(cantidadReservas) +
                     sizeof(tamReservas) + sizeof(reservas) + (sizeof(Reserva*) * tamReservas);
    return tamanio;
}
