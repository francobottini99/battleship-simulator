#ifndef __COLA_POSICIONES_H__
#define __COLA_POSICIONES_H__

#include <iostream>

#include "PilaPosiciones.h"

class PilaPosiciones;

class ColaPosiciones
{
private:
    struct nodo{
        PilaPosiciones* value;
        struct nodo* next;
    };

    nodo* bottom;
    nodo* front; 
public:
    ColaPosiciones();
    ~ColaPosiciones();

    void enqueue(PilaPosiciones* value);
    void dequeue(PilaPosiciones* pila);
    void print();
};

#endif