#include "miscelaneos.h"
#include "alojamiento.h"
#include "huesped.h"
#include <iostream>
#include <fstream>

using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short int a)
{
    if (m < 1 || m > 12) return false;


    unsigned char diasMes = 31;
    if (m == 2)
        diasMes = ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 29 : 28;
    else if (m == 4 || m == 6 || m == 9 || m == 11)
        diasMes = 30;

    return (d >= 1 && d <= diasMes);
}

string validarAnotaciones(){
    string anotaciones;
    cout << "Ingrese las anotaciones: ";
    cin >> anotaciones;
    while(anotaciones.length()>1000){
        cout << "Demasiadas anotaciones, intenta ser mas preciso";
        cin >> anotaciones;
        }
    return anotaciones;
}

Fecha validarFecha(string id){
    string dia, mes;
    unsigned short int anio;
    do{
        cout << "Ingrese el dia de " + id + ": ";
        cin >> dia;

        cout << "Ingrese el mes de " + id + ": ";
        cin >> mes;

        cout << "Ingrese el anio de " + id + ": ";
        cin >> anio;
    }
    while(!esValida(static_cast<unsigned char>(stoi(dia)),static_cast<unsigned char>(stoi(mes)),anio));
    return Fecha(*dia.c_str(),*mes.c_str(),anio);
}

bool validarMetodoDePago(){
    bool metodoDePago;
    cout << "Ingrese el metodo de pago: \n (0) Para PSE \n (1) Tarjeta de credito \n";
    cin >> metodoDePago;

    return metodoDePago;
}

unsigned int contarLineasArchivos(string nombreArchivo){
    unsigned int contadorLineas = 0;
    ifstream archivo;
    string linea;

    archivo.open(nombreArchivo);

    while(getline(archivo,linea)){
        contadorLineas++;}

    archivo.close();
    return contadorLineas;
}

Alojamiento** cargarAlojamientos(string nombreArchivo, unsigned int &cantidad) {
    unsigned int lineas = contarLineasArchivos(nombreArchivo);
    Alojamiento** alojamientos = new Alojamiento*[lineas];

    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    getline(archivo, lineaArchivo);
    while (getline(archivo, lineaArchivo)) {
        unsigned int codigo = 0, precio = 0, i = 0;
        string nombre = "", documento = "", departamento = "", municipio = "", direccion = "";
        bool amenidades[5], tipo;
        Reserva** reservas = nullptr;
        Anfitrion* anfitrion = nullptr;
        unsigned char cantidadReservas = 0;

        while (lineaArchivo[i] != ',') {
            codigo = (codigo * 10) + (lineaArchivo[i] - '0');
            i++;
        }
        i+=2;

        while (lineaArchivo[i] != ',') {
            nombre += lineaArchivo[i++];
        }
        i++;

        while (lineaArchivo[i] != ',') {
            documento += lineaArchivo[i++];
        }
        i+=2;

        while (lineaArchivo[i] != ',') {
            departamento += lineaArchivo[i++];
        }
        i+=2;

        while (lineaArchivo[i] != ',') {
            municipio += lineaArchivo[i++];
        }
        i+=2;

        tipo = lineaArchivo[i] - '0';
        i+=3;

        while (lineaArchivo[i] != ',') {
            direccion += lineaArchivo[i++];
        }
        i+=2;

        while (lineaArchivo[i] != ',') {
            precio = (precio * 10) + (lineaArchivo[i++] - '0');
        }
        i+=2;

        for (int a = 0; a < 5; a++) {
            amenidades[a] = (lineaArchivo[i++] - '0');
            if (lineaArchivo[i] == ' ') i++;
        }
        i++;

        while (i < lineaArchivo.size()) {
            if (lineaArchivo[i] == '-') cantidadReservas++;
            i++;
        }

        reservas = new Reserva*[cantidadReservas];
        for (int a = 0; a < cantidadReservas; ++a){
            reservas[a] = nullptr;}

        alojamientos[cantidad++] = new Alojamiento(
            nombre, codigo, anfitrion,
            departamento, municipio, tipo,
            direccion, precio, amenidades, reservas, cantidadReservas);
    }

    archivo.close();
    return alojamientos;
}

template< class T > T* buscarPorCodigo(T** datos, unsigned int cantidad, unsigned int codigoBuscado ) {
    int izquierda = 0, derecha = cantidad - 1;

    while (izquierda <= derecha) {
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

Anfitrion** cargarAnfitriones(string nombreArchivo, unsigned int &cantidad, Alojamiento** alojamientosTotales, unsigned int cantidadAlojamientosTotales){
    unsigned int lineas = contarLineasArchivos(nombreArchivo), codigo;
    Anfitrion** anfitriones = new Anfitrion*[lineas];
    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    cantidad = 0;

    while (getline(archivo, lineaArchivo)) {
        unsigned char documentoAnfitrion[11];
        float puntuacion = 0.0;
        unsigned char antiguedadMeses = 0, cantidadAlojamientos = 0;
        unsigned int i = 0, prei = 0;
        while(lineaArchivo[i] != ','){
            documentoAnfitrion[i++] = lineaArchivo[i];
        }
        i+=2;

        string temPun = "";
        while(lineaArchivo[i] != ','){
            temPun += lineaArchivo[i++];
        }
        puntuacion = stof(temPun);
        i+=2;

        while(lineaArchivo[i] != ','){
            antiguedadMeses = (antiguedadMeses * 10) + (lineaArchivo[i++] - '0');
        }
        i++;

        prei = i;
        while (i < lineaArchivo.size()) {
            if (lineaArchivo[i] == '-') cantidadAlojamientos++;
            i++;
        }


        codigo = 0;
        Alojamiento** alojamientos = new Alojamiento*[cantidadAlojamientos];
        unsigned int idx = 0;

        while (prei < lineaArchivo.size()) {
            prei++;
            if (lineaArchivo[prei] >= '0' && lineaArchivo[prei] <= '9') {
                codigo = (codigo * 10) + (lineaArchivo[prei] - '0');
            }
            else if (lineaArchivo[prei] == '-' || prei == lineaArchivo.size()) {
                // Buscar en el arreglo
                Alojamiento* alojamientoEncontrado = buscarPorCodigo<Alojamiento>(alojamientosTotales, cantidadAlojamientosTotales, codigo);
                alojamientos[idx++] = alojamientoEncontrado;
                codigo = 0;
            }
        }


        // Crear el alojamiento
        anfitriones[cantidad] = new Anfitrion(documentoAnfitrion, puntuacion, antiguedadMeses, cantidadAlojamientos, alojamientos);

        for(unsigned int i = 0; i < cantidadAlojamientos; i++){
            alojamientos[i]->setAnfitrionResponsable((anfitriones[cantidad]));
        }
        cantidad++;
    }
    archivo.close();
    return anfitriones;
}

Reserva*** cargarReserva(string nombreArchivo, unsigned int &cantidad, unsigned int &bloques, unsigned int &fila, unsigned int &columna, unsigned int& cCodigo, Alojamiento** alojamientosTotales, unsigned int cantidadAlojamientosTotales) {
    unsigned int lineas = contarLineasArchivos(nombreArchivo) - 1;
    bloques = (lineas / 10 > 8) ? (lineas / 10) : 8;

    Reserva*** reservas = new Reserva**[bloques * 2];
    for (unsigned int i = 0; i < bloques * 2; ++i) {
        reservas[i] = new Reserva*[bloques];
        for (unsigned int j = 0; j < bloques; ++j) {
            reservas[i][j] = nullptr;
        }
    }

    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    cantidad = 0;
    unsigned int i = 0;
    getline(archivo, lineaArchivo);
    while( lineaArchivo[i] != '-')
        cCodigo = (cCodigo*10) + (lineaArchivo[i++] - '0');
    while (getline(archivo, lineaArchivo)) {
        string anotaciones;
        unsigned char dia = 0, mes = 0, duracion = 0;
        unsigned short anio = 0;
        unsigned int monto = 0, codigoReserva = 0, codigoAlojamiento = 0;
        bool metodoDePago;
        Alojamiento* alojamientoReserva = nullptr;
        Huesped* huespedReserva = nullptr; // se asignará después

        i = 0;
        while(lineaArchivo[i] != ','){
            codigoReserva = (codigoReserva * 10) + (lineaArchivo[i++] - '0');
        }
        i+=2;

        while(lineaArchivo[i] != ','){
            codigoAlojamiento = (codigoAlojamiento * 10) + (lineaArchivo[i++] - '0');
        }
        alojamientoReserva = buscarPorCodigo<Alojamiento>(alojamientosTotales, cantidadAlojamientosTotales, codigoAlojamiento);

        i+=2;

        while(lineaArchivo[i] != '-'){
            dia = (dia*10) + (lineaArchivo[i++]-'0');
        }
        i++;
        while(lineaArchivo[i] != '-'){
            mes = (mes*10) + (lineaArchivo[i++]-'0');
        }
        i++;
        while(lineaArchivo[i] != ','){
            anio = (anio*10)+(lineaArchivo[i++]-'0');
        }
        i+=2;

        Fecha fechaEntrada(dia,mes,anio);
        dia = 0;
        mes = 0;
        anio = 0;

        while(lineaArchivo[i] != ','){
            duracion = (duracion*10) + (lineaArchivo[i++] - '0');
        }

        i+=2;

        while(lineaArchivo[i] != '-'){
            dia = (dia*10) + (lineaArchivo[i++]-'0');
        }
        i++;
        while(lineaArchivo[i] != '-'){
            mes = (mes*10) + (lineaArchivo[i++]-'0');
        }
        i++;
        while(lineaArchivo[i] != ','){
            anio = (anio*10)+(lineaArchivo[i++]-'0');
        }
        i+=14;

        Fecha fechaSalida(dia,mes,anio);
        dia = 0;
        mes = 0;
        anio = 0;
        metodoDePago = (lineaArchivo[i] - '0');
        i+=3;
        while(lineaArchivo[i] != '-'){
            dia = (dia*10) + (lineaArchivo[i++]-'0');
        }
        i++;
        while(lineaArchivo[i] != '-'){
            mes = (mes*10) + (lineaArchivo[i++]-'0');
        }
        i++;
        while(lineaArchivo[i] != ','){
            anio = (anio*10)+(lineaArchivo[i++]-'0');
        }
        Fecha fechaPago(dia,mes,anio);
        i+=2;
        while(lineaArchivo[i] != ','){
            monto = (monto*10) + (lineaArchivo[i++] - '0');
        }
        i+=2;
        while (i < lineaArchivo.size()) {
            anotaciones+= lineaArchivo[i++];
        }

        // Calcular fila y columna
        fila = cantidad / bloques;
        columna = cantidad % bloques;

        reservas[fila][columna] = new Reserva(anotaciones, fechaEntrada, fechaSalida, fechaPago, monto,
                                              huespedReserva, alojamientoReserva,
                                              codigoReserva, duracion, metodoDePago);

        for(unsigned char b = 0; b < alojamientoReserva->getCantidadReservas(); b++){
            if((alojamientoReserva->getReservasVigentes())[b] == nullptr){
                (alojamientoReserva->getReservasVigentes())[b] = reservas[fila][columna];
                break;
            }
        }
        cantidad++;
    }

    archivo.close();
    return reservas;
}

Reserva* buscarReservaPorCodigo(Reserva*** reservas, unsigned int filas, unsigned int columnas, unsigned int codigoBuscado) {
    for (unsigned int i = 0; i < filas; ++i) {
        if (reservas[i] == nullptr || reservas[i][0] == nullptr || reservas[i][columnas - 1] == nullptr)
            continue;

        unsigned int codMin = reservas[i][0]->getCodigoIdentificador();
        unsigned int codMax = reservas[i][columnas - 1]->getCodigoIdentificador();
        if (codigoBuscado < codMin || codigoBuscado > codMax)
            continue;

        int low = 0;
        int high = columnas - 1;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (!reservas[i][mid]) {
                int left = mid - 1, right = mid + 1;
                while (left >= low || right <= high) {
                    if (left >= low && reservas[i][left]) {
                        mid = left;
                        break;
                    }
                    if (right <= high && reservas[i][right]) {
                        mid = right;
                        break;
                    }
                    --left; ++right;
                }
                if (left < low && right > high) break;
            }

            unsigned int codigoActual = reservas[i][mid]->getCodigoIdentificador();
            if (codigoActual == codigoBuscado) {
                return reservas[i][mid];
            } else if (codigoBuscado < codigoActual) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
    }

    return nullptr;
}

Huesped** cargarHuesped(string nombreArchivo, unsigned int &cantidad, Reserva*** reservasTotales, unsigned int filas, unsigned int bloques){
    unsigned int lineas = contarLineasArchivos(nombreArchivo), codigo;
    Huesped** huespeds= new Huesped*[lineas];
    ifstream archivo(nombreArchivo);
    string lineaArchivo;
    cantidad = 0;

    while (getline(archivo, lineaArchivo)) {
        unsigned char documentoHuesped[11];
        float puntuacion = 0.0;
        unsigned char antiguedadMeses = 0, cantidadReservas = 0;
        unsigned int i = 0, prei = 0;
        while(lineaArchivo[i] != ','){
            documentoHuesped[i++] = lineaArchivo[i];
        }
        i+=2;

        string temPun = "";
        while(lineaArchivo[i] != ','){
            temPun += lineaArchivo[i++];
        }
        puntuacion = stof(temPun);
        i+=2;

        while(lineaArchivo[i] != ','){
            antiguedadMeses = (antiguedadMeses * 10) + (lineaArchivo[i++] - '0');
        }
        i++;

        prei = i;
        while (i < lineaArchivo.size()) {
            if (lineaArchivo[i] == '-') cantidadReservas++;
            i++;
        }


        codigo = 0;
        Reserva** reservas = new Reserva*[cantidadReservas];
        unsigned int idx = 0;

        while (prei < lineaArchivo.size()) {
            prei++;
            if (lineaArchivo[prei] >= '0' && lineaArchivo[prei] <= '9') {
                codigo = (codigo * 10) + (lineaArchivo[prei] - '0');
            }
            else if (lineaArchivo[prei] == '-' || prei == lineaArchivo.size()) {
                // Buscar en el arreglo
                Reserva* reservaEncontrada = buscarReservaPorCodigo(reservasTotales, filas, bloques, codigo);
                reservas[idx++] = reservaEncontrada;
                codigo = 0;
            }
        }


        // Crear el alojamiento

        huespeds[cantidad] = new Huesped(documentoHuesped, puntuacion, antiguedadMeses, cantidadReservas, reservas);

        for (unsigned int j = 0; j < cantidadReservas; j++) {
            if (reservas[j]) {
                reservas[j]->setHuesped(huespeds[cantidad]);
            }
        }

        cantidad++;
    }
    archivo.close();
    return huespeds;
}

