#include "bumby.h"
#include "arma_minion.h"
#include <cstdlib>

#define TIEMPO_MOVER 50
#define TIEMPO_ATACAR 200
#define CANT_DIRECCIONES 3
#define AVANZAR_X 3
#define RETROCEDER_X 4
#define BAJAR_Y 2
#define BUMBY 2

#define ANCHO 30
#define ALTO 30

enum direcciones_ataque{DERECHA_ABAJO, CENTRO_ABAJO, IZQUIERDA_ABAJO};
enum estado_npc{MURIENDO};

Bumby::Bumby(Mapa *mapa, Coordenada c, Arma_minion* arma, int id):
Personaje_npc(mapa, c, id),
arma(arma){
  tiempo_pasado = 0;
  t_ataque = 0;
  t_mover = 0;
  tipo = BUMBY;
  alto = ALTO;
  ancho = ANCHO;
  mover_bumby = new StrategyMoverBumby();
}

void Bumby::atacar(int dir, Mapa* mapa){
	Coordenada pos_inicial(-1, -1);
	int dir_x = 0;
	int dir_y = BAJAR_Y;
	switch(dir){
		case DERECHA_ABAJO:
			pos_inicial = coordenada.derecha(ancho/2).abajo(alto/2);
			dir_x = AVANZAR_X;
			break;
		case CENTRO_ABAJO:
			pos_inicial = coordenada.abajo(alto/2);
			//dir_x = AVANZAR_X;
			break;
		case IZQUIERDA_ABAJO:
			pos_inicial = coordenada.izquierda(ancho/2).abajo(alto/2);
			dir_x = RETROCEDER_X;
			break;
	}
	Bala *bala = arma->atacar(dir_x, dir_y, pos_inicial);
	mapa->agregar_bala(bala);
	bala->notificar_observadores();
}

void Bumby::update(float tiempo, Mapa* mapa){
  if (activo){
    t_ataque += tiempo;
    t_mover += tiempo;
  }
  if ((t_ataque < TIEMPO_ATACAR ||t_mover < TIEMPO_MOVER) || !activo){
    return;
  }
	if (t_mover >= TIEMPO_MOVER){ //Se mueve cada 2 segundos!
    mover(tiempo, mapa);
    t_mover -= TIEMPO_MOVER;
	}
	if (t_ataque >= TIEMPO_ATACAR){
		int dir = std::rand() % CANT_DIRECCIONES;
		atacar(dir, mapa);
    t_ataque -= TIEMPO_ATACAR;
	}
}

void Bumby::recibir_ataque(Bala* ataque){
	ataque->daniar(this);
	if(!this->esta_vivo()){
		estado_actual = MURIENDO;
	}
	notificar_observadores();
}

void Bumby::mover(float tiempo, Mapa* mapa){
  mover_bumby->mover(mapa, this, tiempo);
  this->notificar_observadores();
}
