#include "anfitrion.h"


Anfitrion::Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, unsigned char cAl, Alojamiento** alojamientos)
    : puntuacion(p), antiguedadMeses(antiguedad), cantidadAlojamientos(cAl), alojamientos(alojamientos)
{
    for (unsigned char i = 0; i < 11; i++)
        documentoAnfitrion[i] = documento[i];
}


Anfitrion::~Anfitrion() {}


unsigned char* Anfitrion::getDocumentoAnfitrion() { return documentoAnfitrion; }
float Anfitrion::getPuntuacion() const { return puntuacion; }
unsigned char Anfitrion::getAntiguedadMeses() const { return antiguedadMeses; }
unsigned char Anfitrion::getCantidadAlojamientos() const {return cantidadAlojamientos;}
Alojamiento** Anfitrion::getAlojamientos() const { return alojamientos; }


void Anfitrion::setAlojamientos(Alojamiento** nuevosAlojamientos)
{
    alojamientos = nuevosAlojamientos;
}
