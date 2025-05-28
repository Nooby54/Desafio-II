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
    tamReservas = cantidadReservas;
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
    if (this->cantidadReservas == this->tamReservas)
    {
        redimensionarArreglo<Reserva>(this->reservasVigentes, this->tamReservas, this->tamReservas + 6,iteraciones);
        this->tamReservas += 6;
    }
    this->reservasVigentes[this->cantidadReservas] = reserva;
    this->cantidadReservas++;
}

unsigned char Alojamiento::getCantidadReservas() const { return cantidadReservas; }

size_t Alojamiento::tamanio(){
    size_t  tamanio = nombreAlojamiento.capacity() + sizeof(codigoIdentificador) + sizeof(anfitrionResponsable) +
               departamento.capacity() + municipio.capacity() + sizeof(tipo) + direccion.capacity() + sizeof(precioNoche)+
               sizeof(amenidades) + sizeof(reservasVigentes) + (sizeof(Reserva*) * tamReservas) + sizeof(cantidadReservas) + sizeof(tamReservas);
    return tamanio;
}
