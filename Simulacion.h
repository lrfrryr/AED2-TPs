//
// Created by juanb on 11/5/2021.
//

#ifndef TP3_ALGO2LANDIA_SIMULACION_H
#define TP3_ALGO2LANDIA_SIMULACION_H
#include "Tipos.h"
#include "string_map.h"

#include <vector>
#include "Mapa.h"
using  itrVector    = vector<string_map<list<Objetivo>::iterator>>::iterator;
using  itrConjunto  = list<Objetivo>::iterator;

class  Simulacion {
         public:
            Simulacion(const Mapa &mapa,const  Coordenada pos,const  map<Objeto,Coordenada> &obj);
            ~Simulacion();

           const Mapa mapa();

           Coordenada  posJugador() const;

           int cantMovimientos() const  ;

           const list<Objetivo> &objetivosDisponibles() const;

           int cantObjetivosRealizados() const;

           list<Color> coloresObjetos();

           Coordenada  posObjeto(Objeto o);

           void mover(const Direccion d);

           void agObjetivo(const Objetivo o);

           void moverObjeto(const Coordenada c,const Direccion d);

           bool hayObjeto(Coordenada c);

         private:
                Coordenada _posJugador ;
                Nat _objetivosRealizados;
                Nat _cantMovimientos;
                string_map<Coordenada> _posObjeto;
                list<Objetivo> _objetivosDisponibles;

                vector<string_map<itrConjunto>> _objetivos;

                vector<vector<pair<Objeto,itrVector>>> _objetos;
                Mapa _mapa;

                void cumplirObjetivo(const Coordenada, const Direccion);

                bool hayMovObjeto(const Coordenada c, const Direccion);

                bool cumpleObjetivo(const Coordenada c,const Direccion d);


};


#endif //TP3_ALGO2LANDIA_SIMULACION_H
