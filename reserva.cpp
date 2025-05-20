#include "reserva.h"

Reserva::Reserva(Fecha& fEntrada, unsigned char d, Fecha& fSalida,
                 string cReserva, string& cAlojamiento,
                 string& dHuesped, bool mPago,
                 Fecha& fPago, unsigned int m, string notas):fechaEntrada(fEntrada),
    duracion(d),fechaSalida(fSalida),codigoReserva(cReserva), codigoAlojamiento(cAlojamiento),
    documentoHuesped(dHuesped), metodoDePago(mPago), fechaPago(fPago), monto(m), anotaciones(notas){}
Fecha Reserva::getFechaEntrada() const {
    return fechaEntrada;
}
unsigned char Reserva::getDuracion() const{
    return duracion;
}
Fecha Reserva::getFechaSalida() const{
    return fechaSalida;
}

string Reserva::getCodigoAlojamiento() const{
    return codigoAlojamiento;
}

string Reserva::getDocumentoHuesped() const{
    return documentoHuesped;
}

bool Reserva::getMetodoPago() const {
    return metodoDePago;
}

Fecha Reserva::getFechaPago() const{
    return fechaPago;
}
unsigned int Reserva::getMonto() const{
    return monto;}

string Reserva::getAnotaciones() const{
    return anotaciones;}

Reserva Reserva::operator= (Reserva& reserva) const {
    return Reserva(reserva.fechaEntrada, reserva.duracion,reserva.fechaSalida,reserva.codigoReserva,
                   reserva.codigoAlojamiento,reserva.documentoHuesped,reserva.metodoDePago,reserva.fechaPago,
                   reserva.monto,reserva.anotaciones);
}
Reserva::~Reserva(){
    //delete[] this;
}

