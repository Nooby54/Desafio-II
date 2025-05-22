#include "miscelaneos.h"
#include "huesped.h"
#include <algorithm>
#include <bitset>
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



