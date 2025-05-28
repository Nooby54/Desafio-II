#include "reserva.h"
using namespace std;

Reserva::Reserva(string notas,
                 Fecha &fEntrada,
                 Fecha &fSalida,
                 Fecha &fPago,
                 unsigned int m,
                 Huesped *dHuesped,
                 Alojamiento *aReserva,
                 unsigned int cReserva,
                 unsigned char d,
                 bool mPago) : anotaciones(notas), fechaEntrada(fEntrada), fechaSalida(fSalida), fechaPago(fPago),
                               monto(m), huespedReserva(dHuesped), alojamientoReserva(aReserva),
                               codigoReserva(cReserva), duracion(d), metodoDePago(mPago) {}

string Reserva::getAnotaciones() const
{
    return anotaciones;
}

Fecha Reserva::getFechaEntrada() const
{
    return fechaEntrada;
}

Fecha Reserva::getFechaSalida() const
{
    return fechaSalida;
}

Fecha Reserva::getFechaPago() const
{
    return fechaPago;
}

unsigned int Reserva::getMonto() const
{
    return monto;
}

Huesped *Reserva::getHuesped() const
{
    return huespedReserva;
}

void Reserva::setHuesped(Huesped *huesped)
{
    huespedReserva = huesped;
}

Alojamiento *Reserva::getAlojamientoReserva() const
{
    return alojamientoReserva;
}

unsigned int Reserva::getCodigoIdentificador() const
{
    return codigoReserva;
}

unsigned char Reserva::getDuracion() const
{
    return duracion;
}

bool Reserva::getMetodoPago() const
{
    return metodoDePago;
}

Reserva::~Reserva() {}

size_t Reserva::tamanio()
{
    /**
 * Calcula un estimado del tamaño en bytes que ocupa el objeto Reserva en memoria.
 * Incluye capacidad de la cadena de anotaciones, objetos Fecha, y demás atributos básicos y punteros.
 *
 * @return Tamaño aproximado en bytes del objeto.
 */

    size_t tamanio = anotaciones.capacity() + 3*sizeof(Fecha) + sizeof(monto) + sizeof(huespedReserva) +
                     sizeof(alojamientoReserva) + sizeof(codigoReserva) + sizeof(duracion) + sizeof(metodoDePago);
    return tamanio;
}
