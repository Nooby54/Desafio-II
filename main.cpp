#include <iostream>
#include <climits>

#include "alojamiento.h"
#include "huesped.h"
#include "reserva.h"
#include "miscelaneos.h"
using namespace std;

int main()
{
    // Cargar archivos
    unsigned int cantidadAlojamientos = 0, cantidadAnfitriones = 0, cantidadReservas = 0, cantidadHuesped = 0, columnasTotales = 0, fila = 0, columna = 0, contadorCodigoReservas = 0;
    Alojamiento **alojamientos = cargarAlojamientos("../../data/alojamientos.txt", cantidadAlojamientos);
    Anfitrion **anfitriones = cargarAnfitriones("../../data/anfitrion.txt", cantidadAnfitriones, alojamientos, cantidadAlojamientos);
    Reserva ***reservas = cargarReserva("../../data/reservas.txt", cantidadReservas, columnasTotales, fila, columna, contadorCodigoReservas, alojamientos, cantidadAlojamientos);
    unsigned int filasTotales = columnasTotales * 2;
    Huesped **huespedes = cargarHuesped("../../data/huesped.txt", cantidadHuesped, reservas, filasTotales, columnasTotales);

    // Fecha de corte y actualizacion de historico
    cout << "A continuacion debera definir la fecha de corte: " << endl;
    Fecha fechaCorte = validarFecha("la fecha de corte");
    actualizarHistorico(reservas, fechaCorte, "../../data/historico.txt", cantidadReservas, filasTotales, columnasTotales);
    // Ciclo
    string autenticar;
    do
    {
        cout << endl
             << "Seleccione 1 para autenticarse o 0 para salir: ";
        cin >> autenticar;
        if (autenticar == "1")
        {
            // Datos para autenticar
            cout << endl
                 << "Ingrese el numero de documento: ";
            unsigned char documento[11];
            cin >> documento;

            if (buscarUsuario<Anfitrion>(anfitriones, cantidadAnfitriones, documento))
            {
                Anfitrion *usuario = buscarUsuario<Anfitrion>(anfitriones, cantidadAnfitriones, documento);
                string modo = "";
                do
                {
                    cout << endl
                         << "1 para consultar reservas.\n2 para eliminar reservas.\n3 para salir\nEscoge un modo: ";
                    cin >> modo;
                    if (modo == "1")
                    {
                        // Consultar reservas
                        Fecha fechaInicio = validarFecha("comienzo de la consulta");
                        Fecha fechaFin = validarFecha("fin de la consulta");

                        cout << fechaInicio.imprimirFecha() << endl;
                        cout << fechaFin.imprimirFecha() << endl;
                        usuario->consultarReservas(fechaInicio, fechaFin);
                    }
                    else if (modo == "2")
                    {
                        // Eliminar reserva
                        // Validar que le pertenezca
                        eliminarReserva(reservas, filasTotales, columnasTotales, cantidadReservas);
                    }
                    else if (modo == "3")
                    {
                        break;
                    }
                } while (modo != "1" || modo != "2" || modo != "3");
            }
            else if (buscarUsuario<Huesped>(huespedes, cantidadHuesped, documento))
            {
                Huesped *usuario = buscarUsuario<Huesped>(huespedes, cantidadHuesped, documento);
                string modo = "";
                do
                {
                    cout << endl
                         << "1 para reservar de forma general.\n2 para reservar por codigo.\n3 para eliminar una reserva.\n4 para salir\nEscoge un modo: ";
                    cin >> modo;

                    if (modo == "1")
                    {
                        unsigned int cantidadAlRe = 0;
                        Fecha fechaInicio = validarFecha("inicio reserva");
                        string sDuracion;
                        cout << endl
                             << "Ingrese la duracion de su reserva (en cantidad de noches): ";
                        cin >> sDuracion;
                        unsigned char duracion = static_cast<unsigned char>(stoi(sDuracion));
                        Fecha fechaSalida = fechaInicio.calcularFechaDias(duracion);
                        string municipio;
                        float puntuacion = 0;
                        unsigned int precio = UINT_MAX;
                        cout << endl
                             << "Ingrese el municipio: ";
                        cin >> municipio;
                        cout << endl
                             << "Ingrese 1 para filtrar por precio, 2 para filtrar por puntuacion, 3 para filtrar por ambos o cualquier otro numero para no filtrar: ";
                        string preOPun;
                        cin >> preOPun;
                        if (preOPun == "1")
                        {
                            cout << endl
                                 << "Ingrese el precio maximo que esta dispuesto a pagar: ";
                            cin >> precio;
                        }
                        else if (preOPun == "2")
                        {
                            cout << endl
                                 << "Ingrese la puntuacion minima que debe tener el anfitrion: ";
                            cin >> puntuacion;
                        }
                        else if (preOPun == "3")
                        {
                            cout << endl
                                 << "Ingrese el precio maximo que esta dispuesto a pagar: ";
                            cin >> precio;
                            cout << endl
                                 << "Ingrese la puntuacion minima que debe tener el anfitrion: ";
                            cin >> puntuacion;
                        }

                        Alojamiento **alojamientosReservas = reservaConFiltro(alojamientos, cantidadAlojamientos, fechaInicio, fechaSalida, municipio, cantidadAlRe, puntuacion, precio);

                        unsigned int codigoReserva = 0;
                        cout << "Ingrese el codigo del alojamiento que quiere reservar: ";
                        cin >> codigoReserva;
                        for (unsigned int i = 0; i < cantidadAlRe; i++)
                        {
                            if (alojamientosReservas[i] && alojamientosReservas[i]->getCodigoIdentificador() == codigoReserva)
                            {
                                string anotaciones = validarAnotaciones();
                                Fecha fechaPago = validarFecha("fecha de pago");
                                bool mPago = validarMetodoDePago();
                                fila++;
                                columna++;
                                contadorCodigoReservas++;
                                reservas[fila][columna] = new Reserva(anotaciones, fechaInicio, fechaSalida, fechaPago, alojamientosReservas[i]->getPrecioNoche() * duracion, usuario, alojamientosReservas[i], contadorCodigoReservas, duracion, mPago);
                                alojamientosReservas[i]->agregarReserva(reservas[fila][columna]);
                                usuario->agregarReserva(reservas[fila][columna]);
                            }
                        }
                    }
                    else if (modo == "2")
                    {
                        // Reserva con codigo de alojamiento especifico
                        Fecha fechaInicio = validarFecha("inicio reserva");
                        string sDuracion;
                        cout << endl
                             << "Ingrese la duracion de su reserva (en cantidad de noches): ";
                        cin >> sDuracion;
                        unsigned char duracion = static_cast<unsigned char>(stoi(sDuracion));
                        Fecha fechaSalida = fechaInicio.calcularFechaDias(duracion);

                        unsigned int codigoAlojamiento = 0;
                        cout << endl
                             << "Ingrese el codigo del alojamiento: ";
                        cin >> codigoAlojamiento;
                        Alojamiento *alTemp = buscarPorCodigo(alojamientos, cantidadAlojamientos, codigoAlojamiento);

                        for (unsigned int r = 0; r < alTemp->getCantidadReservas(); r++)
                        {
                            if (alTemp->getReservasVigentes()[r])
                            {
                                Reserva *reTemp = alTemp->getReservasVigentes()[r];
                                if (((fechaSalida < reTemp->getFechaEntrada()) || (reTemp->getFechaEntrada() < fechaInicio)))
                                {
                                    // Imprimir que esta disponible para reservar
                                    cout << endl
                                         << "Este alojamiento esta disponible para reservas en esas fechas" << endl;
                                    string anotaciones = validarAnotaciones();
                                    Fecha fechaPago = validarFecha("fecha de pago");
                                    bool mPago = validarMetodoDePago();
                                    fila++;
                                    columna++;
                                    contadorCodigoReservas++;
                                    reservas[fila][columna] = new Reserva(anotaciones, fechaInicio, fechaSalida, fechaPago, alTemp->getPrecioNoche() * duracion, usuario, alTemp, contadorCodigoReservas, duracion, mPago);
                                    alTemp->agregarReserva(reservas[fila][columna]);
                                    usuario->agregarReserva(reservas[fila][columna]);
                                }
                            }
                        }
                    }
                    else if (modo == "3")
                    {
                        // Validar que le pertenezca
                        eliminarReserva(reservas, filasTotales, columnasTotales, cantidadReservas);
                    }
                    else if (modo == "4")
                    {
                        break;
                    }
                } while (modo != "1" || modo != "2" || modo != "3" || modo != "4");
            }
            else
            {
                cout << "El usuario no existe";
            }
        }
        else if (autenticar == "0")
        {
            break;
        }
    } while (autenticar != "1" || autenticar != "0");

    // Guardar archivos
    guardarReservas("../../data/reservas.txt", reservas, filasTotales, columnasTotales, contadorCodigoReservas);
    guardarHuespedes("../../data/huesped.txt", huespedes, cantidadHuesped);
    guardarAlojamientos("../../data/alojamientos.txt", alojamientos, cantidadAlojamientos);

    // Liberar memoria
    // Alojamientos
    for (unsigned int i = 0; i < cantidadAlojamientos; ++i)
    {
        delete alojamientos[i];
    }
    delete[] alojamientos;

    // Reservas
    for (unsigned int i = 0; i < filasTotales; ++i)
    {
        for (unsigned int j = 0; j < columnasTotales; ++j)
        {
            delete reservas[i][j];
        }
        delete[] reservas[i];
    }
    delete[] reservas;

    // Anfitriones
    for (unsigned int i = 0; i < cantidadAnfitriones; ++i)
    {
        delete anfitriones[i];
    }
    delete[] anfitriones;

    // Huespedes
    for (unsigned int i = 0; i < cantidadHuesped; ++i)
    {
        delete huespedes[i];
    }
    delete[] huespedes;
    return 0;
}
