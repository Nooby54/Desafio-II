#include "anfitrion.h"


Anfitrion::Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, Alojamiento** alojamientos)
    : puntuacion(p), antiguedadMeses(antiguedad), alojamientos(alojamientos)
{
    for (unsigned char i = 0; i < 11; i++)
        documentoAnfitrion[i] = documento[i];
}


Anfitrion::~Anfitrion() {}


unsigned char* Anfitrion::getDocumentoAnfitrion() { return documentoAnfitrion; }
float Anfitrion::getPuntuacion() const { return puntuacion; }
unsigned char Anfitrion::getAntiguedadMeses() const { return antiguedadMeses; }
Alojamiento** Anfitrion::getAlojamientos() const { return alojamientos; }


void Anfitrion::setAlojamientos(Alojamiento** nuevosAlojamientos)
{
    alojamientos = nuevosAlojamientos;
}
