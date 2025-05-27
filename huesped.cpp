#include "huesped.h"

Huesped::Huesped(unsigned char (&dH)[11], float p, unsigned char aM, unsigned char cReservas, Reserva** rH):
    puntuacion(p), antiguedadMeses(aM), cantidadReservas(cReservas),reservas(rH){
    memcpy(documentoHuesped,dH,11);
}

Reserva **Huesped::getReservas() const{
    return reservas;
}

void Huesped::setReservas(Reserva** &nReservas){
    reservas = nReservas;
}

void Huesped::eliminarReserva(unsigned int codigoReserva){
    unsigned char k = 0;
    for(unsigned int i = 0; i < cantidadReservas; i++){
        if(reservas[i]->getCodigoIdentificador() == codigoReserva){
            reservas[i] = nullptr;
        }
        else{
            reservas[k] = reservas[i];
            k++;
        }
    }
    cantidadReservas = k;
}

unsigned char* Huesped::getDocumento(){
    return documentoHuesped;
}

float Huesped::getPuntuacion(){
    return puntuacion;
}

unsigned char Huesped::getAntiguedadMeses(){
    return antiguedadMeses;
}

unsigned char Huesped::getCantidadReservas() const{
    return cantidadReservas;
}
