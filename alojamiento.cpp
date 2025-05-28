#include "alojamiento.h"
#include "miscelaneos.h"

Alojamiento::Alojamiento(string nombre, unsigned int codigo, Anfitrion *anfitrion,
                         string depto, string mun, bool tipoAloj, string dir,
                         unsigned int precio, bool ameni[5], Reserva **reservas, unsigned char cantidad)
    : nombreAlojamiento(nombre), codigoIdentificador(codigo),
      anfitrionResponsable(anfitrion), departamento(depto), municipio(mun),
      tipo(tipoAloj), direccion(dir), precioNoche(precio),
      reservasVigentes(reservas), cantidadReservas(cantidad)
{
    // Inicializa el tamaño total del arreglo de reservas al mismo valor que la cantidad actual
    tamReservas = cantidadReservas;

    // Copia el arreglo de amenidades (5 elementos booleanos) al atributo del objeto
    memcpy(amenidades, ameni, 5 * sizeof(bool));
}

Alojamiento::~Alojamiento() {}

string Alojamiento::getNombreAlojamiento() const { return nombreAlojamiento; }
unsigned int Alojamiento::getCodigoIdentificador() const { return codigoIdentificador; }
Anfitrion *Alojamiento::getAnfitrionRespon() const { return anfitrionResponsable; }
void Alojamiento::setAnfitrionResponsable(Anfitrion *anfitrion) { anfitrionResponsable = anfitrion; }
string Alojamiento::getDepartamento() const { return departamento; }
string Alojamiento::getMunicipio() const { return municipio; }
bool Alojamiento::getTipo() const { return tipo; }
string Alojamiento::getDireccion() const { return direccion; }
unsigned int Alojamiento::getPrecioNoche() const { return precioNoche; }
bool *Alojamiento::getAmenidades() { return amenidades; }
Reserva **Alojamiento::getReservasVigentes() const { return reservasVigentes; }

void Alojamiento::eliminarReserva(unsigned int codigoReserva, unsigned int &iteraciones)
{
    /**
 * @brief Elimina una reserva del alojamiento según su código identificador.
 *
 * Busca la reserva cuyo código coincide con el proporcionado y la elimina del arreglo
 * `reservasVigentes`. Para mantener la continuidad del arreglo, compacta los elementos
 * desplazando hacia adelante las reservas posteriores. Si no se encuentra la reserva,
 * no se realiza ninguna modificación.
 *
 * @param codigoReserva Código identificador de la reserva que se desea eliminar.
 * @param iteraciones Referencia a un contador de iteraciones realizadas, útil para fines de análisis o debugging.
 */
    unsigned char k = 0;
    for (unsigned int i = 0; i < cantidadReservas; i++)
    {
        iteraciones++;
        if (reservasVigentes[i]->getCodigoIdentificador() == codigoReserva)
        {
            reservasVigentes[i] = nullptr;
        }
        else
        {
            reservasVigentes[k] = reservasVigentes[i];
            k++;
        }
    }
    cantidadReservas = k;
}

void Alojamiento::agregarReserva(Reserva *reserva, unsigned int &iteraciones)
{
    /**
 * @brief Agrega una nueva reserva al alojamiento.
 *
 * Si el arreglo de reservas actuales ha alcanzado su capacidad máxima (`tamReservas`),
 * lo redimensiona para permitir la inclusión de nuevas reservas. Luego añade la nueva
 * reserva al final del arreglo y actualiza la cantidad de reservas.
 *
 * @param reserva Puntero a la reserva que se desea agregar.
 * @param iteraciones Referencia a un contador que acumula la cantidad de iteraciones realizadas
 *                    durante la redimensión del arreglo (si ocurre).
 */

    if (this->cantidadReservas == this->tamReservas)
    {
        redimensionarArreglo<Reserva>(this->reservasVigentes, this->tamReservas, this->tamReservas + 6,iteraciones);
        this->tamReservas += 6;
    }
    this->reservasVigentes[this->cantidadReservas] = reserva;
    this->cantidadReservas++;
}

unsigned char Alojamiento::getCantidadReservas() const { return cantidadReservas; }

size_t Alojamiento::tamanio()
{
    /**
 * @brief Calcula el tamaño en bytes que ocupa la instancia del alojamiento.
 *
 * Estima la memoria utilizada por los atributos del objeto, incluyendo cadenas (usando `capacity()`),
 * punteros, enteros, booleanos y el arreglo de punteros a reservas.
 *
 * @return Tamaño aproximado en bytes que ocupa la instancia del objeto.
 */
    size_t  tamanio = nombreAlojamiento.capacity() + sizeof(codigoIdentificador) + sizeof(anfitrionResponsable) +
               departamento.capacity() + municipio.capacity() + sizeof(tipo) + direccion.capacity() + sizeof(precioNoche)+
               sizeof(amenidades) + sizeof(reservasVigentes) + (sizeof(Reserva*) * tamReservas) + sizeof(cantidadReservas) + sizeof(tamReservas);
    return tamanio;
}
