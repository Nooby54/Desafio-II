#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
using namespace std;

class Huesped;
class Alojamiento;
class Reserva
{
private:
    string anotaciones;
    Fecha fechaEntrada;
    Fecha fechaSalida;
    Fecha fechaPago;
    unsigned int monto;
    Huesped* huespedReserva;
    Alojamiento* alojamientoReserva;
    unsigned int codigoReserva;
    unsigned char duracion;
    bool metodoDePago;

public:
    Reserva(string notas,
            Fecha &fEntrada,
            Fecha &fSalida,
            Fecha &fPago,
            unsigned int m,
            Huesped* hReserva,
            Alojamiento* aReserva,
            unsigned int cReserva,
            unsigned char d,
            bool mPago);

    string getAnotaciones() const;
    Fecha getFechaEntrada() const;
    Fecha getFechaSalida() const;
    Fecha getFechaPago() const;
    unsigned int getMonto() const;
    Huesped *getHuesped() const;
    void setHuesped(Huesped* huesped);
    Alojamiento *getAlojamientoReserva() const;
    unsigned int getCodigoIdentificador() const;
    unsigned char getDuracion() const;
    bool getMetodoPago() const;

    ~Reserva();
};

#endif // RESERVA_H
