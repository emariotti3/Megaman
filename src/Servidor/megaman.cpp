#include "megaman.h"
#include "arma_megaman.h"
#include <string>
#include <iostream>
#include <sstream>

#define DERECHA 3
#define IZQUIERDA 4

Megaman::Megaman(Mapa *mapa, Coordenada c, std::string id):
Personaje(mapa, c, id){
	arma_act = 1;
	armas.push_back(new Arma_megaman());
}

void Megaman::update(size_t tiempo){
	Personaje::update(tiempo, mapa);
}

void Megaman::atacar(size_t tiempo, int dir, Mapa* mapa){
	Bala* bala;
	Coordenada pos_inicial(-1, -1);
	if (dir == DERECHA){
		bala = armas[arma_act-1]->atacar(1, 0);
		pos_inicial = coordenada.derecha(ancho/2);
	}
	if (dir == IZQUIERDA){
		bala = armas[arma_act-1]->atacar(-1, 0);
		pos_inicial = coordenada.izquierda(ancho/2);
	}
	mapa->agregar_bala(bala);
}

void Megaman::mover(size_t tiempo, Mapa* mapa){
  if (mapa->esta_en_aire(coordenada, alto)){
    flotando = true;
    velocidad_y += 1; //valor gravedad.
  }
  if (velocidad_x == 0 && velocidad_y == 0){
    std::cout << "las velocidades son 0 \n";
    return;
  }
  Coordenada nueva_coordenada = coordenada;
  if (velocidad_x > 0){
    std::cout << "derecha \n";
    nueva_coordenada = nueva_coordenada.derecha(2);
  }
  if (velocidad_x < 0){
    std::cout << "izquierda \n";
    nueva_coordenada = nueva_coordenada.izquierda(2);
  }
  if (velocidad_y < 0){
    std::cout << "arriba \n";
    nueva_coordenada = nueva_coordenada.arriba(2);
  }
  if (velocidad_y > 0){
    std::cout << "abajo \n";
    nueva_coordenada = nueva_coordenada.abajo(2);
  }

  if (mapa->puede_ubicarse_en(nueva_coordenada, alto, ancho)){
    std::cout << "hola \n";
    coordenada = nueva_coordenada;
  }else{
    std::cout << "mi coordenada rechazada: " <<  "x: " << nueva_coordenada.obtener_abscisa() << "y: "
    << nueva_coordenada.obtener_ordenada() << "\n";
    if (nueva_coordenada.obtener_abscisa() > 0){
		velocidad_x = 0;
    }
    if (nueva_coordenada.obtener_ordenada() > 0){
		velocidad_y = 0;
    }
  }
}

void Megaman::recibir_ataque(Bala* ataque){
	ataque->daniar(this);
}
