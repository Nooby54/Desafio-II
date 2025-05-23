#ifndef ANFITRION_H
#define ANFITRION_H

class Alojamiento;

class Anfitrion
{
private:
    unsigned char documentoAnfitrion[11];
    float puntuacion;
    unsigned char antiguedadMeses, cantidadAlojamientos;
    Alojamiento** alojamientos;

public:
    Anfitrion(unsigned char (&documento)[11], float p, unsigned char antiguedad, unsigned char cAl, Alojamiento** alojamientos);
    ~Anfitrion();

    unsigned char* getDocumentoAnfitrion();
    float getPuntuacion() const;
    unsigned char getAntiguedadMeses() const;
    unsigned char getCantidadAlojamientos() const;
    Alojamiento** getAlojamientos() const;
    void setAlojamientos(Alojamiento** nuevosAlojamientos);
};

#endif // ANFITRION_H
