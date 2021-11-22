#include "aed2_simulacion.h"

// completar
aed2_Simulacion::aed2_Simulacion(const aed2_Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio)
: _simu(mapa.mapa(),inicio,objetos),
  _aed2mapa(mapa), _posObjeto(objetos)
//Hay que ver que onda broo
{


}
void aed2_Simulacion::mover(Direccion d){
    _simu.mover(d);
    for (pair<Objeto,Coordenada> o : _posObjeto){
        _posObjeto[o.first] = _simu.posObjeto(o.first);
    }
}

void aed2_Simulacion::agregarObjetivo(Objetivo o){
    _simu.agObjetivo(o);
}



Coordenada aed2_Simulacion::posAgente() const{
    return _simu.posJugador();
}

const list<Objetivo>& aed2_Simulacion::objetivosDisponibles() const{
    return _simu.objetivosDisponibles();
}

Nat aed2_Simulacion::movimientos() const{
    return _simu.cantMovimientos();

}

Nat aed2_Simulacion::objetivosResueltos() const{
    return _simu.cantObjetivosRealizados();
}

const aed2_Mapa aed2_Simulacion::mapa() const {
    return _aed2mapa;
}

const map<Color, Coordenada> &aed2_Simulacion::posObjetos() const {
    return _posObjeto;
}
