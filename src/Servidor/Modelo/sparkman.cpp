#include "sparkman.h"
#include "bala.h"
#include "arma_sparkman.h"

#define TIEMPO_ACCION 2
#define TIPO_SPARKMAN -1 //TODO: definir el id.

Sparkman::Sparkman(Mapa *mapa, Coordenada c, Arma_sparkman* arma, int id):
Personaje(mapa, c, id),
arma(arma){
  tiempo_pasado = 0;
  tipo = TIPO_SPARKMAN;
}

void Sparkman::atacar(int dir, Mapa* mapa){
	std::vector<Bala*> balas = balas_ataque();
  for (size_t i = 0; i < balas.size(); i++){
    mapa->agregar_bala(balas[i]);
    balas[i]->notificar_observadores();
  }
}

void Sparkman::mover(size_t tiempo, Mapa* mapa){ } //TODO: hacer el mover.

void Sparkman::recibir_ataque(Bala* ataque){
  ataque->daniar(this);
}

void Sparkman::update(size_t tiempo){
  tiempo_pasado += tiempo;
  if (tiempo_pasado < TIEMPO_ACCION){
    return;
  }
  //atacar
  //mover
}

void Sparkman::sacar_movimiento(int direccion){}

void Sparkman::agregar_movimiento(int direccion){}

std::vector<Bala*> Sparkman::balas_ataque(){ //Ataca en un círculo medio defo.
  std::vector<Bala*> balas;

  Coordenada pos_inicial = coordenada.izquierda(ancho/2);
  balas.push_back(arma->atacar(-1, 0, pos_inicial));
  balas.push_back(arma->atacar(-1, 1, pos_inicial));
  balas.push_back(arma->atacar(-1, -1, pos_inicial));

  pos_inicial = coordenada.derecha(ancho/2);
  balas.push_back(arma->atacar(1, 0, pos_inicial));
  balas.push_back(arma->atacar(1, 1, pos_inicial));
  balas.push_back(arma->atacar(1, -1, pos_inicial));

  balas.push_back(arma->atacar(0 , 1, coordenada.abajo(alto/2)));
  balas.push_back(arma->atacar(0 , -1, coordenada.arriba(alto/2)));

  return balas;
}