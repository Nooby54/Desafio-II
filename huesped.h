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
    unsigned char tamReservas;
    Reserva **reservas;

public:
    Huesped(unsigned char (&documentoHuesped)[11], float p, unsigned char aM, unsigned char cReservas, Reserva **rH);
    Reserva **getReservas() const;
    void agregarReserva(Reserva *reserva, unsigned int &iteraciones);
    void eliminarReserva(unsigned int codigoReserva, unsigned int &iteraciones);
    unsigned char *getDocumento();
    float getPuntuacion();
    unsigned char getAntiguedadMeses();
    unsigned char getCantidadReservas() const;
    size_t tamanio();
};

#endif // HUESPED_H
