//
// Created by juanb on 11/5/2021.
//
// Aca implementamos   Simulacion

#include "Simulacion.h"

Simulacion::Simulacion(const Mapa &mapa, const Coordenada pos, const map<Objeto,Coordenada> &obj)
    :_posJugador(pos), _cantMovimientos(0) , _objetivosRealizados(0),_objetivos(obj.size(),string_map<itrConjunto>()),
    _mapa(mapa), _posObjeto(),
    _objetos(mapa.alto(),vector<pair<Objeto,itrVector>>(mapa.ancho(), make_pair("",_objetivos.end())))
{
    vector<string_map<itrConjunto>>::iterator itr = _objetivos.begin();
    for(pair<Objeto,Coordenada> o : obj){
       // string_map<list<Objetivo>::iterator> dicc;
       // itrVector itAD = _objetivos.insert(itr,dicc);
        //itr++;
        Coordenada pos = o.second;

        _objetos[pos.second][pos.first] = make_pair(o.first,itr++);

        _posObjeto.insert(make_pair(o.first,pos));
    }
}



Simulacion::~Simulacion() {
}

const Mapa Simulacion::mapa() {
    return _mapa;
}

 Coordenada Simulacion::posJugador() const{
    return _posJugador;
}

int Simulacion::cantMovimientos() const{
    return _cantMovimientos;
}

const list<Objetivo> &Simulacion::objetivosDisponibles() const{
    return _objetivosDisponibles;
}

list<Color> Simulacion::coloresObjetos() {
    list<Color> res;
    for (int i = 0; i < _mapa.alto(); ++i) {
        for(int j = 0;j < _mapa.ancho();++j){
            if (_objetos[i][j].first != "")
                res.insert(res.end(),_objetos[i][j].first);
        }

    }


    return res;
}

Coordenada Simulacion::posObjeto(Objeto o) {
    return _posObjeto.at(o);
}

int Simulacion::cantObjetivosRealizados() const{
    return _objetivosRealizados;
}

bool Simulacion::hayObjeto(Coordenada c) {
    return _objetos[c.second][c.first].first != "" ;
}

void Simulacion::mover(const Direccion d) {
    Coordenada p = _mapa.siguientePosicion(_posJugador, d);
    if (_mapa.enRango(p)) {
        if (_mapa.hayMovimiento(_posJugador, d)) {
            if (hayObjeto(p)) {
                if (hayMovObjeto(p, d)) {
                    if (cumpleObjetivo(p, d))
                        cumplirObjetivo(p, d);
                    moverObjeto(p, d);
                    _posJugador = p;
                }
            } else { // ver si este else va aca
                _posJugador = _mapa.siguientePosicion(_posJugador, d);
            }

        }
        _cantMovimientos++;
    }
}

void Simulacion::agObjetivo(const Objetivo o) {
    if(_mapa.colorDe(_posObjeto.at(o.first)) == o.second){
        _objetivosRealizados++; //Si el objetivo  se cumple instantaneamente
                                //No se agrega nada a la estructura
    }else{

        list<Objetivo>::iterator itConj = _objetivosDisponibles.insert(_objetivosDisponibles.end(),o);
        //Se agrega al conjunto (_objetivosDisponibles) el objetivo y se obtiene su iterador
        Coordenada p = _posObjeto.at(o.first);
        //Se obtiene la posición del objeto dentro del mapa,
        itrVector itrVec=  _objetos[p.second][p.first].second;
        //Busca dentro del mapa de objetos(_objetos) un iterador a la posición del vector de objetos
        (*itrVec).insert(make_pair(o.second,itConj)); // accedo al Trie(destino,itConj)
                                                         // y defino el nuevo objetivo y con su iterador
    }
    //fin
}

void Simulacion::moverObjeto(const Coordenada c, const Direccion d) {
    Coordenada p = _mapa.siguientePosicion(c,d);
    _objetos[p.second][p.first] = _objetos[c.second][c.first];
    _objetos[c.second][c.first] = make_pair("",_objetivos.end());
    Objeto o = _objetos[p.second][p.first].first;
    _posObjeto[o] = p;
}

void Simulacion::cumplirObjetivo(const Coordenada p , const Direccion d) {
    vector<string_map<list<Objetivo>::iterator>>::iterator itAd = _objetos[p.second][p.first].second;
    //Obtengo el itAd, que apunta a un TRIE de un iterador de  lista de objetivos
    Color destino = mapa().colorDe(_mapa.siguientePosicion(p,d));
    //Obtengo el color de a donde quiero ir
    list<Objetivo>::iterator itrConj = (*itAd).at(destino);
    //Obtengo el conjunto
    _objetivosDisponibles.erase(itrConj);
    (*itAd).erase(destino);
    _objetivosRealizados++;
    //Elimino de ambos lugaress.
}

bool Simulacion::cumpleObjetivo(const Coordenada c, const Direccion d) {

    vector<string_map<list<Objetivo>::iterator>>::iterator itr = _objetos[c.second][c.first].second; //
    Color destino = mapa().colorDe(_mapa.siguientePosicion(c,d));
    return ((*itr).count(destino)!=0);
}

bool Simulacion::hayMovObjeto(const Coordenada c, const Direccion d) {
    Coordenada  sig = _mapa.siguientePosicion(c,d);
    bool res = _mapa.enRango(sig) &&
               _mapa.hayMovimiento(c,d) &&
               !hayObjeto(sig);

    return res;
}
