#ifndef HUESPED_H
#define HUESPED_H

#include "reserva.h"
class Huesped
{
private:
    unsigned char documentoHuesped[11];
    float puntuacion;
    unsigned char antiguedadMeses;
    unsigned char cantidadReservas;
    Reserva** reservas;

public:
    Huesped(unsigned char (&documentoHuesped)[11], float p, unsigned char aM, unsigned char cReservas, Reserva **rH);
    Reserva** getReservas() const;
    void setReservas(Reserva** &nreservas);
    void eliminarReserva(unsigned int codigoReserva);
    unsigned char* getDocumento();
    float getPuntuacion();
    unsigned char getAntiguedadMeses();
    unsigned char getCantidadReservas() const;
};

#endif // HUESPED_H
