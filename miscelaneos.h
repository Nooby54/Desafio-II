#ifndef MISCELANEOS_H
#define MISCELANEOS_H

#include <string>
#include "anfitrion.h"
#include "reserva.h"
#include "fecha.h"

using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short int a);
string validarAnotaciones();
Fecha validarFecha(string id);
bool validarMetodoDePago();
unsigned int contarLineasArchivos(string nombreArchivo);
Alojamiento** cargarAlojamientos(string nombreArchivo, unsigned int &cantidad);
template< class T > T* buscarPorCodigo(T** datos, unsigned int cantidad, unsigned int codigoBuscado );
Anfitrion** cargarAnfitriones(string nombreArchivo, unsigned int &cantidad, Alojamiento** alojamientosTotales, unsigned int cantidadAlojamientosTotales);
Reserva*** cargarReserva(string nombreArchivo, unsigned int &cantidad, unsigned int &bloques, unsigned int &fila, unsigned int &columna, unsigned int& cCodigo, Alojamiento** alojamientosTotales, unsigned int cantidadAlojamientosTotales);
Reserva* buscarReservaPorCodigo(Reserva*** reservas, unsigned int filas, unsigned int columnas, unsigned int codigoBuscado);
Huesped** cargarHuesped(string nombreArchivo, unsigned int &cantidad, Reserva*** reservasTotales, unsigned int filas, unsigned int bloques);
#endif
