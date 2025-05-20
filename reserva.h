#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
using namespace std;
class Reserva
{
private:
    string anotaciones;
    Fecha fechaEntrada;
    Fecha fechaSalida;
    Fecha fechaPago;
    unsigned int monto;
    unsigned char *documentoHuesped;
    unsigned int *codigoAlojamiento;
    unsigned int codigoReserva;
    unsigned char duracion;
    bool metodoDePago;

public:
    Reserva(string notas,
            Fecha &fEntrada,
            Fecha &fSalida,
            Fecha &fPago,
            unsigned int m,
            unsigned char *dHuesped,
            unsigned int *cAlojamiento,
            unsigned int cReserva,
            unsigned char d,
            bool mPago);

    string getAnotaciones() const;
    Fecha getFechaEntrada() const;
    Fecha getFechaSalida() const;
    Fecha getFechaPago() const;
    unsigned int getMonto() const;
    unsigned char *getDocumentoHuesped() const;
    unsigned int *getCodigoAlojamiento() const;
    unsigned int getCodigoReserva() const;
    unsigned char getDuracion() const;
    bool getMetodoPago() const;

    ~Reserva();
};

#endif // RESERVA_H
