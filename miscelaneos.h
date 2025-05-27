#ifndef MISCELANEOS_H
#define MISCELANEOS_H

#include <string>
#include "anfitrion.h"
#include "reserva.h"
#include "fecha.h"

using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short int a);
string validarAnotaciones(unsigned int &iteraciones);
Fecha validarFecha(string id, unsigned int &iteraciones);
bool validarMetodoDePago();
unsigned int contarLineasArchivos(string nombreArchivo, unsigned int &iteraciones);
Alojamiento **cargarAlojamientos(string nombreArchivo, unsigned int &cantidad, unsigned int &iteraciones);
template <class T>
T *buscarPorCodigo(T **datos, unsigned int cantidad, unsigned int codigoBuscado, unsigned int &iteraciones);
Anfitrion **cargarAnfitriones(string nombreArchivo, unsigned int &cantidad, Alojamiento **alojamientosTotales, unsigned int cantidadAlojamientosTotales, unsigned int &iteraciones);
Reserva ***cargarReserva(string nombreArchivo, unsigned int &cantidad, unsigned int &bloques, unsigned int &fila, unsigned int &columna, unsigned int &cCodigo, Alojamiento **alojamientosTotales, unsigned int cantidadAlojamientosTotales, unsigned int &iteraciones);
Reserva *buscarReservaPorCodigo(Reserva ***reservas, unsigned int filas, unsigned int columnas, unsigned int codigoBuscado, unsigned int &iteraciones);
Huesped **cargarHuesped(string nombreArchivo, unsigned int &cantidad, Reserva ***reservasTotales, unsigned int filas, unsigned int bloques, unsigned int &iteraciones);
bool interseccionFechas(Alojamiento *alojamiento, Huesped *huesped, Fecha fechaInicio, Fecha fechaFin, unsigned int &iteraciones);
void actualizarHistorico(Reserva ***reservas, Fecha fecha, string nombreArchivo, unsigned int &cantidad, unsigned int filas, unsigned int columnas, unsigned int &iteraciones);
void guardarArchivos(const string &nombreArchivo, Reserva ***reservas, unsigned int filas, unsigned int columnas, unsigned int cantidad, unsigned int &iteraciones);
void guardarArchivos(const string &nombreArchivo, Huesped **huespedes, int cantidad, unsigned int &iteraciones);
void guardarArchivos(const string &nombreArchivo, Alojamiento **alojamientos, int cantidad, unsigned int &iteraciones);
void eliminarReserva(Reserva ***&reservas, unsigned int filasTotales, unsigned int columnasTotales, unsigned int &cantidadReservas, Huesped*& huesped, unsigned int &iteraciones);
void eliminarReserva(Reserva ***&reservas, unsigned int filasTotales, unsigned int columnasTotales, unsigned int &cantidadReservas, Anfitrion*& anfitrion, unsigned int &iteraciones);
Alojamiento **reservaConFiltro(Alojamiento **alojamientos, unsigned int cantidadAlojamientos, Fecha fechaInicio, Fecha fechaFin, string municipio, unsigned int &cantidad, float puntuacion, unsigned int precio, unsigned int &iteraciones);
void imprimir(Reserva*& reserva);
template <class T>
T *buscarUsuario(T **datos, unsigned int cantidad, unsigned char documento[11], unsigned int &iteraciones)
{
    for (unsigned int c = 0; c < cantidad; c++)
    {
        iteraciones++;
        unsigned char *docActual = datos[c]->getDocumento();
        bool iguales = true;
        for (int i = 0; i < 11; ++i)
        {
            iteraciones++;
            if ((docActual[i]) != documento[i])
            {
                iguales = false;
                break;
            }
        }
        if (iguales)
            return datos[c];
    }

    return nullptr;
}
template <typename T>
void redimensionarArreglo(T **&arreglo, unsigned int cantidadVieja, unsigned int cantidadNueva, unsigned int &iteraciones)
{
    T **nuevoArreglo = new T *[cantidadNueva];
    if (arreglo != nullptr)
    {
        memcpy(nuevoArreglo, arreglo, cantidadVieja * sizeof(T *));
        delete[] arreglo;
    }
    for (unsigned int i = cantidadVieja; i < cantidadNueva; ++i)
    {
        iteraciones++;
        nuevoArreglo[i] = nullptr;
    }
    arreglo = nuevoArreglo;
}

#endif
