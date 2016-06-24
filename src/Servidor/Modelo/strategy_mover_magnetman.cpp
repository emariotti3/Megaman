#include "strategy_mover_magnetman.h"
#include "magnetman.h"

#define TIEMPO_SALTO 5
#define GRAVEDAD 5
#define VELOCIDAD_Y 60
#define VELOCIDAD_X 5
#define VELOCIDAD_SALTO 25

enum estados{MURIENDO, DISPARANDO, RESPAWNEANDO, CORRIENDO, SALTANDO,
		IDLE, ESCALANDO};

StrategyMoverMagnetman::StrategyMoverMagnetman():
velocidad_x(0),
velocidad_y(0),
tiempo_salto(0){}

void StrategyMoverMagnetman::mover(Mapa *mapa, Magnetman *pj,
float tiempo){
	bool personaje_en_aire = mapa->esta_en_aire(pj);
	if (personaje_en_aire){
		pj->flotando = true;
	}
	if (!personaje_en_aire){
		pj->flotando = false;
		//Espero para volver a saltar.
		tiempo_salto += tiempo;
	}
	if (personaje_en_aire){
		velocidad_y -= GRAVEDAD; //valor gravedad.
	}
	if ((tiempo_salto >= TIEMPO_SALTO) && !pj->flotando){
		velocidad_y += VELOCIDAD_Y;
		tiempo_salto -= TIEMPO_SALTO;
		Coordenada c_enemigo = mapa->obtener_coordenada_enemigo(pj);
		int delta_x = c_enemigo.obtener_abscisa()-(pj->coordenada.obtener_abscisa());
		if (delta_x > 0){
			velocidad_x = VELOCIDAD_X;
		}else if (delta_x < 0){ //Si justo es 0 estan la misma posicion!
			velocidad_x = -VELOCIDAD_X;
		}
	}
	actualizar_coordenada(mapa, pj);
}

void StrategyMoverMagnetman::actualizar_coordenada(Mapa *mapa,
Magnetman *pj){
	Coordenada nueva_coordenada = pj->coordenada;
	if (velocidad_x > 0){
		nueva_coordenada = nueva_coordenada.derecha(VELOCIDAD_X);
		pj->estado_actual = CORRIENDO;
	}
	if (velocidad_x < 0){
		nueva_coordenada = nueva_coordenada.izquierda(VELOCIDAD_X);
		pj->estado_actual = CORRIENDO;
	}
	if (velocidad_y > 0){
		nueva_coordenada = nueva_coordenada.arriba(VELOCIDAD_SALTO);
		pj->estado_actual = SALTANDO;
	}
	if (velocidad_y < 0){
		nueva_coordenada = nueva_coordenada.abajo(VELOCIDAD_SALTO);
	}
	if (nueva_coordenada == pj->get_coordenada()){
		return;
	}
	if (mapa->puede_ubicarse(pj, nueva_coordenada)){
		pj->coordenada = nueva_coordenada;
		pj->notificar_observadores();
	}else{
		velocidad_x = (velocidad_x != 0)? 0 : velocidad_x;
		velocidad_y = (velocidad_y != 0)? 0 : velocidad_y;
		pj->estado_actual = IDLE;
	}
}

StrategyMoverMagnetman::~StrategyMoverMagnetman(){}