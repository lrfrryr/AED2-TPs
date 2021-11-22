#ifndef TP3_ALGO2LANDIA_MAPA_H
#define TP3_ALGO2LANDIA_MAPA_H
#include "Tipos.h"
#include <vector>

using namespace  std;
class Mapa {
public:
    Mapa();
    Mapa(Nat ancho,  Nat alto, map<Color,Coordenada> );



    Nat ancho() const;
    Nat alto() const;
    bool esElevacion(Coordenada) const;
    bool esRampa(Coordenada) const;
    bool esPiso(Coordenada) const;

    void agregarElevacion(Coordenada);
    void agregarRampa(Coordenada);
    bool enRango(Coordenada);
    map <Color, Coordenada>  receptaculos() const;
    Coordenada  siguientePosicion(Coordenada c,Direccion d);
    Color colorDe (Coordenada c) const ;


    bool hayMovimiento(const Coordenada  pos, const Direccion d);
private:
     vector<vector<pair<TipoCasillero,Color>>> _tablero ;
};

#endif //TP3_ALGO2LANDIA_MAPA_H
