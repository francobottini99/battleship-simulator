#include "Flota.h"

Flota::Flota(int size, Tablero* tablero) {
    //srand(time(NULL));

    index = 0;
    ocupado = 0;
    hundidos = 0;
    this->size = size;
    armada = new Barco[size];
    this->tablero = tablero;
}

Flota::~Flota() {
    for(int i = 0; i < index; i++) {
        tablero->removeBarco(&armada[i]);
    }

    delete [] armada;
}

char Flota::recibirDisparo(int fila, int columna) {
    if(fila >= 0 && columna >= 0 && fila < tablero->getFilas() && columna < tablero->getColumnas()) {
        for(int i = 0; i < index; i++) {        
            for(int j = 0; j < (int)armada[i].getTipo(); j++) {
                if(armada[i].getEstado()[j].ubicacion.fila == fila && armada[i].getEstado()[j].ubicacion.columna == columna && !armada[i].getHundido()) {
                    armada[i].getEstado()[j].averiada = true;
                    armada[i].updateHundido();

                    tablero->updateBarco(&armada[i]);

                    if(armada[i].getHundido()) {
                        hundidos++;
                        if(hundidos == index){
                            return 't';
                        } else {
                            return 'h';
                        }
                    } else {
                        return 'v';
                    }
                }
            }
        }
    }

    return 'a';
}

void Flota::addBarcosRandomPosition(Barco::Tipos tipo, int cantidad) {
    if(index + cantidad <= size) {
        ocupado += (int)tipo * cantidad * 3 + 6 * cantidad;

        if(ocupado < (tablero->getFilas() + 2) * (tablero->getColumnas() + 2)) {
            for (int i = 0; i < cantidad; i++)
            {
                int randFila, randColumna, randOrientacion;
            
                while(true) {
                    randFila = rand() % tablero->getFilas();
                    randColumna = rand() % tablero->getFilas();
                    randOrientacion = rand() % 2;
                
                    if (tablero->freePlace((int)tipo, randOrientacion, randFila, randColumna)) {
                        if((int)tipo + randFila <= tablero->getFilas() && randOrientacion == (int)Barco::Orientaciones::VERTICAL) {
                            break;
                        }else if((int)tipo + randColumna <= tablero->getColumnas() && randOrientacion == (int)Barco::Orientaciones::HORIZONTAL) {
                            break;
                        }
                    }
                }

                armada[index].setParams(tipo, (Barco::Orientaciones)randOrientacion, randFila, randColumna);
                tablero->addBarco(&armada[index]);
                index++;
            }
        } else {
            throw std::invalid_argument("Se supero la capacidad del tablero.");
        }
    } else {
        throw std::invalid_argument("Se supero el tamanio establecido para la flota.");
    }
}