#ifndef __TABLERO_H__
#define __TABLERO_H__

#include "Barco.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

class Barco;

class Tablero
{
private:
    int filas;
    int columnas;
    bool **casillas;
    bool enable;

    void updateBox(int fila, int columna, bool state);
    bool isEmpetyBox(int fila, int columna);
    void gotoxy (int x, int y);
    void hidecursor();
public:
    Tablero(int filas, int columnas);
    ~Tablero();

    void print(int nroSimulacion, int nroMovimientos);
    void clear();

    bool freePlace(int tipo, int orientacion, int fila, int columna);
    
    void addBarco(Barco* barco);
    void removeBarco(Barco* barco);
    void updateBarco(Barco* barco);

    void setEnable(bool enable);

    int getFilas();
    int getColumnas();
};

#endif


