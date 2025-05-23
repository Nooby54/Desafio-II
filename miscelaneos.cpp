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

    while (getline(archivo, lineaArchivo)) {
        unsigned int codigo = 0, precio = 0, i = 0;
        string nombre = "", documento = "", departamento = "", municipio = "", direccion = "";
        bool amenidades[5], tipo;
        Reserva** reservas = nullptr;
        Anfitrion* anfitrion = nullptr;
        unsigned char cantidadReservas = 0;

        // 1. Código
        while (lineaArchivo[i] != ',') {
            codigo = (codigo * 10) + (lineaArchivo[i] - '0');
            i++;
        }
        i+=2;

        // 2. Nombre
        while (lineaArchivo[i] != ',') {
            nombre += lineaArchivo[i++];
        }
        i++;

        // 3. Documento anfitrión
        while (lineaArchivo[i] != ',') {
            documento += lineaArchivo[i++];
        }
        i+=2;

        // 4. Departamento
        while (lineaArchivo[i] != ',') {
            departamento += lineaArchivo[i++];
        }
        i+=2;

        // 5. Municipio
        while (lineaArchivo[i] != ',') {
            municipio += lineaArchivo[i++];
        }
        i+=2;

        // 6. Tipo
        tipo = lineaArchivo[i] - '0';
        i+=3;
        // 7. Dirección
        while (lineaArchivo[i] != ',') {
            direccion += lineaArchivo[i++];
        }
        i+=2;
        // 8. Precio
        while (lineaArchivo[i] != ',') {
            precio = (precio * 10) + (lineaArchivo[i++] - '0');
        }
        i+=2;

        // 9. Amenidades
        for (int a = 0; a < 5; a++) {
            //cout << nombre << (lineaArchivo[i++] - '0');
            amenidades[a] = (lineaArchivo[i++] - '0');
            if (lineaArchivo[i] == ' ') i++;
        }
        i++;

        // 10. Reservas (solo contamos cantidad)
        while (i < lineaArchivo.size()) {
            if (lineaArchivo[i] == '-') cantidadReservas++;
            i++;
        }

        reservas = new Reserva*[cantidadReservas];
        for (int a = 0; a < cantidadReservas; ++a){
            reservas[a] = nullptr;}

        // Crear el alojamiento
        alojamientos[cantidad++] = new Alojamiento(
            nombre, codigo, anfitrion,
            departamento, municipio, tipo,
            direccion, precio, amenidades, reservas, cantidadReservas);
    }

    archivo.close();
    return alojamientos;
}

Alojamiento* buscarAlojamientoPorCodigo(Alojamiento** alojamientos, unsigned int cantidad, unsigned int codigoBuscado) {
    int izquierda = 0, derecha = cantidad - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        unsigned int codigoActual = alojamientos[medio]->getCodigoIdentificador();

        if (codigoActual == codigoBuscado)
            return alojamientos[medio];
        else if (codigoBuscado < codigoActual)
            derecha = medio - 1;
        else
            izquierda = medio + 1;
    }
    return nullptr; // no encontrado
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
                Alojamiento* alojamientoEncontrado = buscarAlojamientoPorCodigo(alojamientosTotales, cantidadAlojamientosTotales, codigo);
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
