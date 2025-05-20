#include "reserva.h"
#include <iostream>
using namespace std;

Reserva::Reserva(string notas, Fecha& fEntrada, Fecha& fSalida, Fecha& fPago, unsigned int m,
        unsigned char* dHuesped, unsigned char* cAlojamiento, unsigned char* cReserva,
        unsigned char d, bool mPago):
    fechaEntrada(fEntrada), fechaSalida(fSalida), fechaPago(fPago), duracion(d),
    codigoReserva(cReserva), codigoAlojamiento(cAlojamiento), documentoHuesped(dHuesped),
    anotaciones(notas), metodoDePago(mPago), monto(m){}

Fecha Reserva::getFechaEntrada() const {
    return fechaEntrada;
}
unsigned char Reserva::getDuracion() const{
    return duracion;
}
Fecha Reserva::getFechaSalida() const{
    return fechaSalida;
}

unsigned char* Reserva::getCodigoAlojamiento() const{
    cout << codigoAlojamiento << endl;
    return codigoAlojamiento;
}

unsigned char* Reserva::getDocumentoHuesped() const{
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

Reserva::~Reserva(){}

