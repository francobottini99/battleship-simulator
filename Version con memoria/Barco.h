#ifndef __POSICION__
#define __POSICION__

struct posicion{
    int fila;
    int columna;
};
#endif

#ifndef __CUERPO_BARCO__
#define __CUERPO_BARCO__

struct cuerpoBarco {
    posicion ubicacion;
    bool averiada;
};

#endif

#ifndef __BARCO_H__
#define __BARCO_H__

#include <iostream>
#include <string>

class Barco
{
private:
    cuerpoBarco* estado;
    
    int tipo;
    int orientacion;
    bool hundido;
    
    std::string getTipoName();
    std::string getOrientacionName();
    std::string getStringPosition();
public:
    enum class Orientaciones { VERTICAL = 1, HORIZONTAL = 0, NOTHING = -1 };
    enum class Tipos { DESTRUCTOR = 4, CRUCEROS = 3, CANONERAS = 2, SUBMARINOS = 1, NOTHING = -1 };

    Barco(Tipos tipo, Orientaciones orientacion, int fila, int columna);
    Barco();
    ~Barco();
    
    void updateHundido();
    void setParams(Tipos tipo, Orientaciones orientacion, int fila, int columna);
    void print();

    Tipos getTipo();
    Orientaciones getOrientacion();
    cuerpoBarco* getEstado();
    bool getHundido();
};

#endif