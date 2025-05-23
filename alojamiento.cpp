#include "alojamiento.h"

Alojamiento::Alojamiento(string nombre, unsigned int codigo, Anfitrion* anfitrion,
            string depto, string mun, bool tipoAloj, string dir,
            unsigned int precio, bool ameni[5], Reserva** reservas, unsigned char cantidad)
    : nombreAlojamiento(nombre), codigoIdentificador(codigo),
    anfitrionResponsable(anfitrion), departamento(depto), municipio(mun),
    tipo(tipoAloj), direccion(dir), precioNoche(precio),
    reservasVigentes(reservas), cantidadReservas(cantidad)
{
    memcpy(amenidades, ameni, 5 * sizeof(bool));
}

Alojamiento::~Alojamiento() {}

string Alojamiento::getNombreAlojamiento() const { return nombreAlojamiento; }
unsigned int Alojamiento::getCodigoIdentificador() const { return codigoIdentificador; }
Anfitrion* Alojamiento::getAnfitrionRespon() const { return anfitrionResponsable; }
void Alojamiento::setAnfitrionResponsable(Anfitrion* anfitrion) { anfitrionResponsable = anfitrion;}
string Alojamiento::getDepartamento() const { return departamento; }
string Alojamiento::getMunicipio() const { return municipio; }
bool Alojamiento::getTipo() const { return tipo; }
string Alojamiento::getDireccion() const { return direccion; }
unsigned int Alojamiento::getPrecioNoche() const { return precioNoche; }
bool* Alojamiento::getAmenidades() { return amenidades; }
Reserva** Alojamiento::getReservasVigentes() const { return reservasVigentes; }
