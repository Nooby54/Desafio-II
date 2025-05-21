#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "reserva.h"
#include "anfitrion.h"
class Alojamiento
{
private:
    std::string nombreAlojamiento;
    unsigned int codigoIdentificador;
    Anfitrion* anfitrionResponsable;
    std::string departamento;
    std::string municipio;
    bool tipo;
    std::string direccion;
    unsigned int precioNoche;
    bool amenidades[5];
    Reserva** reservasVigentes;
    unsigned char cantidadReservas;

public:
    Alojamiento(std::string nombre, unsigned int codigo, Anfitrion* anfitrion,
                std::string depto, std::string mun, bool tipoAloj, std::string dir,
                unsigned int precio, bool ameni[5], Reserva** reservas, unsigned char cantidad)
        : nombreAlojamiento(nombre), codigoIdentificador(codigo),
        anfitrionResponsable(anfitrion), departamento(depto), municipio(mun),
        tipo(tipoAloj), direccion(dir), precioNoche(precio),
        reservasVigentes(reservas), cantidadReservas(cantidad)
    {
        for (unsigned char i = 0; i < 5; i++)
            amenidades[i] = ameni[i];
    }

    ~Alojamiento() {}

    std::string getNombreAlojamiento() const { return nombreAlojamiento; }
    unsigned int getCodigoIdentificador() const { return codigoIdentificador; }
    Anfitrion* getAnfitrionRespon() const { return anfitrionResponsable; }
    std::string getDepartamento() const { return departamento; }
    std::string getMunicipio() const { return municipio; }
    bool getTipo() const { return tipo; }
    std::string getDireccion() const { return direccion; }
    unsigned int getPrecioNoche() const { return precioNoche; }
    bool* getAmenidades() { return amenidades; }
    Reserva** getReservasVigentes() const { return reservasVigentes; }
};

#endif // ALOJAMIENTO_H
