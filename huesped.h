#ifndef HUESPED_H
#define HUESPED_H

#include "reserva.h"
class Huesped
{
private:
    unsigned char* documentoHuesped;
    float puntuacion;
    unsigned char antiguedadMeses;
    Reserva* reservas;
public:
    Huesped(unsigned char* dH, float p, unsigned char aM, Reserva* rH = nullptr);
    Reserva* getReservas();
    void setReservas(Reserva* &nreservas);
    unsigned char* getDocumento();
    unsigned char getPuntuacion();
    unsigned char getAntiguedadMeses();
    Reserva* redimensionarReserva(Reserva* reservasHuesped, unsigned char tamaño) const;
};

#endif // HUESPED_H
