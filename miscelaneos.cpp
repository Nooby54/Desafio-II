#include "miscelaneos.h"
#include "alojamiento.h"
#include "huesped.h"
#include <iostream>
#include <fstream>

using namespace std;

bool esValida(unsigned char d, unsigned char m, unsigned short int a)
{
    /**
 * @brief Verifica si una fecha específica es válida según el calendario gregoriano.
 *
 * Esta función comprueba si una fecha dada (día, mes y año) corresponde a una fecha válida,
 * teniendo en cuenta la cantidad de días en cada mes y los años bisiestos.
 * El mes debe estar en el rango de 1 a 12, y el día debe estar dentro del rango permitido
 * por el mes correspondiente. Para febrero, se consideran los años bisiestos.
 *
 * @param d Día del mes (1 a 31, dependiendo del mes y año).
 * @param m Mes del año (1 a 12).
 * @param a Año en formato de cuatro dígitos (por ejemplo, 2024).
 * @return `true` si la fecha es válida según las reglas del calendario gregoriano, `false` en caso contrario.
 *
 */
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
    /**
 * @brief Solicita y valida una cadena de anotaciones ingresada por el usuario.
 *
 * Esta función permite al usuario ingresar un texto libre como anotaciones. Si el texto ingresado supera
 * los 1000 caracteres, se solicita al usuario que lo reduzca. Se realiza un seguimiento del número de
 * intentos fallidos mediante una referencia al parámetro `iteraciones`, que se incrementa cada vez que
 * el usuario excede el límite permitido de caracteres.
 *
 * @param iteraciones Parámetro de entrada/salida que cuenta cuántas veces el usuario excedió el límite
 *                    de caracteres permitido (más de 1000 caracteres).
 * @return Una cadena de texto (`std::string`) con las anotaciones validadas, con una longitud máxima de 1000 caracteres.
 *
 * @note La entrada vacía (presionar enter sin escribir nada) se acepta como válida.
 */

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
    /**
 * @brief Solicita al usuario una fecha válida (día, mes y año) y la devuelve como un objeto `Fecha`.
 *
 * Esta función guía al usuario en la introducción de una fecha válida mediante entradas separadas para día,
 * mes y año. Se valida que los valores numéricos ingresados sean apropiados y que la fecha resultante sea
 * coherente según el calendario gregoriano (incluyendo el manejo de años bisiestos).
 *
 * La función repite la solicitud de entrada hasta que se obtiene una fecha válida. También lleva un conteo
 * del número total de intentos realizados a través del parámetro `iteraciones`, que se incrementa cada vez
 * que el usuario proporciona un valor no válido (día, mes o una fecha completa inválida).
 *
 * @param id Cadena descriptiva que se mostrará al usuario para contextualizar la fecha (por ejemplo: "inicio", "nacimiento").
 * @param iteraciones Parámetro de entrada/salida que contará el número de veces que el usuario cometió errores de entrada.
 * @return Objeto `Fecha` que representa la fecha validada (día, mes, año).
 *
 * @note Se utiliza `std::stoi` para convertir las cadenas ingresadas a enteros. Si la conversión falla, se vuelve a solicitar la entrada.

 */
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
    /**
 * @brief Solicita al usuario que seleccione un método de pago y devuelve su elección.
 *
 * Esta función muestra un menú simple con dos opciones de método de pago: PSE (opción 0)
 * o tarjeta de crédito (opción 1). La entrada se interpreta como un valor booleano:
 * - `false` (0) representa PSE.
 * - `true` (1) representa tarjeta de crédito.
 *
 * @return Valor booleano que representa el método de pago seleccionado:
 *         `false` para PSE, `true` para tarjeta de crédito.
*/


    bool metodoDePago;
    cout << "(0) Para PSE \n (1) Tarjeta de credito \nIngrese el metodo de pago: ";
    cin >> metodoDePago;

    return metodoDePago;
}

unsigned int contarLineasArchivos(string nombreArchivo, unsigned int &iteraciones)
{
    /**
 * @brief Cuenta la cantidad de líneas en un archivo de texto.
 *
 * Esta función abre un archivo de texto especificado por su nombre y recorre línea por línea,
 * incrementando un contador por cada línea leída exitosamente. También incrementa un contador
 * externo (`iteraciones`) para llevar un registro de cuántas líneas se procesaron.
 *
 * @param nombreArchivo Nombre (o ruta) del archivo de texto a analizar.
 * @param iteraciones Parámetro de entrada/salida que se incrementa por cada línea leída,
 *                    útil para fines estadísticos o de control.
 * @return Número total de líneas encontradas en el archivo.
 */

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
    /**
 * @brief Carga alojamientos desde un archivo de texto y los almacena en memoria dinámica.
 *
 * Esta función lee un archivo de texto línea por línea, donde cada línea contiene la información
 * serializada de un alojamiento (incluyendo su código, nombre, ubicación, precio, tipo, amenidades
 * y cantidad de reservas). Por cada línea, se crea dinámicamente un objeto `Alojamiento`, que se
 * guarda en un arreglo de punteros a alojamientos. También se inicializan las reservas como punteros
 * nulos, y el anfitrión se establece como `nullptr`.
 *
 * @param nombreArchivo Nombre o ruta del archivo desde el cual se cargan los alojamientos.
 * @param cantidad Parámetro de salida que se incrementa por cada alojamiento leído correctamente.
 * @param iteraciones Contador de pasos o acciones realizadas durante la ejecución, útil para fines de trazabilidad.
 *
 * @return Un arreglo dinámico de punteros a objetos `Alojamiento`, con cada entrada correspondiente
 *         a una línea del archivo. La memoria debe ser liberada manualmente por el usuario.
 */

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
    /**
 * @brief Realiza una búsqueda binaria para encontrar un objeto por su código identificador.
 *
 * Esta función plantilla implementa el algoritmo de búsqueda binaria sobre un arreglo de punteros a
 * objetos de tipo `T`. Se asume que el arreglo está ordenado de forma ascendente según el valor
 * retornado por el método `getCodigoIdentificador()` de los objetos. Si se encuentra un objeto con
 * el código buscado, se retorna un puntero al mismo; de lo contrario, se retorna `nullptr`.
 *
 * @tparam T Tipo del objeto al que apunta el arreglo. Debe contar con el método público
 *           `unsigned int getCodigoIdentificador() const`.
 *
 * @param datos Arreglo de punteros a objetos del tipo `T` ordenados por código.
 * @param cantidad Cantidad de elementos en el arreglo.
 * @param codigoBuscado Código identificador que se desea localizar.
 * @param iteraciones Contador de iteraciones del ciclo de búsqueda, útil para propósitos estadísticos o de depuración.
 *
 * @return Puntero al objeto cuyo código coincide con `codigoBuscado`, o `nullptr` si no se encuentra.
 *
 * @note El arreglo `datos` debe estar ordenado previamente por el valor retornado por
 *       `getCodigoIdentificador()`, de lo contrario los resultados serán impredecibles.
 */

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
    /**
 * @brief Carga desde un archivo los datos de anfitriones y vincula sus alojamientos correspondientes.
 *
 * Esta función lee un archivo de texto que contiene los datos de anfitriones, incluyendo su documento,
 * puntuación, antigüedad en meses y la lista de códigos de alojamientos asociados. Por cada línea del
 * archivo, se crea dinámicamente un objeto `Anfitrion`, se vinculan los objetos `Alojamiento` correspondientes,
 * y se actualiza en cada alojamiento la referencia al anfitrión responsable.
 *
 * @param nombreArchivo Nombre del archivo de texto que contiene los datos de los anfitriones.
 * @param cantidad Variable pasada por referencia donde se almacenará la cantidad de anfitriones cargados.
 * @param alojamientosTotales Arreglo con todos los alojamientos disponibles en el sistema.
 * @param cantidadAlojamientosTotales Cantidad total de alojamientos en el arreglo anterior.
 * @param iteraciones Contador de operaciones realizadas (lectura, búsqueda, creación, etc.), útil para análisis estadístico.
 *
 * @return Puntero a un arreglo dinámico de punteros a objetos `Anfitrion`, conteniendo todos los anfitriones cargados.
 */

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
    /**
 * @brief Carga las reservas desde un archivo de texto y las almacena en una matriz dinámica 2D de punteros.
 *
 * Esta función lee un archivo de texto que contiene información sobre reservas realizadas en alojamientos,
 * asignando dinámicamente objetos `Reserva` en una matriz 2D que puede crecer en bloques. Cada reserva
 * queda vinculada a su alojamiento correspondiente y será añadida a la lista de reservas vigentes de dicho alojamiento.
 *
 * @param nombreArchivo Nombre del archivo que contiene los datos de las reservas.
 * @param cantidad Variable pasada por referencia donde se almacena la cantidad de reservas cargadas.
 * @param bloques Variable pasada por referencia, contiene la cantidad de columnas asignadas en la matriz.
 * @param fila Variable pasada por referencia donde se almacena la última fila utilizada.
 * @param columna Variable pasada por referencia donde se almacena la última columna utilizada.
 * @param cCodigo Variable pasada por referencia que almacena el código correlativo de reservas.
 * @param alojamientosTotales Arreglo con todos los alojamientos disponibles.
 * @param cantidadAlojamientosTotales Cantidad total de alojamientos en el arreglo.
 * @param iteraciones Contador de operaciones realizadas (lectura, parsing, asignación, etc.).
 *
 * @return Una matriz dinámica 2D de punteros a `Reserva`, con las reservas organizadas por bloques.
 */

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
    /**
 * @brief Busca una reserva específica por su código identificador dentro de una matriz 2D de reservas.
 *
 * Esta función recorre una matriz dinámica 2D de punteros a `Reserva` buscando una reserva
 * cuyo código identificador coincida con `codigoBuscado`. Devuelve un puntero a la reserva
 * encontrada o nullptr si no existe.
 *
 * @param reservas Matriz 2D de punteros a `Reserva` donde se buscará la reserva.
 * @param filas Número de filas de la matriz.
 * @param columnas Número de columnas de la matriz.
 * @param codigoBuscado Código identificador de la reserva que se desea encontrar.
 * @param iteraciones Contador de iteraciones y operaciones para medir eficiencia o complejidad.
 *
 * @return Puntero a la reserva encontrada con el código buscado, o nullptr si no existe.
 *
 * @note La función ignora punteros nulos en la matriz.
 * @note El contador `iteraciones` se incrementa por cada acceso o comparación realizada.
 */

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
    /**
 * @brief Carga huéspedes desde un archivo de texto y asocia sus reservas correspondientes.
 *
 * Esta función lee un archivo de texto línea por línea, donde cada línea representa un huésped con su
 * documento, puntuación, antigüedad en meses y una lista de códigos de reservas separados por guiones.
 * Por cada huésped, crea un objeto Huesped dinámicamente y asocia los punteros a las reservas correspondientes
 * buscadas en la matriz tridimensional de reservas proporcionada.
 *
 * Además, se incrementa un contador de iteraciones para seguimiento de procesamiento, y se actualiza
 * la cantidad de huéspedes cargados por referencia.
 *
 * @param nombreArchivo Ruta del archivo de texto que contiene los datos de los huéspedes.
 * @param cantidad Referencia para almacenar la cantidad total de huéspedes cargados.
 * @param reservasTotales Matriz tridimensional de punteros a Reserva donde se buscarán las reservas asociadas.
 * @param filas Cantidad de filas en la matriz de reservas.
 * @param bloques Cantidad de columnas (bloques) en la matriz de reservas.
 * @param iteraciones Referencia a un contador para registrar el número de iteraciones realizadas.
 *
 * @return Arreglo dinámico de punteros a objetos Huesped cargados desde el archivo.
 */

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
    /**
 * @brief Verifica si existe intersección entre un rango de fechas dado y las fechas de reservas de un alojamiento y un huésped.
 *
 * Esta función examina las reservas vigentes del alojamiento y las reservas del huésped para determinar
 * si el intervalo de fechas [fechaInicio, fechaFin] se solapa con alguna de las reservas existentes.
 * Se incrementa el contador de iteraciones para llevar un registro de la cantidad de comprobaciones realizadas.
 *
 * La intersección se verifica si la fechaInicio o fechaFin cae dentro del rango de fechas de cualquier reserva.
 *
 * @param alojamiento Puntero al objeto Alojamiento que contiene las reservas vigentes a revisar.
 * @param huesped Puntero al objeto Huesped cuyas reservas también serán revisadas.
 * @param fechaInicio Fecha inicial del intervalo a verificar.
 * @param fechaFin Fecha final del intervalo a verificar.
 * @param iteraciones Referencia a un contador que se incrementa con cada iteración realizada en la búsqueda.
 *
 * @return true si alguna reserva del alojamiento o del huésped intersecta con el rango de fechas dado.
 * @return false si no se encuentra intersección con ninguna reserva.
 */

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
{/**
 * @brief Actualiza el archivo histórico con reservas anteriores a una fecha dada y reorganiza el arreglo de reservas.
 *
 * Esta función recorre una matriz tridimensional de punteros a reservas, identifica aquellas cuyo
 * fecha de entrada es anterior a la fecha especificada, las guarda en un archivo de texto en modo
 * append, elimina la reserva de las listas del huésped y del alojamiento correspondiente, y libera
 * la memoria asociada. Además, compacta la matriz de reservas para eliminar huecos producidos por
 * las reservas eliminadas, colocando las reservas válidas al inicio de la estructura.
 * Finalmente, rellena con nullptr las posiciones sobrantes.
 *
 * @param reservas Matriz tridimensional (filas x columnas) de punteros a objetos Reserva.
 * @param fecha Fecha límite para considerar una reserva como histórica (todas las reservas anteriores a esta fecha serán archivadas y eliminadas).
 * @param nombreArchivo Nombre del archivo donde se almacenan las reservas históricas (se abre en modo append).
 * @param cantidad Referencia a la cantidad total de reservas actuales; se actualiza tras eliminar reservas históricas.
 * @param filas Cantidad de filas en la matriz de reservas.
 * @param columnas Cantidad de columnas en la matriz de reservas.
 * @param iteraciones Referencia a un contador que se incrementa con cada iteración del proceso, para control de eficiencia.
 *
 * @note La función elimina la memoria de las reservas archivadas y actualiza las estructuras de datos asociadas.
 * @note El arreglo 'reservas' queda compactado, con reservas activas al inicio y nullptr en las posiciones vacías.
 */

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

void guardarArchivos(const string &nombreArchivo, Alojamiento **alojamientos, int cantidad, unsigned int &iteraciones)
{
    /**
 * @brief Guarda la información de un arreglo de alojamientos en un archivo de texto.
 *
 * Esta función escribe en un archivo los datos principales de cada objeto Alojamiento
 * contenido en un arreglo, serializando sus atributos básicos y algunos datos relacionados,
 * como las amenidades y los identificadores de las reservas vigentes.
 *
 * @param nombreArchivo Nombre del archivo donde se almacenarán los datos (sobrescribe el contenido existente).
 * @param alojamientos Arreglo de punteros a objetos Alojamiento que se desean guardar.
 * @param cantidad Número total de alojamientos en el arreglo.
 * @param iteraciones Referencia a un contador que se incrementa en cada iteración significativa, para medir eficiencia o trazabilidad.
 *
 * @note Se verifica que el arreglo de alojamientos y el archivo se hayan abierto correctamente.
 * @note Para las amenidades, se almacenan 5 valores binarios (1 o 0) separados por espacios; si no existen, se coloca un guion '-'.
 * @note Los identificadores de las reservas vigentes se almacenan al final, separados por " -".
 * @note La función no retorna valor y no lanza excepciones en caso de error; simplemente retorna si falla la apertura del archivo o el arreglo es nulo.
 */

    if (!alojamientos)
        return;

    ofstream archivo(nombreArchivo);
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
        archivo << (doc ? string(reinterpret_cast<char *>(doc), 10) : ", ") << ", ";

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

void guardarArchivos(const string &nombreArchivo, Huesped **huespedes, int cantidad, unsigned int &iteraciones)
{
    /**
 * @brief Guarda la información de un arreglo de alojamientos en un archivo de texto.
 *
 * Esta función escribe en un archivo los datos principales de cada objeto Alojamiento
 * contenido en un arreglo, serializando sus atributos básicos y algunos datos relacionados,
 * como las amenidades y los identificadores de las reservas vigentes.
 *
 * @param nombreArchivo Nombre del archivo donde se almacenarán los datos (sobrescribe el contenido existente).
 * @param alojamientos Arreglo de punteros a objetos Alojamiento que se desean guardar.
 * @param cantidad Número total de alojamientos en el arreglo.
 * @param iteraciones Referencia a un contador que se incrementa en cada iteración significativa, para medir eficiencia o trazabilidad.
 *
 * @note Se verifica que el arreglo de alojamientos y el archivo se hayan abierto correctamente.
 */


    if (!huespedes)
        return;

    ofstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir " << nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < cantidad; ++i)
    {
        iteraciones++;
        Huesped *h = huespedes[i];
        if (!h)
            continue;

        unsigned char *doc = h->getDocumento();
        archivo << (string(reinterpret_cast<char *>(doc), 10)) << ", ";
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

void guardarArchivos(const string &nombreArchivo, Reserva ***reservas, unsigned int filas, unsigned int columnas, unsigned int cantidad, unsigned int &iteraciones)
{
    /**
 * @brief Guarda la información de una matriz de reservas en un archivo de texto.
 *
 * Esta función serializa los datos de todas las reservas contenidas en una matriz tridimensional
 * de punteros a Reserva, y los escribe en un archivo en formato de texto. Se incluye un encabezado
 * con la cantidad total de reservas, seguido por los datos individuales de cada una en formato CSV.
 *
 * @param nombreArchivo Nombre del archivo donde se guardarán los datos (sobrescribe el contenido existente).
 * @param reservas Matriz de punteros a punteros de punteros a objetos Reserva (Reserva***).
 * @param filas Número de filas de la matriz.
 * @param columnas Número de columnas de la matriz.
 * @param cantidad Cantidad total de reservas vigentes a guardar (escrita como encabezado en el archivo).
 * @param iteraciones Referencia a un contador de iteraciones, incrementado en cada paso relevante para trazabilidad.
 * @note Si el archivo no puede abrirse, la función retorna sin modificar nada.
 */

    ofstream archivo(nombreArchivo);
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
    /**
 * @brief Elimina una reserva asociada a un huésped, si existe y le pertenece.
 *
 * Esta función busca y elimina una reserva en la estructura tridimensional de reservas, solo si
 * el código ingresado corresponde a una reserva activa del huésped actual. Elimina los vínculos
 * en el huésped y en el alojamiento correspondiente, libera la memoria y actualiza la cantidad total.
 *
 * @param reservas Referencia al puntero triple que contiene la matriz de reservas (Reserva***).
 * @param filasTotales Número total de filas de la matriz de reservas.
 * @param columnasTotales Número total de columnas de la matriz de reservas.
 * @param cantidadReservas Referencia a la cantidad total de reservas activas, se decrementa si se elimina una.
 * @param huesped Puntero al huésped que solicita la eliminación de una reserva.
 * @param iteraciones Referencia a un contador de pasos/iteraciones para fines de trazabilidad y análisis de rendimiento.
 *
 * @details
 * - Solicita al usuario el código de la reserva a eliminar.
 * - Verifica si dicha reserva pertenece al huésped actual.
 * - Si pertenece, recorre la matriz de reservas y la elimina:
 *   - Llama a `eliminarReserva` del huésped y del alojamiento correspondiente.
 *   - Libera la memoria con `delete` y pone el puntero a `nullptr`.
 *   - Reduce la cantidad total de reservas.
 * - Si no se encuentra la reserva o no pertenece al huésped, muestra un mensaje de error.
 *
 * @note Esta función no reacomoda la matriz tras la eliminación (los huecos permanecen como nullptr).
 */


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

void eliminarReserva(Reserva ***&reservas, unsigned int filasTotales, unsigned int columnasTotales, unsigned int &cantidadReservas, Anfitrion*& anfitrion, unsigned int &iteraciones)
{
    /**
 * @brief Elimina una reserva desde la perspectiva del anfitrión, si le pertenece alguno de sus alojamientos.
 *
 * Esta función permite al anfitrión eliminar una reserva vigente, siempre que la reserva esté asociada a
 * alguno de sus alojamientos. Elimina los vínculos correspondientes en el huésped y el alojamiento,
 * libera la memoria y actualiza la cantidad global de reservas.
 *
 * @param reservas Referencia al puntero triple que contiene la matriz de reservas (Reserva***).
 * @param filasTotales Número total de filas en la matriz de reservas.
 * @param columnasTotales Número total de columnas en la matriz de reservas.
 * @param cantidadReservas Referencia al contador global de reservas activas, que se decrementa si se elimina una.
 * @param anfitrion Puntero al anfitrión que desea eliminar una reserva de alguno de sus alojamientos.
 * @param iteraciones Referencia a un contador de pasos/iteraciones, útil para análisis de rendimiento y depuración.
 *
 * @details
 * - Solicita al usuario el código de reserva a eliminar.
 * - Verifica si el código corresponde a una reserva vinculada a alguno de los alojamientos del anfitrión.
 * - Si la reserva pertenece:
 *   - Recorre la matriz global de reservas para encontrar y eliminar el objeto.
 *   - Llama a `eliminarReserva` en el huésped y en el alojamiento correspondiente.
 *   - Libera la memoria (`delete`) y marca la celda como `nullptr`.
 *   - Decrementa el contador global de reservas.
 * - Si la reserva no pertenece al anfitrión o no se encuentra, informa un error.
 * @note La verificación de pertenencia se hace primero para evitar eliminar reservas ajenas.
 */

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
    /**
 * @brief Filtra y retorna alojamientos disponibles que cumplan con criterios de búsqueda.
 *
 * Esta función permite filtrar un arreglo de alojamientos según los siguientes criterios:
 * - Disponibilidad entre dos fechas.
 * - Coincidencia del municipio.
 * - Precio por noche menor o igual al límite dado.
 * - Puntuación del anfitrión mayor o igual al valor especificado.
 *
 * Si un alojamiento cumple con los filtros y está disponible en las fechas indicadas, se muestra por consola
 * y se agrega a un arreglo dinámico que se retorna al final de la función.
 *
 * @param alojamientos Arreglo original de punteros a objetos `Alojamiento`.
 * @param cantidadAlojamientos Número total de alojamientos en el arreglo original.
 * @param fechaInicio Fecha inicial de la búsqueda.
 * @param fechaFin Fecha final de la búsqueda.
 * @param municipio Nombre del municipio a filtrar.
 * @param cantidad (Entrada/Salida) Capacidad del arreglo devuelto; inicialmente en 5, puede aumentar dinámicamente.
 * @param puntuacion Puntuación mínima que debe tener el anfitrión del alojamiento.
 * @param precio Precio máximo por noche permitido.
 * @param iteraciones Contador de pasos ejecutados, útil para análisis de rendimiento o trazabilidad.
 *
 * @return Un nuevo arreglo dinámico (`Alojamiento**`) que contiene punteros a los alojamientos disponibles.
 *
 * @details
 * - El arreglo retornado es redimensionado de 5 en 5 posiciones usando la función `redimensionarArreglo(...)`
 *   si se supera la capacidad inicial.
 * - La condición de disponibilidad exige que la reserva existente **no se solape** con el rango de fechas dado.
 *   Es decir, la reserva existente debe comenzar **después** de `fechaFin` o antes de `fechaInicio`.
 * - Cada alojamiento se imprime por consola (nombre, código, dirección) una sola vez si es agregado.
 * - La variable `visitado` asegura que un alojamiento no se agregue múltiples veces por múltiples reservas.
 */


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

void imprimir(Reserva*& reserva)
{
    /**
 * @brief Imprime por consola los detalles básicos de una reserva confirmada.
 *
 * Esta función se encarga de mostrar un resumen claro y formateado de la información más relevante de una reserva,
 * incluyendo los datos del alojamiento asociado, las fechas de entrada y salida, y el código único de la reserva.
 *
 * @param reserva Puntero a un objeto `Reserva` que contiene los datos a imprimir.
 *
 * @pre El puntero `reserva` debe ser válido y no nulo. También se asume que los punteros retornados por
 * `getAlojamientoReserva()` y los objetos `Fecha` son válidos.
 *
 * @note Esta función solo realiza salida por consola, sin retornar ningún valor ni modificar estado.
 */

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


