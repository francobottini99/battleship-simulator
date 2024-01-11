#include "Tablero.h"

Tablero::Tablero(int filas, int columnas){
    if(filas > 0 && columnas > 0) {
        if(filas < 100 && columnas < 100) {
            this->filas = filas; 
            this->columnas = columnas;

            casillas = new bool* [filas];
            for (int i = 0; i < filas; i++)
            {
                casillas[i] = new bool[columnas];
            }

            clear();
            hidecursor();
            enable = true;
        } else {
            throw std::invalid_argument("El tablero deseado excede los limites de diseño (100 X 100)");
        }
    } else {
        throw std::invalid_argument("Argumentos invalidos.");
    }
}

Tablero::~Tablero() {
    for (int i = 0; i < filas; i++)
    {
        delete [] casillas[i];
    }
    
    delete [] casillas;
}

void Tablero::clear() {
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            casillas[i][j] = false;
        }
    }
}

void Tablero::print(int nroSimulacion, int nroMovimientos){
    if(enable) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        gotoxy(0, 0);

        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                if(casillas[i][j]){
                    SetConsoleTextAttribute(hConsole, 12);
                    std::cout << "O";
                } else {
                    SetConsoleTextAttribute(hConsole, 9);
                    std::cout << "X";
                }
                std::cout << " ";
            }

            if(i == 0) {
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << " NUMERO DE SIMULACIONES: ";
                SetConsoleTextAttribute(hConsole, 14);
                std::cout << nroSimulacion;
                std::cout << "       ";
            }

            if(i == 1) {
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << " PROMEDIO DE MOVIMIENTOS: ";
                SetConsoleTextAttribute(hConsole, 14);
                std::cout << nroMovimientos;
                std::cout << "       ";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;

        SetConsoleTextAttribute(hConsole, 15);
    }
}

void Tablero::updateBox(int fila, int columna, bool state){
    casillas[fila][columna] = state;
}

void Tablero::addBarco(Barco* barco){
    if(barco->getEstado() != nullptr && barco->getTipo() != Barco::Tipos::NOTHING && barco->getOrientacion() != Barco::Orientaciones::NOTHING) {
        if(barco->getEstado()[0].ubicacion.fila < filas && barco->getEstado()[0].ubicacion.columna < columnas){
            if(((int)barco->getTipo() + barco->getEstado()[0].ubicacion.fila <= filas && barco->getOrientacion() == Barco::Orientaciones::VERTICAL) || ((int)barco->getTipo() + barco->getEstado()[0].ubicacion.columna <= columnas && barco->getOrientacion() == Barco::Orientaciones::HORIZONTAL)){
                if(freePlace((int)barco->getTipo(), (int)barco->getOrientacion(), barco->getEstado()[0].ubicacion.fila, barco->getEstado()[0].ubicacion.columna)){
                    for(int i = 0; i < (int)barco->getTipo(); i++) { 
                        updateBox(barco->getEstado()[i].ubicacion.fila, barco->getEstado()[i].ubicacion.columna, !barco->getEstado()[i].averiada);
                    }
                } else {
                    throw std::invalid_argument("Superposicion de barcos.");
                }
            } else {
                throw std::invalid_argument("El barco excede los limites del tablero (" + std::to_string(filas) + " X " + std::to_string(columnas) + ")");
            }
        } else {
            throw std::invalid_argument("La posicion (" + std::to_string(barco->getEstado()[0].ubicacion.fila) + "; " + std::to_string(barco->getEstado()[0].ubicacion.columna) + ") excede a los limites del tablero (" + std::to_string(filas) + " X " + std::to_string(columnas) + ")");
        }
    } else {
        throw std::invalid_argument("Barco nulo.");
    }
}

void Tablero::removeBarco(Barco* barco){
    if(barco->getEstado() != nullptr && barco->getTipo() != Barco::Tipos::NOTHING && barco->getOrientacion() != Barco::Orientaciones::NOTHING) {
        for(int i = 0; i < (int)barco->getTipo(); i++) { 
            updateBox(barco->getEstado()[i].ubicacion.fila, barco->getEstado()[i].ubicacion.columna, !barco->getEstado()[i].averiada);
        }
    } else {
        throw std::invalid_argument("Barco nulo.");
    }
}

void Tablero::updateBarco(Barco* barco){
    if(barco->getEstado() != nullptr && barco->getTipo() != Barco::Tipos::NOTHING && barco->getOrientacion() != Barco::Orientaciones::NOTHING) {
        for(int i = 0; i < (int)barco->getTipo(); i++) { 
            updateBox(barco->getEstado()[i].ubicacion.fila, barco->getEstado()[i].ubicacion.columna, !barco->getEstado()[i].averiada);
        }
    } else {
        throw std::invalid_argument("Barco nulo.");
    }
}

bool Tablero::freePlace(int tipo, int orientacion, int fila, int columna) {
    bool free = true;
    
    for(int i = -1; i < (int)tipo + 1; i++) {
        if(orientacion == (int)Barco::Orientaciones::VERTICAL) {
            if(!isEmpetyBox(fila + i, columna) || 
               !isEmpetyBox(fila + i, columna + 1) ||
               !isEmpetyBox(fila + i, columna - 1)) {
                free = false;
                break;
            }
        } else if(orientacion == (int)Barco::Orientaciones::HORIZONTAL) {
            if(!isEmpetyBox(fila, columna + i) ||
               !isEmpetyBox(fila + 1, columna + i) ||
               !isEmpetyBox(fila - 1, columna + i)) {
                free = false;
                break;
            }
        }
    }

    return free;
}

bool Tablero::isEmpetyBox(int fila, int columna) {
    if(fila >= this->filas || columna >= this->columnas || fila < 0 || columna < 0){
        return true;
    } else {
        return !casillas[fila][columna];
    }
}

int Tablero::getFilas(){
    return filas;
}

int Tablero::getColumnas(){
    return columnas;
}

void Tablero::setEnable(bool enable) {
    this->enable = enable;
}

void Tablero::gotoxy (int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle ( STD_OUTPUT_HANDLE );
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition ( hcon, dwPos );
}

void Tablero::hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}