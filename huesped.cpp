#include "huesped.h"

Huesped::Huesped(unsigned char* dH, float p, unsigned char aM, Reserva* rH):
    documentoHuesped(dH),puntuacion(p), antiguedadMeses(aM), reservas(rH){}

Reserva* Huesped::getReservas(){
    return reservas;
}
void Huesped::setReservas(Reserva* &nReservas){
    reservas = nReservas;
}
unsigned char* Huesped::getDocumento(){
    return documentoHuesped;
}

unsigned char Huesped::getPuntuacion(){
    return puntuacion;
}
unsigned char Huesped::getAntiguedadMeses(){
    return antiguedadMeses;
}
/*
Reserva* redimensionarReserva(Reserva* reservasHuesped, unsigned char tamanio){
    Reserva* hola = new Reserva[ + tamanio]

}*/
