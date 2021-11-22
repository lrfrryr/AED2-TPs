#include "aed2_mapa.h"


//completar
void aed2_Mapa::agregarRampa(Coordenada c) {
    _mapa.agregarRampa(c);
}

aed2_Mapa::aed2_Mapa()  = default;
//Llama a los constructores por defecto de ae2MAPa

Nat aed2_Mapa::alto() const {
    return _mapa.alto();
}

Nat aed2_Mapa::ancho() const {
   return  _mapa.ancho();
}

TipoCasillero aed2_Mapa::tipoCasillero(Coordenada c) const {
    if(_mapa.esElevacion(c)){
        return ELEVACION;
    }
    else if(_mapa.esRampa(c)){
        return RAMPA;
    }else{
        return PISO;
    }
}

const map<Color,Coordenada>& aed2_Mapa::receptaculos() const {
    return  _receptaculos;
}

Coordenada aed2_Mapa::receptaculo(const Color& co) {
    return  _mapa.receptaculos().at(co); //?
}

aed2_Mapa::aed2_Mapa(Nat ancho, Nat alto, set<Coordenada> elevaciones, map<Color, Coordenada> receptaculos)
: _mapa(alto,ancho,receptaculos), _receptaculos(receptaculos)
//
{
    for(Coordenada c : elevaciones){ // preguntar como agrego las rampas.
        _mapa.agregarElevacion(c);
    }
}

aed2_Mapa::aed2_Mapa(const Mapa& m)
: _mapa(m.alto(),m.ancho(),m.receptaculos()), _receptaculos(m.receptaculos())
{
     for(int i = 0; i < alto(); ++i) {
        for (int j = 0; j < ancho(); ++j) {
            TipoCasillero c = tipoCasillero(make_pair(i,j));
            if ( c == ELEVACION)
                _mapa.agregarElevacion(make_pair(i,j));

            if (c == RAMPA)
                _mapa.agregarRampa(make_pair(i,j));
        }
    }
}

Mapa aed2_Mapa::mapa() const {
    return _mapa;
}




