#ifndef MISCELANEOS_H
#define MISCELANEOS_H

#include <string>
#include "anfitrion.h"
#include "reserva.h"
#include "fecha.h"

using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short a);
string validarAnotaciones();
Fecha validarFecha(string id);
bool validarMetodoDePago();
unsigned int contarLineasArchivos(string nombreArchivo);
Alojamiento** cargarAlojamientos(string nombreArchivo, unsigned int & cantidad);
Alojamiento* buscarAlojamientoPorCodigo(Alojamiento** alojamientos, unsigned int cantidad, unsigned int codigoBuscado);
Anfitrion** cargarAnfitriones(string nombreArchivo, unsigned int &cantidad, Alojamiento** todosLosAlojamientos, unsigned int cantidadTotalAlojamientos);
Reserva*** cargarReserva(string nombreArchivo, unsigned int &cantidad, unsigned int &bloques, unsigned int &fila, unsigned int &columna, unsigned int& cCodigo, Alojamiento** alojamientosTotales, unsigned int cantidadAlojamientosTotales);
#endif
