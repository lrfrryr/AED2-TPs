//
// Created by juanb on 11/5/2021.
//

#include "Mapa.h"

Mapa::Mapa() : _tablero(){}

Mapa::Mapa( Nat ancho, Nat alto,  map<Color, Coordenada>  dicc )
        :_tablero(alto,vector<pair<TipoCasillero,Color>>(ancho,make_pair(PISO,""))){
    for (pair<Color,Coordenada> c: dicc) {
        Coordenada cord = dicc[c.first];
        _tablero[cord.second][cord.first].second = c.first;
    }
}


Nat Mapa::alto() const {
    return _tablero.size();
}

Nat Mapa::ancho() const {
    return _tablero[0].size();
}

bool Mapa::esElevacion(Coordenada c) const {
    return _tablero[c.second][c.first].first == ELEVACION;
}

bool Mapa::esRampa(Coordenada c) const {
    return _tablero[c.second][c.first].first == RAMPA;
}


bool Mapa::esPiso(Coordenada c) const {
    return _tablero[c.second][c.first].first == PISO;
}



void Mapa::agregarElevacion(Coordenada c) {
    _tablero[c.second][c.first].first = ELEVACION;
}

void Mapa::agregarRampa(Coordenada c) {
    _tablero[c.second][c.first].first = RAMPA;
}

bool Mapa::enRango(Coordenada c) {
    return c.second < alto() && c.first < ancho();
}

 map<Color, Coordenada> Mapa::receptaculos() const {

    map<Color,Coordenada> res;
    for (int i = 0; i < this->alto(); ++i) {
        for (int j = 0; j < this->ancho() ; ++j) {
            Color c = colorDe(make_pair(j,i));
            if(c != "")
                res.insert(make_pair(c, make_pair(j,i)));
        }
    }
    return res;

}

bool Mapa::hayMovimiento(const Coordenada pos, const Direccion d) {
    Coordenada  sig = siguientePosicion(pos,d);
    bool  res  = (enRango(pos) && enRango(sig)) &&
            (!esPiso(pos) || (esPiso(pos) && !esElevacion(sig)));
    return res;

}

Coordenada Mapa::siguientePosicion(Coordenada c,Direccion d) {

    switch (d) {
        case ARRIBA:
            return make_pair(c.first,c.second+1);

        case ABAJO:
            return make_pair(c.first,c.second-1);

        case IZQUIERDA:
            return make_pair(c.first-1,c.second);

        case DERECHA:
            return make_pair(c.first+1,c.second);

        default:
            break;
    }
    return c;
}

  Color Mapa::colorDe(Coordenada c) const{
    return _tablero[c.second][c.first].second;
}



