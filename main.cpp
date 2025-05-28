#include <iostream>
#include <climits>

#include "alojamiento.h"
#include "huesped.h"
#include "reserva.h"
#include "miscelaneos.h"
using namespace std;

int main()
{
    // Variables de tamanio e iteraciones
    unsigned int iteraciones = 0;
    size_t tamanioObjetos = 0;

    // Cargar archivos
    unsigned int cantidadAlojamientos = 0, cantidadAnfitriones = 0, cantidadReservas = 0, cantidadHuesped = 0, columnasTotales = 0, fila = 0, columna = 0, contadorCodigoReservas = 0;
    Alojamiento **alojamientos = cargarAlojamientos("../../data/alojamientos.txt", cantidadAlojamientos, iteraciones);
    Anfitrion **anfitriones = cargarAnfitriones("../../data/anfitrion.txt", cantidadAnfitriones, alojamientos, cantidadAlojamientos, iteraciones);
    Reserva ***reservas = cargarReserva("../../data/reservas.txt", cantidadReservas, columnasTotales, fila, columna, contadorCodigoReservas, alojamientos, cantidadAlojamientos, iteraciones);
    unsigned int filasTotales = columnasTotales * 2;
    Huesped **huespedes = cargarHuesped("../../data/huesped.txt", cantidadHuesped, reservas, fila+1, columnasTotales, iteraciones);

    // Fecha de corte y actualizacion de historico
    cout << "----------------------------------------" << endl;
    cout << "Fecha de corte" << endl;
    Fecha fechaCorte = validarFecha("la fecha de corte",iteraciones);
    Fecha fechaMaxima = fechaCorte.calcularFecha();
    actualizarHistorico(reservas, fechaCorte, "../../data/historico.txt", cantidadReservas, fila+1, columnasTotales,iteraciones);
    cout << endl;
    // Ciclo
    string autenticar;
    do
    {
        cout << "----------------------------------------" << endl;
        cout << "Seleccione 1 para autenticarse o 0 para salir: ";
        cin >> autenticar;
        cout << endl;
        if (autenticar == "1")
        {
            // Datos para autenticar
            cout << "Ingrese el numero de documento: ";
            unsigned char documento[11];
            cin >> documento;
            cout  << endl;

            Anfitrion *usuarioAnfitrion = buscarUsuario<Anfitrion>(anfitriones, cantidadAnfitriones, documento,iteraciones);
            Huesped* usuarioHuesped = buscarUsuario<Huesped>(huespedes, cantidadHuesped, documento,iteraciones);
            if (usuarioAnfitrion)
            {
                string modo = "";
                do
                {
                    cout << "----------------------------------------" << endl;
                    cout << "1 para consultar reservas.\n2 para eliminar reservas.\n3 para salir\nEscoge un modo: ";
                    cin >> modo;
                    cout << endl;
                    if (modo == "1")
                    {
                        // Consultar reservas
                        cout << "----------------------------------------" << endl;
                        Fecha fechaInicio = validarFecha("comienzo de la consulta",iteraciones);
                        Fecha fechaFin = validarFecha("fin de la consulta",iteraciones);

                        usuarioAnfitrion->consultarReservas(fechaInicio, fechaFin, iteraciones);
                    }
                    else if (modo == "2")
                    {
                        cout << "----------------------------------------" << endl;
                        eliminarReserva(reservas, fila+1, columnasTotales, cantidadReservas, usuarioAnfitrion, iteraciones);
                    }
                    else if (modo == "3")
                    {
                        break;
                    }
                } while (modo != "1" || modo != "2" || modo != "3");
            }
            else if (usuarioHuesped)
            {
                string modo = "";
                do
                {
                    cout << "----------------------------------------" << endl;
                    cout << "1 para reservar de forma general.\n2 para reservar por codigo.\n3 para eliminar una reserva.\n4 para salir\nEscoge un modo: ";
                    cin >> modo;
                    cout << endl;

                    if (modo == "1")
                    {
                        cout << "----------------------------------------" << endl;
                        unsigned int cantidadAlRe = 0;
                        Fecha fechaInicio = validarFecha("inicio reserva",iteraciones);
                        while (fechaInicio < fechaCorte || fechaMaxima < fechaInicio)
                        {
                            cout << "La fecha debe ser mayor a la fecha de corte" << endl;
                            fechaInicio = validarFecha("inicio reserva",iteraciones);
                        }
                        string sDuracion;
                        cout << "Ingrese la duracion de su reserva (en cantidad de noches): ";
                        cin >> sDuracion;
                        cout << endl;

                        unsigned char duracion = static_cast<unsigned char>(stoi(sDuracion));
                        Fecha fechaSalida = fechaInicio.calcularFecha(duracion,iteraciones);
                        string municipio;
                        float puntuacion = 0;
                        unsigned int precio = UINT_MAX;
                        cout << "Ingrese el municipio: ";
                        cin >> municipio;
                        cout << endl;

                        cout << "Ingrese 1 para filtrar por precio, 2 para filtrar por puntuacion, 3 para filtrar por ambos o cualquier otro numero para no filtrar: ";
                        string preOPun;
                        cin >> preOPun;
                        cout << endl;

                        if (preOPun == "1")
                        {
                            cout << "Ingrese el precio maximo que esta dispuesto a pagar: ";
                            cin >> precio;
                            cout << endl;
                        }
                        else if (preOPun == "2")
                        {
                            cout << "Ingrese la puntuacion minima que debe tener el anfitrion: ";
                            cin >> puntuacion;
                            cout << endl;
                        }
                        else if (preOPun == "3")
                        {
                            cout << "Ingrese el precio maximo que esta dispuesto a pagar: ";
                            cin >> precio;

                            cout << endl;
                            cout << "Ingrese la puntuacion minima que debe tener el anfitrion: ";
                            cin >> puntuacion;
                            cout << endl;
                        }

                        Alojamiento **alojamientosReservas = reservaConFiltro(alojamientos, cantidadAlojamientos, fechaInicio, fechaSalida, municipio, cantidadAlRe, puntuacion, precio,iteraciones);

                        cout << "----------------------------------------" << endl;
                        if (cantidadAlRe == 0)
                        {
                            cout << "No hay alojamientos disponibles o no existen alojamientos que satisfagan tus preferencias" << endl;
                        }
                        else
                        {
                            unsigned int codigoReserva = 0;
                            cout << "Ingrese el codigo del alojamiento que quiere reservar: ";
                            cin >> codigoReserva;
                            for (unsigned int i = 0; i < cantidadAlRe; i++)
                            {
                                if (alojamientosReservas[i] && alojamientosReservas[i]->getCodigoIdentificador() == codigoReserva)
                                {

                                    string anotaciones = validarAnotaciones(iteraciones);
                                    Fecha fechaPago = validarFecha("fecha de pago",iteraciones);
                                    bool mPago = validarMetodoDePago();

                                    // Si se llega al final de la columna actual
                                    if (columna >= columnasTotales)
                                    {
                                        columna = -1;
                                        fila++;

                                        // Si también se llega al final de las filas actuales
                                        if (fila >= filasTotales)
                                        {

                                            // Aumentar el tamaño de filas
                                            unsigned int nuevasFilasTotales = filasTotales + 5;
                                            Reserva ***nuevo = new Reserva **[nuevasFilasTotales];

                                            // Copiar punteros existentes
                                            for (unsigned int i = 0; i < filasTotales; i++)
                                            {
                                                nuevo[i] = reservas[i];
                                            }

                                            // Inicializar nuevas filas
                                            for (unsigned int i = filasTotales; i < nuevasFilasTotales; i++)
                                            {
                                                nuevo[i] = new Reserva *[columnasTotales];
                                                for (unsigned int j = 0; j < columnasTotales; j++)
                                                {
                                                    nuevo[i][j] = nullptr;
                                                }
                                            }

                                            delete[] reservas;

                                            reservas = nuevo;
                                            filasTotales = nuevasFilasTotales;
                                        }

                                        if (!reservas[fila])
                                        {
                                            reservas[fila] = new Reserva *[columnasTotales];
                                            for (unsigned int j = 0; j < columnasTotales; j++)
                                            {
                                                reservas[fila][j] = nullptr;
                                            }
                                        }
                                    }

                                    columna++;
                                    contadorCodigoReservas++;
                                    reservas[fila][columna] = new Reserva(anotaciones, fechaInicio, fechaSalida, fechaPago, alojamientosReservas[i]->getPrecioNoche() * duracion, usuarioHuesped, alojamientosReservas[i], contadorCodigoReservas, duracion, mPago);
                                    alojamientosReservas[i]->agregarReserva(reservas[fila][columna],iteraciones);
                                    usuarioHuesped->agregarReserva(reservas[fila][columna],iteraciones);
                                    imprimir(reservas[fila][columna]);
                                    break;
                                }
                            }
                        }
                    }
                    else if (modo == "2")
                    {
                        cout << "----------------------------------------" << endl;
                        Fecha fechaInicio = validarFecha("inicio reserva",iteraciones);
                        while (fechaInicio < fechaCorte || fechaMaxima < fechaInicio)
                        {
                            cout << "La fecha debe ser mayor a la fecha de corte" << endl;
                            fechaInicio = validarFecha("inicio reserva",iteraciones);
                        }
                        string sDuracion;
                        unsigned int duracionTemporal = 0;
                        do
                        {
                            cout << "Ingrese la duracion de su reserva (en cantidad de noches): ";
                            cin >> sDuracion;
                            cout << endl;
                            try
                            {
                                duracionTemporal = stoi(sDuracion);
                                if (duracionTemporal > UCHAR_MAX)
                                {
                                    cout << "La duracion es demasiado larga, maximo puedes reservar por " << UCHAR_MAX << " dias" << endl;
                                    duracionTemporal = 0;
                                }
                            }
                            catch (...)
                            {
                                duracionTemporal = 0;
                                cout << "Cantidad invalida. Intente nuevamente." << endl;
                            }
                        } while (duracionTemporal == 0);
                        unsigned char duracion = static_cast<unsigned char>(stoi(sDuracion));

                        Fecha fechaSalida = fechaInicio.calcularFecha(duracion,iteraciones);

                        unsigned int codigoAlojamiento = 0;
                        cout << "Ingrese el codigo del alojamiento: ";
                        cin >> codigoAlojamiento;
                        cout << endl;
                        Alojamiento *alTemp = buscarPorCodigo(alojamientos, cantidadAlojamientos, codigoAlojamiento, iteraciones);

                        for (unsigned int r = 0; r < alTemp->getCantidadReservas(); r++)
                        {
                            if (alTemp->getReservasVigentes()[r])
                            {
                                Reserva *reTemp = alTemp->getReservasVigentes()[r];
                                if (((fechaSalida < reTemp->getFechaEntrada()) || (reTemp->getFechaEntrada() < fechaInicio)))
                                {
                                    cout << "Este alojamiento esta disponible para reservar en estas fechas: " << endl;
                                    string anotaciones = validarAnotaciones(iteraciones);
                                    Fecha fechaPago = validarFecha("fecha de pago", iteraciones);
                                    bool mPago = validarMetodoDePago();
                                    // Si se llega al final de la columna actual
                                    if (columna >= columnasTotales)
                                    {
                                        columna = 0;
                                        fila++;

                                        // Si también se llega al final de las filas actuales
                                        if (fila >= filasTotales)
                                        {
                                            // Aumentar el tamaño de filas
                                            unsigned int nuevasFilasTotales = filasTotales + 5;
                                            Reserva ***nuevo = new Reserva **[nuevasFilasTotales];

                                            // Copiar punteros existentes
                                            for (unsigned int i = 0; i < filasTotales; i++)
                                            {
                                                nuevo[i] = reservas[i];
                                            }

                                            // Inicializar nuevas filas
                                            for (unsigned int i = filasTotales; i < nuevasFilasTotales; i++)
                                            {
                                                nuevo[i] = new Reserva *[columnasTotales];
                                                for (unsigned int j = 0; j < columnasTotales; j++)
                                                {
                                                    nuevo[i][j] = nullptr;
                                                }
                                            }

                                            delete[] reservas;

                                            reservas = nuevo;
                                            filasTotales = nuevasFilasTotales;
                                        }

                                        if (!reservas[fila])
                                        {
                                            reservas[fila] = new Reserva *[columnasTotales];
                                            for (unsigned int j = 0; j < columnasTotales; j++)
                                            {
                                                reservas[fila][j] = nullptr;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        columna++;
                                    }

                                    contadorCodigoReservas++;
                                    reservas[fila][columna] = new Reserva(anotaciones, fechaInicio, fechaSalida, fechaPago, alTemp->getPrecioNoche() * duracion, usuarioHuesped, alTemp, contadorCodigoReservas, duracion, mPago);
                                    alTemp->agregarReserva(reservas[fila][columna],iteraciones);
                                    usuarioHuesped->agregarReserva(reservas[fila][columna],iteraciones);
                                    imprimir(reservas[fila][columna]);
                                    break;
                                }
                            }
                        }
                    }
                    else if (modo == "3")
                    {
                        cout << "----------------------------------------" << endl;
                        eliminarReserva(reservas, fila+1, columnasTotales, cantidadReservas, usuarioHuesped, iteraciones);
                    }
                    else if (modo == "4")
                    {
                        break;
                    }
                } while (modo != "1" || modo != "2" || modo != "3" || modo != "4");
            }
            else
            {
                cout << "El usuario no existe" << endl;
            }
        }
        else if (autenticar == "0")
        {
            break;
        }
    } while (autenticar != "1" || autenticar != "0");

    // Guardar archivos
    guardarArchivos("../../data/reservas.txt", reservas, filasTotales, columnasTotales, contadorCodigoReservas, iteraciones);
    guardarArchivos("../../data/huesped.txt", huespedes, cantidadHuesped, iteraciones);
    guardarArchivos("../../data/alojamientos.txt", alojamientos, cantidadAlojamientos, iteraciones);

    // Liberar memoria
    // Alojamientos
    for (unsigned int i = 0; i < cantidadAlojamientos; ++i)
    {
        iteraciones++;
        tamanioObjetos+= alojamientos[i]->tamanio();
        delete alojamientos[i];
    }
    delete[] alojamientos;


    // Anfitriones
    for (unsigned int i = 0; i < cantidadAnfitriones; ++i)
    {
        iteraciones++;
        tamanioObjetos+= anfitriones[i]->tamanio();
        delete anfitriones[i];
    }
    delete[] anfitriones;

    // Huespedes
    for (unsigned int i = 0; i < cantidadHuesped; ++i)
    {
        iteraciones++;
        tamanioObjetos += huespedes[i]->tamanio();
        delete huespedes[i];
    }
    delete[] huespedes;

    // Reservas
    for (unsigned int i = 0; i < fila; i++)
    {
        iteraciones++;
        for (unsigned int j = 0; j < columnasTotales; j++)
        {
            iteraciones++;
            if(reservas[i][j])
                tamanioObjetos += reservas[i][j]->tamanio();
            delete reservas[i][j];
        }
        delete[] reservas[i];
    }
    delete[] reservas;

    cout << "----------------------------------------" << endl;
    cout << "Cantidad de iteraciones: " << iteraciones << endl;
    cout << "Tamanio de los objetos: " << tamanioObjetos << endl;

    return 0;
}
