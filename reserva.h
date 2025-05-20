#ifndef RESERVA_H
#define RESERVA_H

#include "fecha.h"
#include <string>
using namespace std;
class Reserva
{
private:
    Fecha fechaEntrada,fechaSalida,fechaPago;
    unsigned char duracion;
    string codigoReserva,codigoAlojamiento,documentoHuesped,anotaciones;
    bool metodoDePago;
    unsigned int monto;

public:
    Reserva(Fecha& fEntrada, unsigned char d, Fecha& fSalida,
            string cReserva, string& cAlojamiento,
            string& dHuesped, bool mPago,
            Fecha& fPago, unsigned int m, string notas);

    Fecha getFechaEntrada() const;
    unsigned char getDuracion() const;
    Fecha getFechaSalida() const;
    string getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;
    bool getMetodoPago() const;
    Fecha getFechaPago() const;
    unsigned int getMonto() const;
    string getAnotaciones() const;
    Reserva operator= (Reserva&) const;
    ~Reserva();
};

#endif // RESERVA_H
