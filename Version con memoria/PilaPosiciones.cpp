#include "PilaPosiciones.h"

PilaPosiciones::PilaPosiciones(){
    top = nullptr;
}

PilaPosiciones::~PilaPosiciones() {
    nodo *iterator = top;
    nodo *aux;

    while (iterator != nullptr)
    {
        aux = iterator;
        iterator = iterator->next;
        delete aux;
    }
}

void PilaPosiciones::print() {
    if (top != nullptr) {
        nodo *iterator = top;

        while (iterator != nullptr)
        {
            std::cout << "(" << iterator->value.fila << "; " << iterator->value.columna << ")" << std::endl;
            iterator = iterator->next;
        }
    } else {
        std::cout << "NULL" << std::endl;
    }
}

void PilaPosiciones::push(int fila, int columna){
    nodo *aux;
    aux = new nodo;
    aux->value.fila = fila;
    aux->value.columna = columna; 

    if (top == nullptr)
    {
        aux->next = nullptr;
        top = aux;
    }
    else
    {
        aux->next = top;
        top = aux;
    }
}

void PilaPosiciones::pop(posicion* pos) {
    if (top != nullptr) {
        *pos = top->value;
        
        nodo* aux = top;
        top = top->next;
        
        delete aux;
    } else {
        pos = nullptr;
    }
}