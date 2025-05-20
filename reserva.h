#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
using namespace std;
class Reserva
{
private:
    Fecha fechaEntrada;
    Fecha fechaSalida;
    Fecha fechaPago;
    unsigned char duracion;
    unsigned char* codigoReserva;
    unsigned char* codigoAlojamiento;
    unsigned char* documentoHuesped;
    string anotaciones;
    bool metodoDePago;
    unsigned int monto;

public:

    Reserva(string notas, Fecha& fEntrada, Fecha& fSalida, Fecha& fPago, unsigned int m,
            unsigned char *dHuesped, unsigned char *cAlojamiento, unsigned char *cReserva,
            unsigned char d, bool metodoPago);

    Fecha getFechaEntrada() const;
    unsigned char getDuracion() const;
    Fecha getFechaSalida() const;
    unsigned char* getCodigoAlojamiento() const;
    unsigned char* getDocumentoHuesped() const;
    bool getMetodoPago() const;
    Fecha getFechaPago() const;
    unsigned int getMonto() const;
    string getAnotaciones() const;
    ~Reserva();
};

#endif // RESERVA_H
