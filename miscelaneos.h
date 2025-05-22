#ifndef MISCELANEOS_H
#define MISCELANEOS_H

#include <string>
#include "anfitrion.h"
#include "fecha.h"
using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short a);
string validarAnotaciones();
Fecha validarFecha(string id);
bool validarMetodoDePago();
unsigned int contarLineasArchivos(string nombreArchivo);
Alojamiento** cargarAlojamientos(string nombreArchivo, unsigned int & cantidad);


#endif
