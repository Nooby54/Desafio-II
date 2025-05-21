#include "huesped.h"

Huesped::Huesped(unsigned char (&dH)[11], float p, unsigned char aM, Reserva** rH):
    puntuacion(p), antiguedadMeses(aM), reservas(rH){
    memcpy(documentoHuesped,dH,11);
}

Reserva **Huesped::getReservas(){
    return reservas;
}
void Huesped::setReservas(Reserva** &nReservas){
    reservas = nReservas;
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
