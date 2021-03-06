#include "jumping_snipper.h"
#include "arma_minion.h"

#define TIEMPO_ESTADO 4
#define IZQUIERDA -1
#define JUMPING_SNIPPER 3

#define ALTO 60
#define ANCHO 30

enum estados {MURIENDO, DISPARANDO, RESPAWNEANDO, CORRIENDO, SALTANDO,
		IDLE, ESCALANDO, ESCUDO_UP, ESCUDO_DOWN};

Jumping_snipper::Jumping_snipper(Mapa *mapa, Coordenada c, Arma_minion* arma, int id):
Snipper(mapa, c, arma, id){
  flotando = false;
  tiempo_pasado = 0;
  tipo = JUMPING_SNIPPER;
	alto = ALTO;
	ancho = ANCHO;
}

void Jumping_snipper::update(float tiempo, Mapa* mapa){
  if (activo){
    tiempo_pasado += tiempo;
  }
  //Salta:
	//salto_snipper.mover(mapa, this, tiempo);
  if ((tiempo_pasado < TIEMPO_ESTADO) || !activo){
    estado_actual = IDLE;
    return;
  }
	//paso el tiempo de estado:
	estado_actual = (estado_actual == ESCUDO_UP)? ESCUDO_DOWN : ESCUDO_UP;
	tiempo_pasado -= TIEMPO_ESTADO;
	this->notificar_observadores();
	if (this->esta_bajo_escudo()){
		return;
	}
	//Dispara:
  estado_actual = DISPARANDO;
	Bala *bala = arma->atacar(IZQUIERDA, 0, coordenada.izquierda(ancho/2));
	mapa->agregar_bala(bala);
	bala->notificar_observadores();

	//Personaje::update(tiempo, mapa);
}
