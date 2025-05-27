#include "miscelaneos.h"
#include "alojamiento.h"
#include "huesped.h"
#include <iostream>
#include <fstream>

using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short int a)
{
    if (m < 1 || m > 12)
        return false;

    unsigned char diasMes = 31;
    if (m == 2)
        diasMes = ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 29 : 28;
    else if (m == 4 || m == 6 || m == 9 || m == 11)
        diasMes = 30;

    return (d >= 1 && d <= diasMes);
}

string validarAnotaciones(unsigned int &iteraciones)
{
    string anotaciones;
    cout << "Ingrese las anotaciones, si no tiene presione enter: ";
    cin.ignore();
    getline(cin, anotaciones);
    while (anotaciones.length() > 1000)
    {
        iteraciones++;
        cout << "Demasiadas anotaciones, intenta ser mas preciso: ";
        getline(cin, anotaciones);
    }
    return anotaciones;
}

Fecha validarFecha(string id, unsigned int &iteraciones)
{
    string diaStr, mesStr;
    unsigned short int anio;
    int dia = -1, mes = -1;

    do {
        iteraciones++;
        cout << "A continuacion debe ingresar una fecha, tenga en cuenta que hasta que no sea una fecha valida no podra continuar" << endl;
        do {
            iteraciones++;
            cout << "Ingrese el dia de " + id + ": ";
            cin >> diaStr;
            try {
                dia = stoi(diaStr);
            } catch (...) {
                dia = -1;
                cout << "Día invalido. Intente nuevamente.\n";
            }
        } while (dia < 1 || dia > 31);


        do {
            iteraciones++;
            cout << "Ingrese el mes de " + id + ": ";
            cin >> mesStr;
            try {
                mes = stoi(mesStr);
            } catch (...) {
                mes = -1;
                cout << "Mes invalido. Intente nuevamente.\n";
            }
        } while (mes < 1 || mes > 12);

        cout << "Ingrese el anio de " + id + ": ";
        cin >> anio;

    } while (!esValida(static_cast<unsigned char>(dia), static_cast<unsigned char>(mes), anio));
    return Fecha(static_cast<unsigned char>(dia), static_cast<unsigned char>(mes), anio);
}

bool validarMetodoDePago()
{
    bool metodoDePago;
    cout << "(0) Para PSE \n (1) Tarjeta de credito \nIngrese el metodo de pago: ";
    cin >> metodoDePago;

    return metodoDePago;
}

unsigned int contarLineasArchivos(string nombreArchivo, unsigned int &iteraciones)
{
    unsigned int contadorLineas = 0;
    ifstream archivo;
    string linea;

    archivo.open(nombreArchivo);

    while (getline(archivo, linea))
    {
        iteraciones++;
        contadorLineas++;
    }

    archivo.close();
    return contadorLineas;
}

Alojamiento **cargarAlojamientos(string nombreArchivo, unsigned int &cantidad, unsigned int &iteraciones)
{
    unsigned int lineas = contarLineasArchivos(nombreArchivo, iteraciones);
    Alojamiento **alojamientos = new Alojamiento *[lineas];

    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    while (getline(archivo, lineaArchivo))
    {
        iteraciones++;
        unsigned int codigo = 0, precio = 0, i = 0;
        string nombre = "", documento = "", departamento = "", municipio = "", direccion = "";
        bool amenidades[5], tipo;
        Reserva **reservas = nullptr;
        Anfitrion *anfitrion = nullptr;
        unsigned char cantidadReservas = 0;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            codigo = (codigo * 10) + (lineaArchivo[i] - '0');
            i++;
        }
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            nombre += lineaArchivo[i++];
        }
        i++;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            documento += lineaArchivo[i++];
        }
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            departamento += lineaArchivo[i++];
        }
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            municipio += lineaArchivo[i++];
        }
        i += 2;

        tipo = lineaArchivo[i] - '0';
        i += 3;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            direccion += lineaArchivo[i++];
        }
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            precio = (precio * 10) + (lineaArchivo[i++] - '0');
        }
        i += 2;

        for (int a = 0; a < 5; a++)
        {
            iteraciones++;
            amenidades[a] = (lineaArchivo[i++] - '0');
            if (lineaArchivo[i] == ' ')
                i++;
        }
        i++;

        while (i < lineaArchivo.size())
        {
            iteraciones++;
            if (lineaArchivo[i] == '-')
                cantidadReservas++;
            i++;
        }

        reservas = new Reserva *[cantidadReservas];
        for (int a = 0; a < cantidadReservas; ++a)
        {
            iteraciones++;
            reservas[a] = nullptr;
        }

        alojamientos[cantidad++] = new Alojamiento(
            nombre, codigo, anfitrion,
            departamento, municipio, tipo,
            direccion, precio, amenidades, reservas, cantidadReservas);
    }

    archivo.close();
    return alojamientos;
}

template <class T>
T *buscarPorCodigo(T **datos, unsigned int cantidad, unsigned int codigoBuscado, unsigned int &iteraciones)
{
    int izquierda = 0, derecha = cantidad - 1;

    while (izquierda <= derecha)
    {
        iteraciones++;
        int medio = (izquierda + derecha) / 2;
        unsigned int codigoActual = datos[medio]->getCodigoIdentificador();

        if (codigoActual == codigoBuscado)
            return datos[medio];
        else if (codigoBuscado < codigoActual)
            derecha = medio - 1;
        else
            izquierda = medio + 1;
    }
    return nullptr;
}

Anfitrion **cargarAnfitriones(string nombreArchivo, unsigned int &cantidad, Alojamiento **alojamientosTotales, unsigned int cantidadAlojamientosTotales, unsigned int &iteraciones)
{
    unsigned int lineas = contarLineasArchivos(nombreArchivo, iteraciones), codigo;
    Anfitrion **anfitriones = new Anfitrion *[lineas];
    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    cantidad = 0;

    while (getline(archivo, lineaArchivo))
    {
        iteraciones++;
        unsigned char documentoAnfitrion[11];
        float puntuacion = 0.0;
        unsigned char antiguedadMeses = 0, cantidadAlojamientos = 0;
        unsigned int i = 0, prei = 0;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            documentoAnfitrion[i++] = lineaArchivo[i];
        }
        i += 2;

        string temPun = "";
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            temPun += lineaArchivo[i++];
        }
        puntuacion = stof(temPun);
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            antiguedadMeses = (antiguedadMeses * 10) + (lineaArchivo[i++] - '0');
        }
        i++;

        prei = i;
        while (i < lineaArchivo.size())
        {
            iteraciones++;
            if (lineaArchivo[i] == '-')
                cantidadAlojamientos++;
            i++;
        }

        codigo = 0;
        Alojamiento **alojamientos = new Alojamiento *[cantidadAlojamientos];
        unsigned int idx = 0;

        while (prei < lineaArchivo.size())
        {
            iteraciones++;
            prei++;
            if (lineaArchivo[prei] >= '0' && lineaArchivo[prei] <= '9')
            {
                codigo = (codigo * 10) + (lineaArchivo[prei] - '0');
            }
            else if (lineaArchivo[prei] == '-' || prei == lineaArchivo.size())
            {
                // Buscar en el arreglo
                Alojamiento *alojamientoEncontrado = buscarPorCodigo<Alojamiento>(alojamientosTotales, cantidadAlojamientosTotales, codigo,iteraciones);
                alojamientos[idx++] = alojamientoEncontrado;
                codigo = 0;
            }
        }

        // Crear el alojamiento
        anfitriones[cantidad] = new Anfitrion(documentoAnfitrion, puntuacion, antiguedadMeses, cantidadAlojamientos, alojamientos);

        for (unsigned int i = 0; i < cantidadAlojamientos; i++)
        {
            iteraciones++;
            alojamientos[i]->setAnfitrionResponsable((anfitriones[cantidad]));
        }
        cantidad++;
    }
    archivo.close();
    return anfitriones;
}

Reserva ***cargarReserva(string nombreArchivo, unsigned int &cantidad, unsigned int &bloques, unsigned int &fila, unsigned int &columna, unsigned int &cCodigo, Alojamiento **alojamientosTotales, unsigned int cantidadAlojamientosTotales, unsigned int &iteraciones)
{
    unsigned int lineas = contarLineasArchivos(nombreArchivo,iteraciones) - 1;
    bloques = (lineas / 10 > 8) ? (lineas / 10) : 8;

    Reserva ***reservas = new Reserva **[bloques * 2];
    for (unsigned int i = 0; i < bloques * 2; ++i)
    {
        iteraciones++;
        reservas[i] = new Reserva *[bloques];
        for (unsigned int j = 0; j < bloques; ++j)
        {
            iteraciones++;
            reservas[i][j] = nullptr;
        }
    }

    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    cantidad = 0;
    unsigned int i = 0;
    getline(archivo, lineaArchivo);
    while (lineaArchivo[i] != '-'){
        iteraciones++;
        cCodigo = (cCodigo * 10) + (lineaArchivo[i++] - '0');}
    while (getline(archivo, lineaArchivo))
    {
        iteraciones++;
        string anotaciones;
        unsigned char dia = 0, mes = 0, duracion = 0;
        unsigned short anio = 0;
        unsigned int monto = 0, codigoReserva = 0, codigoAlojamiento = 0;
        bool metodoDePago;
        Alojamiento *alojamientoReserva = nullptr;
        Huesped *huespedReserva = nullptr; // se asignará después

        i = 0;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            codigoReserva = (codigoReserva * 10) + (lineaArchivo[i++] - '0');
        }
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            codigoAlojamiento = (codigoAlojamiento * 10) + (lineaArchivo[i++] - '0');
        }
        alojamientoReserva = buscarPorCodigo<Alojamiento>(alojamientosTotales, cantidadAlojamientosTotales, codigoAlojamiento,iteraciones);

        i += 2;

        while (lineaArchivo[i] != '-')
        {
            iteraciones++;
            dia = (dia * 10) + (lineaArchivo[i++] - '0');
        }
        i++;
        while (lineaArchivo[i] != '-')
        {
            iteraciones++;
            mes = (mes * 10) + (lineaArchivo[i++] - '0');
        }
        i++;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            anio = (anio * 10) + (lineaArchivo[i++] - '0');
        }
        i += 2;

        Fecha fechaEntrada(dia, mes, anio);
        dia = 0;
        mes = 0;
        anio = 0;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            duracion = (duracion * 10) + (lineaArchivo[i++] - '0');
        }

        i += 2;

        while (lineaArchivo[i] != '-')
        {
            iteraciones++;
            dia = (dia * 10) + (lineaArchivo[i++] - '0');
        }
        i++;
        while (lineaArchivo[i] != '-')
        {
            iteraciones++;
            mes = (mes * 10) + (lineaArchivo[i++] - '0');
        }
        i++;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            anio = (anio * 10) + (lineaArchivo[i++] - '0');
        }
        i += 14;

        Fecha fechaSalida(dia, mes, anio);
        dia = 0;
        mes = 0;
        anio = 0;
        metodoDePago = (lineaArchivo[i] - '0');
        i += 3;
        while (lineaArchivo[i] != '-')
        {
            iteraciones++;
            dia = (dia * 10) + (lineaArchivo[i++] - '0');
        }
        i++;
        while (lineaArchivo[i] != '-')
        {
            iteraciones++;
            mes = (mes * 10) + (lineaArchivo[i++] - '0');
        }
        i++;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            anio = (anio * 10) + (lineaArchivo[i++] - '0');
        }
        Fecha fechaPago(dia, mes, anio);
        i += 2;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            monto = (monto * 10) + (lineaArchivo[i++] - '0');
        }
        i += 2;
        while (i < lineaArchivo.size())
        {
            iteraciones++;
            anotaciones += lineaArchivo[i++];
        }

        // Calcular fila y columna
        fila = cantidad / bloques;
        columna = cantidad % bloques;

        reservas[fila][columna] = new Reserva(anotaciones, fechaEntrada, fechaSalida, fechaPago, monto,
                                              huespedReserva, alojamientoReserva,
                                              codigoReserva, duracion, metodoDePago);

        for (unsigned char b = 0; b < alojamientoReserva->getCantidadReservas(); b++)
        {
            iteraciones++;
            if ((alojamientoReserva->getReservasVigentes())[b] == nullptr)
            {
                (alojamientoReserva->getReservasVigentes())[b] = reservas[fila][columna];
                break;
            }
        }
        cantidad++;
    }

    archivo.close();
    return reservas;
}

Reserva *buscarReservaPorCodigo(Reserva ***reservas, unsigned int filas, unsigned int columnas, unsigned int codigoBuscado, unsigned int &iteraciones)
{
    for (unsigned int i = 0; i < filas; ++i)
    {
        iteraciones++;
        if (!reservas[i])
            continue;

        for (unsigned int j = 0; j < columnas; ++j)
        {
            iteraciones++;
            if (!reservas[i][j])
                continue;
            if (reservas[i][j]->getCodigoIdentificador() == codigoBuscado)
            {
                return reservas[i][j];
            }
        }
    }
    return nullptr;
}

Huesped **cargarHuesped(string nombreArchivo, unsigned int &cantidad, Reserva ***reservasTotales, unsigned int filas, unsigned int bloques, unsigned int &iteraciones)
{
    unsigned int lineas = contarLineasArchivos(nombreArchivo,iteraciones), codigo;
    Huesped **huespeds = new Huesped *[lineas];
    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    cantidad = 0;

    while (getline(archivo, lineaArchivo))
    {
        iteraciones++;
        unsigned char documentoHuesped[11];
        float puntuacion = 0.0;
        unsigned char antiguedadMeses = 0, cantidadReservas = 0;
        unsigned int i = 0, prei = 0;
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            documentoHuesped[i++] = lineaArchivo[i];
        }
        i += 2;

        string temPun = "";
        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            temPun += lineaArchivo[i++];
        }
        puntuacion = stof(temPun);
        i += 2;

        while (lineaArchivo[i] != ',')
        {
            iteraciones++;
            antiguedadMeses = (antiguedadMeses * 10) + (lineaArchivo[i++] - '0');
        }
        i++;

        prei = i;
        while (i < lineaArchivo.size())
        {
            iteraciones++;
            if (lineaArchivo[i] == '-')
                cantidadReservas++;
            i++;
        }

        codigo = 0;
        Reserva **reservas = new Reserva *[cantidadReservas];
        unsigned int idx = 0;

        while (prei < lineaArchivo.size())
        {
            iteraciones++;
            prei++;
            if (lineaArchivo[prei] >= '0' && lineaArchivo[prei] <= '9')
            {
                codigo = (codigo * 10) + (lineaArchivo[prei] - '0');
            }
            else if (lineaArchivo[prei] == '-' && lineaArchivo[prei] != ' ')
            {
                // Buscar en el arreglo
                Reserva *reservaEncontrada = buscarReservaPorCodigo(reservasTotales, filas, bloques, codigo,iteraciones);
                reservas[idx++] = reservaEncontrada;
                codigo = 0;
            }
        }

        // Crear el alojamiento

        huespeds[cantidad] = new Huesped(documentoHuesped, puntuacion, antiguedadMeses, cantidadReservas, reservas);

        for (unsigned int j = 0; j < cantidadReservas; j++)
        {
            iteraciones++;
            if (reservas[j])
            {
                reservas[j]->setHuesped(huespeds[cantidad]);
            }
        }

        cantidad++;
    }
    archivo.close();
    return huespeds;
}

bool interseccionFechas(Alojamiento *alojamiento, Huesped *huesped, Fecha fechaInicio, Fecha fechaFin, unsigned int &iteraciones)
{
    for (unsigned char r = 0; r < alojamiento->getCantidadReservas(); r++)
    {
        iteraciones++;
        Reserva *reserva = alojamiento->getReservasVigentes()[r];
        if ((fechaInicio >= reserva->getFechaEntrada() && fechaInicio <= reserva->getFechaSalida()) || (fechaFin >= reserva->getFechaEntrada() && fechaFin <= reserva->getFechaSalida()))
        {
            return true;
        }
    }
    for (unsigned char r = 0; r < huesped->getCantidadReservas() - 1; r++)
    {
        iteraciones++;
        Reserva *reserva = huesped->getReservas()[r];
        if ((fechaInicio >= reserva->getFechaEntrada() && fechaInicio <= reserva->getFechaSalida()) || (fechaFin >= reserva->getFechaEntrada() && fechaFin <= reserva->getFechaSalida()))
        {
            return true;
        }
    }

    return false;
}

void actualizarHistorico(Reserva ***reservas, Fecha fecha, string nombreArchivo, unsigned int &cantidad, unsigned int filas, unsigned int columnas, unsigned int &iteraciones)
{
    ofstream archivo(nombreArchivo, ios::app);

    unsigned int k = 0;

    for (unsigned int i = 0; i < filas; ++i)
    {
        iteraciones++;
        if (!reservas[i])
            continue;

        for (unsigned int j = 0; j < columnas; ++j)
        {
            iteraciones++;
            if (reservas[i][j])
            {
                if (reservas[i][j]->getFechaEntrada() < fecha)
                {
                    Reserva *reTemp = reservas[i][j];
                    archivo << reTemp->getCodigoIdentificador() << ", " << reTemp->getAlojamientoReserva()->getCodigoIdentificador() << ", " << (int)reTemp->getFechaEntrada().getDia() << "-" << (int)reTemp->getFechaEntrada().getMes() << "-" << reTemp->getFechaEntrada().getAnio() << ", " << (int)reTemp->getDuracion() << ", " << (int)reTemp->getFechaSalida().getDia() << "-" << (int)reTemp->getFechaSalida().getMes() << "-" << reTemp->getFechaSalida().getAnio() << ", " << reTemp->getHuesped()->getDocumento() << ", " << reTemp->getMetodoPago() << ", " << (int)reTemp->getFechaPago().getDia() << "-" << (int)reTemp->getFechaPago().getMes() << "-" << reTemp->getFechaPago().getAnio() << ", " << reTemp->getMonto() << ", " << reTemp->getAnotaciones() << "\n";
                    reTemp->getHuesped()->eliminarReserva(reTemp->getCodigoIdentificador(),iteraciones);
                    reTemp->getAlojamientoReserva()->eliminarReserva(reTemp->getCodigoIdentificador(),iteraciones);
                    delete reservas[i][j];
                    reservas[i][j] = nullptr;
                    cantidad--;
                }
                else
                {
                    if (k < filas * columnas)
                    {
                        unsigned int filaNueva = k / columnas;
                        unsigned int columnaNueva = k % columnas;
                        if (i != filaNueva || j != columnaNueva)
                        {
                            reservas[filaNueva][columnaNueva] = reservas[i][j];
                            reservas[i][j] = nullptr;
                        }
                        k++;
                    }
                }
            }
        }
    }

    for (unsigned int i = k; i < filas * columnas; ++i)
    {
        iteraciones++;
        unsigned int filaNueva = i / columnas;
        unsigned int colNueva = i % columnas;
        reservas[filaNueva][colNueva] = nullptr;
    }

    archivo.close();
}

void guardarAlojamientos(const std::string &nombreArchivo, Alojamiento **alojamientos, int cantidad, unsigned int &iteraciones)
{
    if (!alojamientos)
        return;

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        return;
    }

    for (int i = 0; i < cantidad; ++i)
    {
        iteraciones++;
        Alojamiento *a = alojamientos[i];
        if (!a)
            continue;

        archivo << a->getCodigoIdentificador() << ", ";
        archivo << (!a->getNombreAlojamiento().empty() ? a->getNombreAlojamiento() : ", ") << ", ";

        unsigned char *doc = a->getAnfitrionRespon()->getDocumento();
        archivo << (doc ? std::string(reinterpret_cast<char *>(doc), 10) : ", ") << ", ";

        archivo << a->getDepartamento() << ", "
                << a->getMunicipio() << ", "
                << a->getTipo() << ", "
                << a->getDireccion() << ", "
                << a->getPrecioNoche() << ", ";

        bool *amenidades = a->getAmenidades();
        if (amenidades)
        {
            for (int j = 0; j < 5; ++j)
            {
                iteraciones++;
                archivo << (amenidades[j] ? 1 : 0);
                if (j < 4)
                    archivo << " ";
            }
        }
        else
        {
            archivo << "-";
        }
        archivo << ", ";

        Reserva **reservas = a->getReservasVigentes();
        unsigned char cantidadReservas = a->getCantidadReservas();

        if (reservas && cantidadReservas > 0)
        {
            for (int j = 0; j < cantidadReservas; ++j)
            {
                iteraciones++;
                archivo << reservas[j]->getCodigoIdentificador();
                archivo << " -";
            }
        }

        archivo << "\n";
    }

    archivo.close();
}

void guardarHuespedes(const std::string &nombreArchivo, Huesped **huespedes, int cantidad, unsigned int &iteraciones)
{
    if (!huespedes)
        return;

    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        std::cerr << "Error: No se pudo abrir " << nombreArchivo << std::endl;
        return;
    }

    for (int i = 0; i < cantidad; ++i)
    {
        iteraciones++;
        Huesped *h = huespedes[i];
        if (!h)
            continue;

        unsigned char *doc = h->getDocumento();
        archivo << (std::string(reinterpret_cast<char *>(doc), 10)) << ", ";
        archivo << h->getPuntuacion() << ", " << static_cast<int>(h->getAntiguedadMeses()) << ", ";

        Reserva **r = h->getReservas();
        unsigned char cantidadReservas = h->getCantidadReservas();

        if (r && cantidadReservas > 0)
        {
            for (int j = 0; j < cantidadReservas; ++j)
            {
                iteraciones++;
                archivo << r[j]->getCodigoIdentificador();
                if (j < cantidadReservas)
                    archivo << " - ";
            }
        }

        archivo << "\n";
    }

    archivo.close();
}

void guardarReservas(const std::string &nombreArchivo, Reserva ***reservas, unsigned int filas, unsigned int columnas, unsigned int cantidad, unsigned int &iteraciones)
{
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
        return;

    archivo << cantidad << "-\n";

    for (unsigned int i = 0; i < filas; ++i)
    {
        iteraciones++;
        for (unsigned int j = 0; j < columnas; ++j)
        {
            iteraciones++;
            if (!reservas[i][j])
                continue;

            Reserva *r = reservas[i][j];

            archivo << r->getCodigoIdentificador() << ", "
                    << r->getAlojamientoReserva()->getCodigoIdentificador() << ", "
                    << (int)r->getFechaEntrada().getDia() << "-"
                    << (int)r->getFechaEntrada().getMes() << "-"
                    << r->getFechaEntrada().getAnio() << ", "
                    << (int)r->getDuracion() << ", "
                    << (int)r->getFechaSalida().getDia() << "-"
                    << (int)r->getFechaSalida().getMes() << "-"
                    << r->getFechaSalida().getAnio() << ", ";

            unsigned char *doc = r->getHuesped()->getDocumento();
            for (int k = 0; k < 10; ++k){
                iteraciones++;
                archivo << static_cast<char>(doc[k]);}
            archivo << ", ";

            archivo << r->getMetodoPago() << ", "
                    << (int)r->getFechaPago().getDia() << "-"
                    << (int)r->getFechaPago().getMes() << "-"
                    << r->getFechaPago().getAnio() << ", "
                    << r->getMonto() << ", "
                    << r->getAnotaciones() << "\n";
        }
    }

    archivo.close();
}

void eliminarReserva(Reserva ***&reservas, unsigned int filasTotales, unsigned int columnasTotales, unsigned int &cantidadReservas, Huesped*& huesped, unsigned int &iteraciones)
{
    bool reservaExiste = false, reservaPertenece = false;
    unsigned int eliminarReserva = 0;
    cout << "Ingrese el codigo de la reserva a eliminar: ";
    cin >> eliminarReserva;

    for(unsigned int i = 0; i < huesped->getCantidadReservas();i++){
        iteraciones++;
        if(!huesped->getReservas()[i]) continue;
        if(huesped->getReservas()[i]->getCodigoIdentificador() == eliminarReserva){
            reservaPertenece = true;
            break;
        }
    }
    if(reservaPertenece){
        for (unsigned int i = 0; i < filasTotales; ++i)
        {
            iteraciones++;
            if (!reservas[i])
                continue;

            for (unsigned int j = 0; j < columnasTotales; ++j)
            {
                iteraciones++;
                if (!reservas[i][j])
                    continue;
                if (reservas[i][j]->getCodigoIdentificador() == eliminarReserva)
                {
                    reservas[i][j]->getHuesped()->eliminarReserva(eliminarReserva,iteraciones);
                    reservas[i][j]->getAlojamientoReserva()->eliminarReserva(eliminarReserva,iteraciones);
                    delete reservas[i][j];
                    reservas[i][j] = nullptr;
                    reservaExiste = true;
                }
            }
        }}
    if (reservaExiste)
    {
        cout << "Reserva eliminada correctamente";
        cantidadReservas--;
    }
    else{
        cout << "Ocurrio un problema: La reserva no te pertenece o no se encontro la reserva";
    }
}

void eliminarReserva(Reserva ***&reservas, unsigned int filasTotales, unsigned int columnasTotales, unsigned int &cantidadReservas, Anfitrion*& anfitrion, unsigned int &iteraciones){
    bool reservaExiste = false, reservaPertenece = false;
    unsigned int eliminarReserva = 0;
    cout << "Ingrese el codigo de la reserva a eliminar: ";
    cin >> eliminarReserva;

    for(unsigned int i = 0; i < anfitrion->getCantidadAlojamientos();i++){
        iteraciones++;
        for(unsigned int j = 0; j < anfitrion->getAlojamientos()[i]->getCantidadReservas();j++){
            iteraciones++;
            if(!anfitrion->getAlojamientos()[i]->getReservasVigentes()[j]) continue;
            if(anfitrion->getAlojamientos()[i]->getReservasVigentes()[j]->getCodigoIdentificador() == eliminarReserva){
                reservaPertenece = true;
                break;
            }
        }
    }
    if(reservaPertenece){
        for (unsigned int i = 0; i < filasTotales; ++i)
        {
            iteraciones++;
            if (!reservas[i])
                continue;

            for (unsigned int j = 0; j < columnasTotales; ++j)
            {
                iteraciones++;
                if (!reservas[i][j])
                    continue;
                if (reservas[i][j]->getCodigoIdentificador() == eliminarReserva)
                {
                    reservas[i][j]->getHuesped()->eliminarReserva(eliminarReserva,iteraciones);
                    reservas[i][j]->getAlojamientoReserva()->eliminarReserva(eliminarReserva,iteraciones);
                    delete reservas[i][j];
                    reservas[i][j] = nullptr;
                    reservaExiste = true;
                }
            }
        }}
    if (reservaExiste)
    {
        cout << "Reserva eliminada correctamente";
        cantidadReservas--;
    }
    else{
        cout << "Ocurrio un problema: La reserva no te pertenece o no se encontro la reserva";
    }

}

Alojamiento **reservaConFiltro(Alojamiento **alojamientos, unsigned int cantidadAlojamientos, Fecha fechaInicio, Fecha fechaFin, string municipio, unsigned int &cantidad, float puntuacion, unsigned int precio, unsigned int &iteraciones)
{
    Alojamiento **alojamientosDisponibles = new Alojamiento *[5];
    unsigned int guia = 0;
    cantidad = 5;
    for (unsigned int i = 0; i < cantidadAlojamientos; i++)
    {
        iteraciones++;
        if (!alojamientos[i])
            continue;
        Alojamiento *alTemp = alojamientos[i];
        bool visitado = false;
        for (unsigned int r = 0; r < alTemp->getCantidadReservas(); r++)
        {
            iteraciones++;
            if (alTemp->getReservasVigentes()[r])
            {
                Reserva *reTemp = alTemp->getReservasVigentes()[r];
                if (((fechaFin < reTemp->getFechaEntrada()) || (reTemp->getFechaEntrada() < fechaInicio)) && (alTemp->getMunicipio() == municipio) && (alTemp->getPrecioNoche() <= precio) && (alTemp->getAnfitrionRespon()->getPuntuacion() >= puntuacion) && (visitado == false))
                {
                    cout << "Nombre Alojamiento: " << alTemp->getNombreAlojamiento() << endl;
                    cout << "Codigo: " << alTemp->getCodigoIdentificador() << endl;
                    cout << "Direccion: " << alTemp->getDireccion() << endl
                         << endl;
                    visitado = true;
                    if (guia < cantidad)
                    {
                        alojamientosDisponibles[guia] = alTemp;
                    }
                    else
                    {
                        redimensionarArreglo(alojamientosDisponibles, cantidad, cantidad + 5,iteraciones);
                        cantidad += 5;
                        alojamientosDisponibles[guia] = alTemp;
                    }
                    guia++;
                }
            }
        }
    }
    return alojamientosDisponibles;
}

void imprimir(Reserva*& reserva){
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "CONFIRMACION DE LA RESERVA" << endl;
    cout << "Codigo: " << reserva->getCodigoIdentificador() << endl;
    cout << "Informacion del alojamiento" << endl;
    cout << "Nombre: " << reserva->getAlojamientoReserva()->getNombreAlojamiento() << endl;
    cout << "Codigo: " << reserva->getAlojamientoReserva()->getCodigoIdentificador() << endl;
    cout << "La reserva comienza un: " << reserva->getFechaEntrada().imprimirFecha() << endl;
    cout << "La reserva termina un: " << reserva->getFechaSalida().imprimirFecha() << endl;
}

void imprimir(unsigned int iteraciones, size_t tamanioObjetos){
    cout << "Cantidad de iteraciones: " << iteraciones << endl;
    cout << "Tamanio de los objetos: " << tamanioObjetos << endl;
}
