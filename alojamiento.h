#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "reserva.h"

class Anfitrion;

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

public:
    Alojamiento(std::string nombre, unsigned int codigo, Anfitrion* anfitrion,
                std::string depto, std::string mun, bool tipoAloj, std::string dir,
                unsigned int precio, bool ameni[5], Reserva** reservas);

    ~Alojamiento();

    std::string getNombreAlojamiento() const;
    unsigned int getCodigoIdentificador() const;
    Anfitrion* getAnfitrionRespon() const;
    std::string getDepartamento() const;
    std::string getMunicipio() const;
    bool getTipo() const;
    std::string getDireccion() const;
    unsigned int getPrecioNoche() const;
    bool* getAmenidades();
    Reserva** getReservasVigentes() const;
};

#endif // ALOJAMIENTO_H
