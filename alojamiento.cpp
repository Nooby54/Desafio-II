#include "alojamiento.h"
#include <cstring>

Alojamiento::Alojamiento(std::string nombre, unsigned int codigo, Anfitrion* anfitrion,
                         std::string depto, std::string mun, bool tipoAloj, std::string dir,
                         unsigned int precio, bool ameni[5], Reserva** reservas)
    : nombreAlojamiento(nombre), codigoIdentificador(codigo),
    anfitrionResponsable(anfitrion), departamento(depto), municipio(mun),
    tipo(tipoAloj), direccion(dir), precioNoche(precio),
    reservasVigentes(reservas)
{
    memcpy(amenidades, ameni, 5 * sizeof(bool));
}


Alojamiento::~Alojamiento() {}


std::string Alojamiento::getNombreAlojamiento() const { return nombreAlojamiento; }
unsigned int Alojamiento::getCodigoIdentificador() const { return codigoIdentificador; }
Anfitrion* Alojamiento::getAnfitrionRespon() const { return anfitrionResponsable; }
std::string Alojamiento::getDepartamento() const { return departamento; }
std::string Alojamiento::getMunicipio() const { return municipio; }
bool Alojamiento::getTipo() const { return tipo; }
std::string Alojamiento::getDireccion() const { return direccion; }
unsigned int Alojamiento::getPrecioNoche() const { return precioNoche; }
bool* Alojamiento::getAmenidades() { return amenidades; }
Reserva** Alojamiento::getReservasVigentes() const { return reservasVigentes; }
