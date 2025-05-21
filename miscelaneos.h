#ifndef MISCELANEOS_H
#define MISCELANEOS_H

#include <string>
#include "fecha.h"
using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short a);
string validarAnotaciones();
Fecha validarFecha(string id);


#endif
