#include "anfitrion.h"
#include "alojamiento.h"
#include "huesped.h"
#include <iostream>


Anfitrion::Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, unsigned char cAl, Alojamiento** alojamientos)
    : puntuacion(p), antiguedadMeses(antiguedad), cantidadAlojamientos(cAl), alojamientos(alojamientos)
{
    for (unsigned char i = 0; i < 11; i++)
        documentoAnfitrion[i] = documento[i];
}


Anfitrion::~Anfitrion() {}


unsigned char* Anfitrion::getDocumento() { return documentoAnfitrion; }
float Anfitrion::getPuntuacion() const { return puntuacion; }
unsigned char Anfitrion::getAntiguedadMeses() const { return antiguedadMeses; }
unsigned char Anfitrion::getCantidadAlojamientos() const {return cantidadAlojamientos;}
Alojamiento** Anfitrion::getAlojamientos() const { return alojamientos; }
void Anfitrion::setAlojamientos(Alojamiento** nuevosAlojamientos)
{
    alojamientos = nuevosAlojamientos;
}

void Anfitrion::consultarReservas(Fecha fechaInicio, Fecha fechaFin)
{
    for(unsigned int i = 0; i < cantidadAlojamientos; i++){
        for(unsigned char r = 0; r < this->alojamientos[i]->getCantidadReservas(); r++){
            Reserva* reserva = this->alojamientos[i]->getReservasVigentes()[r];
            if(reserva->getFechaEntrada() >= fechaInicio && reserva->getFechaEntrada() <= fechaFin){
                cout << "------------------------\n";
                cout << "Reserva #" << reserva->getCodigoIdentificador() << "\n";

                // Alojamiento
                Alojamiento* a = reserva->getAlojamientoReserva();
                if (a != nullptr) {
                    cout << "  Alojamiento: " << a->getNombreAlojamiento() << "\n";
                } else {
                    cout << "  Alojamiento: No asignado\n";
                }

                // Huésped
                Huesped* h = reserva->getHuesped();
                if (h != nullptr) {
                    cout << "  Huesped: ";
                    unsigned char* docHuesped = h->getDocumento();
                    for (int j = 0; j < 11; ++j) {
                        cout << docHuesped[j];
                    }
                    cout << "\n";
                } else {
                    cout << "  Huesped: [no asignado aun]\n";
                }

                // Fechas
                cout << "  Fecha de Entrada: " << reserva->getFechaEntrada().imprimirFecha() << "\n";
                cout << "  Fecha de Salida : " << reserva->getFechaSalida().imprimirFecha() << "\n";
                cout << "  Fecha de Pago   : " << reserva->getFechaPago().imprimirFecha() << "\n";

                // Otros datos
                cout << "  Duracion        : " << static_cast<int>(reserva->getDuracion()) << " noches\n";
                cout << "  Monto           : $" << reserva->getMonto() << "\n";
                cout << "  Metodo de Pago  : " << (reserva->getMetodoPago() ? "Tarjeta" : "Efectivo") << "\n";
                cout << "  Anotaciones     : " << reserva->getAnotaciones() << "\n";
                cout << "------------------------\n\n";
            }
        }
    }
}
