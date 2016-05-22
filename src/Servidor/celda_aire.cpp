#include "celda_aire.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

Celda_aire::Celda_aire(size_t x, size_t y, Elemento* obstaculo):
Celda(x, y){
	elem = obstaculo;
}

void Celda_aire::agregar_personaje(Mapa &mapa, Personaje* ocupa){
	if (!ocupa){
		std::cout << "no tengo ocupa \n";
	}else{
		std::cout << "tengo ocupa! \n";
	}
	ocupantes[ocupa->devolver_id()] = ocupa;
	std::cout << "no me rompí!! \n";
	if (elem != NULL){
		elem->interactuar(mapa, ocupa);
	}
}

Personaje* Celda_aire::obtener_personaje(std::string &id){
	return ocupantes[id];
}

void Celda_aire::quitar_personaje(Personaje* ocupa){
	ocupantes.erase(ocupa->devolver_id());
}

bool Celda_aire::puedo_ubicar(){
	return true;
}

Celda_aire::~Celda_aire() {}
