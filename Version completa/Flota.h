#ifndef __FLOTA_H__
#define __FLOTA_H__

#include "Barco.h"
#include "Tablero.h"
#include <stdlib.h>
#include <time.h>

class Tablero;
class Barco;

class Flota
{
private:
    Tablero* tablero;
    Barco* armada;

    int size;
    int index;
    int ocupado;
    int hundidos;

public:
    Flota(int size, Tablero* tablero);
    ~Flota();

    void addBarcosRandomPosition(Barco::Tipos tipo, int cantidad);
    char recibirDisparo(int fila, int columna);
};

#endif