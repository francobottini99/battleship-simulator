#ifndef __POSICION__
#define __POSICION__

struct posicion{
    int fila;
    int columna;
};

#endif

#ifndef __PILA_POSICIONES_H__
#define __PILA_POSICIONES_H__

#include <iostream>

class PilaPosiciones
{
private:
    struct nodo{
        posicion value;
        struct nodo *next;
    };

    nodo* top;  
public:
    PilaPosiciones();
    ~PilaPosiciones();

    void push(int fila, int columna);
    void pop(posicion* pos);
    void print();
};

#endif


