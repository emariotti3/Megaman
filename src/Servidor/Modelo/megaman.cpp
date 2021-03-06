#include "megaman.h"
#include "arma_megaman.h"
#include <string>
#include <iostream>
#include <sstream>
#include "bala.h"


#define DERECHA 3
#define IZQUIERDA 4
#define MEGAMAN 1
#define TIEMPO_ACCION 0.4
#define CANTIDAD_VIDAS 3

#define ALTO 60
#define ANCHO 30

typedef std::map<int, StrategyMoverPersonajePc*>::iterator movimientosIt;
enum estados_pc{MURIENDO, DISPARANDO, RESPAWNEANDO, CORRIENDO, SALTANDO,
		IDLE, ESCALANDO};

Megaman::Megaman(Mapa *mapa, Coordenada c, Arma_megaman *arma, int id):
Personaje_pc(mapa, c, id){
	energia = 0;
	for (size_t i = 0; i < CANTIDAD_VIDAS; i++){
		Vida v = Vida();
		vidas.push_back(v);
	}
	armas.push_back(arma);
	arma_act = 0;
	tipo = MEGAMAN;
	movimientos = std::map<int, StrategyMoverPersonajePc*>();
	movimiento_megaman = new StrategyMoverMegaman();
	movimiento_actual = movimiento_megaman;
	estado_actual = IDLE;
	ancho = ANCHO;
	alto = ALTO;
}
/*
void Megaman::update(float tiempo){
	Personaje::update(tiempo, mapa);
}*/

void Megaman::atacar(int dir, Mapa* mapa){
	Bala* bala;
	Coordenada pos_inicial(-1, -1);
	if (dir == DERECHA){
		pos_inicial = coordenada.derecha(ancho/2);
		bala = armas[arma_act]->atacar(dir, 0, pos_inicial);
	}
	if (dir == IZQUIERDA){
		pos_inicial = coordenada.izquierda(ancho/2);
		bala = armas[arma_act]->atacar(dir, 0, pos_inicial);
	}
	estado_actual = DISPARANDO;
	mapa->agregar_bala(bala);
	bala->notificar_observadores();
}

void Megaman::mover(float tiempo, Mapa* mapa){
	if (tiempo_pasado < TIEMPO_ACCION){
		return;
	}
	tiempo_pasado -= TIEMPO_ACCION;
	//Me muevo utilizando la estrategia
	//de movimiento actual:
	movimiento_actual->mover(mapa, this, tiempo);
	//Elimino todas las estrategias especiales
	//adquiridas hasta el momento:
	movimientos.clear();
	//Interactuo con elementos de la nueva
	//ubicacion:
	//mapa->interactuar_con_entorno(this);
}

void Megaman::agregar_movimiento(int direccion){
	if (movimientos.find(direccion)!= movimientos.end()){
		//Si ya tengo una estrategia para moverme en esta
		//direccion uso esa estrategia:
		movimiento_actual = movimientos[direccion];
	}else{
		//Si no tengo una estrategia para moverme
		//en esta direccion agrego la direccion al
		//movimiento normal:
		movimiento_megaman->agregar_movimiento(this, direccion);
		movimiento_actual = movimiento_megaman;
	}
}

void Megaman::agregar_movimiento(StrategyMoverPersonajePc *movimiento){
	movimientos[movimiento->get_direccion()] = movimiento;
}

void Megaman::sacar_movimiento(int direccion){
	movimiento_actual->sacar_movimiento(this, direccion);
}

void Megaman::recibir_ataque(Bala* ataque){
	ataque->daniar(this);
}

void Megaman::agregar_arma(Arma *arma){
	armas.push_back(arma);
}


void Megaman::interactuar(Escalera *esc){
	esc->interactuar(this);
}

void Megaman::perder_energia(int porcentaje){
	if ((energia - porcentaje) <= 0){
		energia = 0;
	}else{
		energia -= porcentaje;
	}
}

void Megaman::ganar_energia(int porcentaje){
	if ((porcentaje - energia) >= GANAR_MAX){
		energia = GANAR_MAX;
	}else{
		energia += porcentaje;
	}
}

int Megaman::get_energia(){
	return 0; //TODO: cambiar al valor de la energia actual!
}

void Megaman::perder_vida(int porcentaje){
	if(!this->esta_vivo()){
		return;
	}
	vidas[0].perder(porcentaje);
	if (vidas[0].esta_vacia()){
		vidas.erase(vidas.begin());
	}
	if(!this->esta_vivo()){
		estado_actual = MURIENDO;
	}
	notificar_observadores();
}

void Megaman::ganar_vida(int porcentaje){
	if (porcentaje == GANAR_MAX){
		Vida vida_nueva = Vida();
		vidas.push_back(vida_nueva);
	}else{
		vidas[0].ganar(porcentaje);
	}
}

bool Megaman::esta_vivo(){
	return !vidas.empty();
}

size_t Megaman::get_cantidad_vidas(){
	return vidas.size();
}

int Megaman::get_porcentaje_vida(){
	int porcentaje = 0;
	if (!vidas.empty()){
		porcentaje = vidas[0].get_porcentaje();
	}
	return porcentaje;
}

void Megaman::interactuar(Capsula_de_energia *capsula){
	capsula->interactuar(this);
}

int Megaman::construir_id_megaman(int id){
	return Ubicable::construir_id_unico(MEGAMAN, id);
}
