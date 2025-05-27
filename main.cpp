#include <iostream>
#include "alojamiento.h"
#include "huesped.h"
#include "reserva.h"
#include "miscelaneos.h"
using namespace std;

void imprimirAlojamientos(Alojamiento** alojamientos, unsigned int cantidad) {

    for (unsigned int i = 0; i < cantidad; ++i) {
        if (!alojamientos[i]) continue;
        Alojamiento* a = alojamientos[i];
        cout << "-------------------------------" << endl;
        cout << "Codigo identificador: " << a->getCodigoIdentificador() << endl;
        cout << "Nombre del alojamiento: " << a->getNombreAlojamiento() << endl;

        Anfitrion* anfitrion = a->getAnfitrionRespon();
        if (anfitrion != nullptr) {
            cout << "Documento del anfitrion: " << alojamientos[i]->getAnfitrionRespon()->getDocumento() << endl;
        } else {
            cout << "Anfitrion: (sin asignar)" << endl;
        }

        cout << "Departamento: " << a->getDepartamento() << endl;
        cout << "Municipio: " << a->getMunicipio() << endl;
        cout << "Tipo: " << (a->getTipo() ? "Apartamento" : "Casa") << endl;
        cout << "Direccion: " << a->getDireccion() << endl;
        cout << "Precio por noche: $" << a->getPrecioNoche() << endl;

        cout << "Amenidades: ";
        bool* amenidades = a->getAmenidades();
        for (int j = 0; j < 5; ++j) {
            cout << (amenidades[j] ? "1" : "0");
            if (j < 4) cout << " ";
        }
        cout << endl;

        // Si tienes una función para obtener la cantidad de reservas:
        Reserva** reservas = a->getReservasVigentes();
        unsigned char cantidadReservas = 0;
        for(int i = 0; i < a->getCantidadReservas(); i++){
            if(reservas != nullptr && reservas[i] != nullptr){
                cout << "Codigo alojamiento reserva: " << reservas[i]->getCodigoIdentificador() << endl;
                cantidadReservas++;
            }
        }
        cout << "Cantidad de reservas: " << int(cantidadReservas) << endl;

        cout << "-------------------------------" << endl;
    }
}

void imprimirReservas(Reserva*** reservas, unsigned int cantidad, unsigned int bloques) {
    for (unsigned int i = 0; i < cantidad; ++i) {
        unsigned int fila = i / bloques;
        unsigned int columna = i % bloques;

        Reserva* r = reservas[fila][columna];
        if (r == nullptr) continue;

        cout << "------------------------\n";
        cout << "Reserva #" << r->getCodigoIdentificador() << "\n";

        // Alojamiento
        Alojamiento* a = r->getAlojamientoReserva();
        if (a != nullptr) {
            cout << "  Alojamiento: " << a->getNombreAlojamiento() << "\n";
        } else {
            cout << "  Alojamiento: No asignado\n";
        }

        // Huésped
        Huesped* h = r->getHuesped();
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
        cout << "  Fecha de Entrada: " << r->getFechaEntrada().imprimirFecha() << "\n";
        cout << "  Fecha de Salida : " << r->getFechaSalida().imprimirFecha() << "\n";
        cout << "  Fecha de Pago   : " << r->getFechaPago().imprimirFecha() << "\n";

        // Otros datos
        cout << "  Duracion        : " << static_cast<int>(r->getDuracion()) << " noches\n";
        cout << "  Monto           : $" << r->getMonto() << "\n";
        cout << "  Metodo de Pago  : " << (r->getMetodoPago() ? "Tarjeta" : "Efectivo") << "\n";
        cout << "  Anotaciones     : " << r->getAnotaciones() << "\n";
        cout << "------------------------\n\n";
    }
}

void imprimirHuespedes(Huesped** huespedes, unsigned int cantidad) {
    for (unsigned int i = 0; i < cantidad; ++i) {
        Huesped* h = huespedes[i];

        cout << "Huesped #" << (i + 1) << endl;
        cout << "Documento: ";
        for (int j = 0; j < 11; ++j) {
            cout << h->getDocumento()[j];
        }
        cout << endl;

        cout << "Puntuacion: " << h->getPuntuacion() << endl;
        cout << "Antiguedad (meses): " << (int)h->getAntiguedadMeses() << endl;
        cout << "Cantidad de reservas: " << (int)h->getCantidadReservas() << endl;

        Reserva** reservas = h->getReservas();
        for (int j = 0; j < h->getCantidadReservas(); ++j) {
            if (reservas[j] != nullptr) {
                cout << " - Reserva " << (j + 1) << ": Codigo " << reservas[j]->getCodigoIdentificador() << endl;
            }
        }

        cout << "----------------------------------------" << endl;
    }
}

int main()
{
    // Cargar archivos
    unsigned int cantidadAlojamientos = 0, cantidadAnfitriones = 0, cantidadReservas = 0, cantidadHuesped = 0, columnasTotales = 0, fila = 0, columna = 0, contador = 0;
    Alojamiento** alojamientos = cargarAlojamientos("../../data/alojamientos.txt", cantidadAlojamientos);
    Anfitrion** anfitriones = cargarAnfitriones("../../data/anfitrion.txt", cantidadAnfitriones, alojamientos, cantidadAlojamientos);
    Reserva*** reservas = cargarReserva("../../data/reservas.txt",cantidadReservas, columnasTotales, fila, columna, contador, alojamientos,cantidadAlojamientos);
    unsigned int filasTotales = columnasTotales * 2;
    Huesped** huespedes = cargarHuesped("../../data/huesped.txt", cantidadHuesped,reservas, filasTotales, columnasTotales);

    /*
    // Impresion
    cout << "Reservas" << endl;
    imprimirReservas(reservas, cantidadReservas,columnasTotales);

    cout << endl << endl << "Alojamientos" << endl;
    imprimirAlojamientos(alojamientos,cantidadAlojamientos);

    cout << endl << endl <<  "Huespedes" << endl;
    imprimirHuespedes(huespedes, cantidadHuesped);
    */

    // Fecha de corte y actualizacion de historico
    cout << "A continuacion definira la fecha de corte: " << endl;
    Fecha fechaCorte = validarFecha("la fecha de corte");
    actualizarHistorico(reservas,fechaCorte,"../../data/historico.txt",cantidadReservas,filasTotales,columnasTotales);
    // Ciclo
    string autenticar;
    do{
        cout << endl << "Seleccione 1 para autenticarse o 0 para salir: ";
        cin >> autenticar;
        if(autenticar == "1"){
            // Datos para autenticar
            cout << endl << "Ingrese el numero de documento: ";
            unsigned char documento[11];
            cin >> documento;

            if(buscarUsuario<Anfitrion>(anfitriones, cantidadAnfitriones, documento)){
                Anfitrion* usuario = buscarUsuario<Anfitrion>(anfitriones, cantidadAnfitriones, documento);
                string modo = "";
                do{
                    cout << endl << "1 para consultar reservas.\n2 para eliminar reservas.\n3 para salir\nEscoge un modo: ";
                    cin >> modo;
                    if(modo == "1"){
                        // Consultar reservas
                        Fecha fechaInicio = validarFecha("comienzo de la consulta");
                        Fecha fechaFin = validarFecha("fin de la consulta");

                        cout << fechaInicio.imprimirFecha() << endl;
                        cout << fechaFin.imprimirFecha() << endl;
                        usuario->consultarReservas(fechaInicio,fechaFin);
                    }
                    else if(modo == "2"){
                        // Eliminar reserva
                        eliminarReserva(reservas, filasTotales, columnasTotales, cantidadReservas);
                    }
                    else if(modo == "3"){
                        break;
                    }}while(modo != "1" || modo != "2" || modo != "3");


            }
            else if(buscarUsuario<Huesped>(huespedes,cantidadHuesped, documento)){
                cout << "Huesped";
                // Reservar alojamiento
                // Fecha, municipio, cantidad noches (Filtro de precio y/o puntuacion)
                // Codigo Alojamiento

                // Eliminar reserva
                eliminarReserva(reservas, filasTotales, columnasTotales, cantidadReservas);
            }
            else{
                cout << "El usuario no existe";
            }}
        else if(autenticar == "0"){
            break;
        }
    }while(autenticar != "1" || autenticar != "0");

    /*
    // Impresion
    cout << "Despues de: " << endl;
    imprimirReservas(reservas, cantidadReservas,columnasTotales);

    cout << endl << endl << "Alojamientos" << endl;
    imprimirAlojamientos(alojamientos,cantidadAlojamientos);

    cout << endl << endl <<  "Huespedes" << endl;
    imprimirHuespedes(huespedes, cantidadHuesped);
*/

    // Guardar archivos
    guardarReservas("../../data/reservas.txt", reservas, filasTotales, columnasTotales, contador);
    guardarHuespedes("../../data/huesped.txt",huespedes, cantidadHuesped);
    guardarAlojamientos("../../data/alojamientos.txt", alojamientos, cantidadAlojamientos);
    return 0;
}
