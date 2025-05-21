#ifndef HUESPED_H
#define HUESPED_H

#include "reserva.h"
class Huesped
{
private:
    unsigned char documentoHuesped[11];
    float puntuacion;
    unsigned char antiguedadMeses;
    Reserva** reservas;

public:
    Huesped(unsigned char (&documentoHuesped)[11], float p, unsigned char aM, Reserva **rH);
    Reserva** getReservas();
    void setReservas(Reserva** &nreservas);
    unsigned char* getDocumento();
    float getPuntuacion();
    unsigned char getAntiguedadMeses();
};

#endif // HUESPED_H
