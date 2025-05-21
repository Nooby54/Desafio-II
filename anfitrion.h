#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>

class Alojamiento;

class Anfitrion
{
private:

    unsigned char documentoAnfitrion[11];
    float puntuacion;
    unsigned char antiguedadMeses;
    Alojamiento** alojamientos;

public:
    Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, Alojamiento** alojamientos)
        : puntuacion(p), antiguedadMeses(antiguedad), alojamientos(alojamientos)
    {
        for (unsigned char i = 0; i < 11; i++)
            documentoAnfitrion[i] = documento[i];
    }

    ~Anfitrion() {}

    unsigned char* getDocumentoAnfitrion() { return documentoAnfitrion; }
    float getPuntuacion() const { return puntuacion; }
    unsigned char getAntiguedadMeses() const { return antiguedadMeses; }
    Alojamiento** getAlojamientos() const { return alojamientos; }

    void setAlojamientos(Alojamiento** nuevosAlojamientos)
    {
        alojamientos = nuevosAlojamientos;
    }
};

#endif // ANFITRION_H
