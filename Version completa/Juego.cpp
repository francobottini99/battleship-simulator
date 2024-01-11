#include "PilaPosiciones.h"
#include "ColaPosiciones.h"
#include "Barco.h"
#include "Tablero.h"
#include "Flota.h"
#include <fstream>

const int simulaciones = 150;
std::string dirTxtMovimientos = "D:/009) FRANCO/04) FACULTAD/22) ALGORITMOS Y ESTRUCTURAS DE DATOS/Primer Parcial/resultados.txt";

void colaAleatoria(ColaPosiciones* colaMovimientos, Tablero* tablero);
void colaSecuencialFilas(ColaPosiciones* colaMovimientos, Tablero* tablero);
void colaSecuencialColumnas(ColaPosiciones* colaMovimientos, Tablero* tablero);
void guardarResultado(int* movimientos);
bool existePosision(posicion* lista, int size, int fila, int columna, Tablero* tablero);
void verificar_agregar(posicion* lista, int* lastIndex, int fila, int columna, Tablero* tablero);

int main(int argc, char *argv[]) {
    srand(time(NULL));
  
    int movimientosTotales = 0; 
    int resultados[simulaciones];

    PilaPosiciones* next = new PilaPosiciones;
    posicion* pos = new posicion;

    try
    {
        for(int i = 0; i < simulaciones; i++) {
            resultados[i] = 0;
            ColaPosiciones colaMovimientos;
            Tablero tablero(10, 10);
            Flota armada(10, &tablero);

            //tablero.setEnable(false);

            bool endCola = false;

            armada.addBarcosRandomPosition(Barco::Tipos::DESTRUCTOR, 1);
            armada.addBarcosRandomPosition(Barco::Tipos::CRUCEROS, 2);
            armada.addBarcosRandomPosition(Barco::Tipos::CANONERAS, 3);
            armada.addBarcosRandomPosition(Barco::Tipos::SUBMARINOS, 4);

            tablero.print(i + 1, movimientosTotales / (i + 1));
            //colaAleatoria(&colaMovimientos, &tablero);
            colaSecuencialFilas(&colaMovimientos, &tablero);
            //colaSecuencialColumnas(&colaMovimientos, &tablero);

            posicion* posicionesAtacadas = new posicion[tablero.getFilas() * tablero.getColumnas()];
            int index = 0;
            do {
                do {
                    colaMovimientos.dequeue(next);
                    next->pop(pos);
                } while(existePosision(posicionesAtacadas, index, pos->fila, pos->columna, &tablero));
                posicionesAtacadas[index] = *pos;

                resultados[i]++;
                movimientosTotales++;
                index++;

                switch(armada.recibirDisparo(pos->fila, pos->columna)) {
                    case 'a': break;
                    case 'v':
                    {
                        tablero.print(i + 1, movimientosTotales / (i + 1));

                        int fila = pos->fila, columna = pos->columna;
                        
                        if(!existePosision(posicionesAtacadas, index, fila + 1, columna, &tablero)){
                            next->push(fila + 1, columna);
                        }
                        
                        if(!existePosision(posicionesAtacadas, index, fila - 1, columna, &tablero)){
                            next->push(fila - 1, columna);
                        }

                        if(!existePosision(posicionesAtacadas, index, fila, columna + 1, &tablero)){
                            next->push(fila, columna + 1);
                        }
                        
                        if(!existePosision(posicionesAtacadas, index, fila, columna - 1, &tablero)){
                            next->push(fila, columna - 1);
                        }

                        verificar_agregar(posicionesAtacadas, &index, fila + 1, columna + 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, fila + 1, columna - 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, fila - 1, columna + 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, fila - 1, columna - 1, &tablero);

                        bool endPila = false;
                        do {
                            do {
                                next->pop(pos);
                            } while(existePosision(posicionesAtacadas, index, pos->fila, pos->columna, &tablero));     
                            posicionesAtacadas[index] = *pos;

                            resultados[i]++;     
                            movimientosTotales++;   
                            index++;     
                            
                            switch(armada.recibirDisparo(pos->fila, pos->columna)) {
                                case 'a': break;
                                case 'h':
                                {
                                    tablero.print(i + 1, movimientosTotales / (i + 1)); 
                                    endPila = true;
                                    if(fila - pos->fila == 0) {
                                        if(columna - pos->columna > 0) {
                                            verificar_agregar(posicionesAtacadas, &index, fila, columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila - 1, columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila + 1, columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila, pos->columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna - 1, &tablero);
                                        } else {
                                            verificar_agregar(posicionesAtacadas, &index, fila, columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila - 1, columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila + 1, columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna + 1, &tablero);
                                        }
                                    } else {
                                        if(fila - pos->fila > 0) {
                                            verificar_agregar(posicionesAtacadas, &index, fila + 1, columna, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila + 1, columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila + 1, columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna - 1, &tablero);
                                        } else {
                                            verificar_agregar(posicionesAtacadas, &index, fila - 1, columna, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila - 1, columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, fila - 1, columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna - 1, &tablero);
                                        }
                                    }
                                    break;
                                }
                                case 't': tablero.print(i + 1, movimientosTotales / (i + 1)); endCola = true; endPila = true; break;
                                case 'v': 
                                {   
                                    tablero.print(i + 1, movimientosTotales / (i + 1));
                                    if(fila - pos->fila == 0) {     
                                        verificar_agregar(posicionesAtacadas, &index, fila + 1, columna, &tablero);
                                        verificar_agregar(posicionesAtacadas, &index, fila - 1, columna, &tablero);

                                        if(columna - pos->columna > 0) {
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna - 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna - 1, &tablero);

                                            next->push(pos->fila, pos->columna - 1);
                                        } else {
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna + 1, &tablero);

                                            next->push(pos->fila, pos->columna + 1);
                                        }
                                    } else {
                                        verificar_agregar(posicionesAtacadas, &index, fila, columna + 1, &tablero);
                                        verificar_agregar(posicionesAtacadas, &index, fila, columna - 1, &tablero);

                                        if(fila - pos->fila > 0) {
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna - 1, &tablero);

                                            next->push(pos->fila - 1, pos->columna);
                                        } else {
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna + 1, &tablero);
                                            verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna - 1, &tablero);

                                            next->push(pos->fila + 1, pos->columna);
                                        }
                                    }
                                    break;
                                }
                            }
                        } while(pos != nullptr && !endPila);
                        break;
                    }
                    case 'h': 
                    {
                        tablero.print(i + 1, movimientosTotales / (i + 1)); 
                        verificar_agregar(posicionesAtacadas, &index, pos->fila, pos->columna - 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila, pos->columna + 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna + 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila + 1, pos->columna - 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna + 1, &tablero);
                        verificar_agregar(posicionesAtacadas, &index, pos->fila - 1, pos->columna - 1, &tablero);
                        break;
                    }
                    case 't': tablero.print(i + 1, movimientosTotales / (i + 1)); endCola = true; break;
                }
            } while(next != nullptr && !endCola);       

            delete [] posicionesAtacadas;
        }
    }
    catch(std::invalid_argument e)
    {
        std::cerr << e.what() << std::endl;  
    }

    //guardarResultado(resultados);

    delete next;
    delete pos;
    system("PAUSE");
    return 0;
}

void colaAleatoria(ColaPosiciones* colaMovimientos, Tablero* tablero) {
    posicion* agregados = new posicion[tablero->getFilas() * tablero->getColumnas()];
    int index = 0;
    for(int i = 0; i < tablero->getFilas(); i++) {
        for(int j = 0; j < tablero->getColumnas(); j++) {
            int randColumna, randFila;

            do {
                randFila = rand() % 10;
                randColumna = rand() % 10;
            } while(existePosision(agregados, index, randFila, randColumna, tablero));

            PilaPosiciones* aux = new PilaPosiciones;

            aux->push(randFila, randColumna);
            colaMovimientos->enqueue(aux);
                    
            agregados[index].fila = randFila;
            agregados[index].columna = randColumna;
            index++;
        }
    }
    delete [] agregados;
}

void colaSecuencialFilas(ColaPosiciones* colaMovimientos, Tablero* tablero) {
    for(int i = 0; i < tablero->getFilas(); i++) {
        for(int j = 0; j < tablero->getColumnas(); j++) {
            PilaPosiciones* aux = new PilaPosiciones;
            aux->push(i, j);
            colaMovimientos->enqueue(aux);
        }
    }
}

void colaSecuencialColumnas(ColaPosiciones* colaMovimientos, Tablero* tablero) {
    for(int i = 0; i < tablero->getColumnas(); i++) {
        for(int j = 0; j < tablero->getFilas(); j++) {
            PilaPosiciones* aux = new PilaPosiciones;
            aux->push(j, i);
            colaMovimientos->enqueue(aux);
        }
    }
}

bool existePosision(posicion* lista, int size, int fila, int columna, Tablero* tablero) {
    if(fila < tablero->getFilas() && fila >= 0 & columna < tablero->getColumnas() && columna >= 0) {
        for(int k = 0; k < size; k++) {
            if(lista[k].fila == fila && lista[k].columna == columna){
                return true;
            }
        }

        return false;
    } else {
        return true;
    }
}

void verificar_agregar(posicion* lista, int* lastIndex, int fila, int columna, Tablero* tablero) {
    if(!existePosision(lista, *lastIndex, fila, columna, tablero)){
        lista[*lastIndex].fila = fila;
        lista[*lastIndex].columna = columna;
        (*lastIndex)++;
    }
}

void guardarResultado(int* movimientos) {
    std::ofstream resultados;
    resultados.open(dirTxtMovimientos);
    resultados.clear();
    for(int i = 0; i < simulaciones; i++){
        resultados << std::to_string(movimientos[i]) + "\n";
    }
    resultados.close();
}