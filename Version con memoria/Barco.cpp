#include "Barco.h"

Barco::Barco(Tipos tipo, Orientaciones orientacion, int fila, int columna){
    hundido = false;
    setParams(tipo, orientacion, fila, columna);
}

Barco::Barco() {
    estado = nullptr;
    orientacion = (int)Orientaciones::NOTHING;
    tipo = (int)Tipos::NOTHING;
    hundido = false;
}

Barco::~Barco() {
    delete [] estado;
}

void Barco::updateHundido() {
    hundido = true;
    for(int i = 0; i < tipo; i++){
        if(!estado[i].averiada){
            hundido = false;
        }
    }
}

void Barco::setParams(Tipos tipo, Orientaciones orientacion, int fila, int columna) {
    this->tipo = (int)tipo;
    this->orientacion = (int)orientacion;

    estado = new cuerpoBarco[(int)tipo];       
    for(int i = 0; i < this->tipo; i++) {
        if(orientacion == Orientaciones::VERTICAL) {
            estado[i].ubicacion.fila = fila + i;
            estado[i].ubicacion.columna = columna;
            estado[i].averiada = false;
        } else if(orientacion == Orientaciones::HORIZONTAL) {
            estado[i].ubicacion.fila = fila;
            estado[i].ubicacion.columna = columna + i;
            estado[i].averiada = false;
        }
    }
}

std::string Barco::getTipoName() {
    switch ((int)tipo) {
        case (int)Tipos::CRUCEROS: return "CRUCERO";
        case (int)Tipos::NOTHING: return "NOTHING";
        case (int)Tipos::CANONERAS: return "CANOÑERAS";
        case (int)Tipos::DESTRUCTOR: return "DESTRUCTOR";
        case (int)Tipos::SUBMARINOS: return "SUBMARINO";
    }
}

std::string Barco::getOrientacionName() {
    switch ((int)orientacion) {
        case (int)Orientaciones::HORIZONTAL: return "HORIZONTAL";
        case (int)Orientaciones::NOTHING: return "NOTHING";
        case (int)Orientaciones::VERTICAL: return "VERTICAL";
    }
}

std::string Barco::getStringPosition() {
    std::string pos = "{ ";
    for (int i = 0; i < (int)tipo; i++)
    {
        pos += "(" + std::to_string(estado[i].ubicacion.fila) + "; " + std::to_string(estado[i].ubicacion.columna) + ") ";
    }
    pos += " }";

    return pos;
}

void Barco::print() {
    std::cout << getTipoName() << " - " << getOrientacionName() << " - " << getStringPosition() << std::endl;
}

Barco::Tipos Barco::getTipo() {
    return (Barco::Tipos)tipo;
}

cuerpoBarco* Barco::getEstado() {
    return estado;
}

Barco::Orientaciones Barco::getOrientacion() {
    return (Barco::Orientaciones)orientacion;
}

bool Barco::getHundido() {
    return hundido;
}