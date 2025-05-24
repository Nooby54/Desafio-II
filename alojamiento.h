#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "reserva.h"
#include "anfitrion.h"

using namespace std;
class Alojamiento
{
private:
    string nombreAlojamiento;
    unsigned int codigoIdentificador;
    Anfitrion* anfitrionResponsable;
    string departamento;
    string municipio;
    bool tipo;
    string direccion;
    unsigned int precioNoche;
    bool amenidades[5];
    Reserva** reservasVigentes;
    unsigned char cantidadReservas;

public:
    Alojamiento(string nombre, unsigned int codigo, Anfitrion* anfitrion,
                string depto, string mun, bool tipoAloj, string dir,
                unsigned int precio, bool ameni[5], Reserva** reservas, unsigned char cantidad);

    ~Alojamiento();

    string getNombreAlojamiento() const;
    unsigned int getCodigoIdentificador() const;
    Anfitrion* getAnfitrionRespon() const;
    void setAnfitrionResponsable(Anfitrion* anfitrion);
    string getDepartamento() const;
    string getMunicipio() const;
    bool getTipo() const;
    string getDireccion() const;
    unsigned int getPrecioNoche() const;
    bool* getAmenidades();
    Reserva** getReservasVigentes() const;
    unsigned char getCantidadReservas() const;
};

#endif // ALOJAMIENTO_H
