#include "reserva.h"
using namespace std;

Reserva::Reserva(string notas,
                 Fecha &fEntrada,
                 Fecha &fSalida,
                 Fecha &fPago,
                 unsigned int m,
                 unsigned char *dHuesped,
                 unsigned int *cAlojamiento,
                 unsigned int cReserva,
                 unsigned char d,
                 bool mPago) : anotaciones(notas), fechaEntrada(fEntrada), fechaSalida(fSalida), fechaPago(fPago),
                               monto(m), documentoHuesped(dHuesped), codigoAlojamiento(cAlojamiento),
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

unsigned char *Reserva::getDocumentoHuesped() const
{
    return documentoHuesped;
}

unsigned int *Reserva::getCodigoAlojamiento() const
{
    return codigoAlojamiento;
}

unsigned int Reserva::getCodigoReserva() const
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
