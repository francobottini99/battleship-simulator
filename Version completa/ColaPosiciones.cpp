#include "ColaPosiciones.h"

ColaPosiciones::ColaPosiciones() {
    bottom = nullptr;
    front = nullptr;
}

ColaPosiciones::~ColaPosiciones() {
    nodo *iterator = front;
    nodo *aux;

    while (iterator != nullptr)
    {
        aux = iterator;
        iterator = iterator->next;
        delete aux;
    }
}

void ColaPosiciones::enqueue(PilaPosiciones* value) {
    nodo *aux;
    aux = new nodo;
    aux->value = value;
    aux->next = nullptr;
    if(front == nullptr) {
        bottom = aux;
        front = aux;
        
    } else {
        bottom->next = aux;
        bottom = aux;
    }
    
}

void ColaPosiciones::dequeue(PilaPosiciones* pila) {
    if(front != nullptr) {
        *pila = *front->value;
        nodo* aux = front;
        if(front == bottom){
            bottom = nullptr;
            front = nullptr;
        } else {
            front = front->next;
        }
        delete aux;
    } else {
        pila = nullptr;
    }
}

void ColaPosiciones::print() {
    if (front != nullptr) {
        nodo *iterator = front;

        while (iterator != nullptr)
        {
            iterator->value->print();
            std::cout << std::endl;
            iterator = iterator->next;
        }
    } else {
        std::cout << "NULL" << std::endl;
    }
}