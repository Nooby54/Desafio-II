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
bool interseccionFechas(Alojamiento* alojamiento, Huesped* huesped, Fecha fechaInicio, Fecha fechaFin);
void actualizarHistorico(Reserva*** reservas, Fecha fecha, string nombreArchivo, unsigned int &cantidad, unsigned int filas, unsigned int columnas);
void guardarReservas(Reserva** reservas, int cantidad);
void guardarHuespedes(Huesped** huespedes, int cantidad);
void guardarAlojamientos(Alojamiento** alojamientos, int cantidad);
template<typename T>
void redimensionarArreglo(T**& arreglo, unsigned int cantidad) {
    T** nuevoArreglo = new T*[cantidad*2];
    memcpy(nuevoArreglo, arreglo, cantidad);

    for (unsigned int i = cantidad; i < cantidad*2; ++i) {
        nuevoArreglo[i] = nullptr;
    }

    delete[] arreglo;
    arreglo = nuevoArreglo;
}

#endif
