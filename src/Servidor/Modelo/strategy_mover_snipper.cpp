#include "strategy_mover_snipper.h"
#include "snipper.h"

#define VELOCIDAD 18
#define TIEMPO_DIRECCION 100

enum direccion{DERECHA, IZQUIERDA};

enum estados{MURIENDO, DISPARANDO, RESPAWNEANDO, CORRIENDO, SALTANDO,
		IDLE, ESCALANDO, ESCUDO_UP, ESCUDO_DOWN};

StrategyMoverSnipper::StrategyMoverSnipper(){
	direccion = DERECHA;
	tiempo_pasado = 0;
}

void StrategyMoverSnipper::mover(Mapa *mapa, Snipper *pj, float tiempo){
	Coordenada coord_nueva = pj->coordenada;
	tiempo_pasado += tiempo;
	if (tiempo_pasado >= TIEMPO_DIRECCION){
		cambiar_direccion();
		tiempo_pasado -= TIEMPO_DIRECCION;
	}
	switch(direccion){
		case DERECHA:
			coord_nueva = pj->coordenada.derecha(VELOCIDAD);
			pj->estado_actual = CORRIENDO;
			break;
		case IZQUIERDA:
			coord_nueva = pj->coordenada.izquierda(VELOCIDAD);
			pj->estado_actual = CORRIENDO;
			break;
	}
	if (mapa->puede_ubicarse(pj, coord_nueva)){
		pj->coordenada = coord_nueva;
		pj->notificar_observadores();
	}
}

void StrategyMoverSnipper::cambiar_direccion(){
	if (direccion == DERECHA){
		direccion = IZQUIERDA;
	}else{
		direccion = DERECHA;
	}
}
