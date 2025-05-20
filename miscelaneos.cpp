#include "miscelaneos.h"


static bool esValida(unsigned char d, unsigned char m, unsigned int a)
{
    if (m < 1 || m > 12) return false;

    unsigned char diasMes;
    switch (m) {
    case 2: diasMes = ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) ? 29 : 28; break;
    case 4: case 6: case 9: case 11: diasMes = 30; break;
    default: diasMes = 31;
    }

    return (d >= 1 && d <= diasMes);
}
