#include "escalera.h"
#include "personaje_pc.h"
#include "bala.h"
#include "puas.h"
#include "bloque.h"
#define TIPO_ESCALERA 12
#define ANCHO 2
#define ALTO 2

enum dir_estrategias{ARRIBA, ABAJO, DERECHA, IZQUIERDA};

Escalera::Escalera(Coordenada c) : Elemento(c, TIPO_ESCALERA) {
	ancho = ANCHO;
	alto = ALTO;
}

bool Escalera::puede_ocupar(Personaje* pj){
	return true;
}

bool Escalera::puede_ocupar(Elemento* pj){
	return pj->puede_ocupar(this);
}

bool Escalera::puede_ocupar(Bala* bala){
	return true;
}

bool Escalera::puede_ocupar(Escalera* esc){
	return false;
}

bool Escalera::puede_ocupar(Bloque* bloque){
	return false;
}

bool Escalera::puede_ocupar(Premio* premio){
	return true;
}

bool Escalera::puede_ocupar(Ubicable* ubic){
	return ubic->puede_ocupar(this);
}

bool Escalera::puede_ocupar(Puas* puas){
	return false;
}

void Escalera::interactuar(Personaje *pj){
	pj->interactuar(this);
}

void Escalera::interactuar(Personaje_pc* pj){
	size_t x = pj->get_coordenada().obtener_abscisa();
	size_t y = pj->get_coordenada().obtener_ordenada();

	size_t x_max = (coord.obtener_abscisa() + (ancho / 2));
	size_t x_min = (coord.obtener_abscisa() - (ancho / 2));
	//Si la componente x de la coordenada central del
	//personaje no esta alineada
	if ( (x < x_min) || (x > x_max) ){
		return;
	}
	//Primero me fijo si el personaje esta apoyado sobre
	//la escalera, en ese caso, le doy estrategias
	//para que se mantenga en su lugar o baje pero
	//no le permito subir mas:
	
	StrategyMoverPersonajePc *estrategia_arriba = new StrategyMoverPersonajePc();
	estrategia_arriba->set_direccion_arriba();
	StrategyMoverPersonajePc *estrategia_abajo = new StrategyMoverPersonajePc();
	estrategia_abajo->set_direccion_abajo();
	StrategyMoverPersonajePc *estrategia_derecha = new StrategyMoverPersonajePc();
	estrategia_derecha->set_direccion_derecha();
	StrategyMoverPersonajePc *estrategia_izquierda = new StrategyMoverPersonajePc();
	estrategia_izquierda->set_direccion_izquierda();
	
	
	size_t piso_personaje = y + (pj->get_alto() / 2);
	size_t tope_escalera = coord.arriba(alto/2).obtener_ordenada();
	if (piso_personaje == tope_escalera){

			//Estrategias para salir de la escalera:
			pj->agregar_movimiento(estrategia_abajo);
			pj->agregar_movimiento(estrategia_derecha);
			pj->agregar_movimiento(estrategia_izquierda);
	}else{
		//Me fijo que el personaje no este en el borde inferior
		//de la escalera(es decir, que el tope del personaje no
		//coincide con el borde inferior externo de la escalera.
		//En ese caso no quiero que el personaje pueda subir.
		size_t tope_personaje = y - (pj->get_alto() / 2);
		size_t piso_escalera = coord.abajo(alto/2).obtener_ordenada();
		if (tope_personaje != piso_escalera){
			pj->agregar_movimiento(estrategia_arriba);
			pj->agregar_movimiento(estrategia_abajo);
		}
	}
}

Escalera::~Escalera() {}
