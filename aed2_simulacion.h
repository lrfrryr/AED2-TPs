#ifndef AED2_SIMULACION_H
#define AED2_SIMULACION_H

#include "Tipos.h"
#include "aed2_mapa.h"
#include "Simulacion.h"


class aed2_Simulacion {
public:

    /**
     * Pre:
     *  > inicio está en contenido en mapa
     *  > las coordenadas en objetos estan en mapa y no se repiten
     *  > las coordenadas en objetos no se solapan con la posición del agente
     */
    aed2_Simulacion(const aed2_Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio);

    void mover(Direccion);

    void agregarObjetivo(Objetivo);

    const aed2_Mapa mapa() const;

    const map<Color, Coordenada>& posObjetos() const;

    Coordenada posAgente() const;

    const list<Objetivo>& objetivosDisponibles() const;

    Nat movimientos() const;
    
    Nat objetivosResueltos() const;


private:
    //completar
    aed2_Mapa _aed2mapa;
    Simulacion _simu;
    map<Color,Coordenada> _posObjeto;
    //map
};

#endif // AED2_SIMULACION_H
