#include "evento_mover.h"
#include "juego.h"
#include <sstream>
#include <string>
#include <iostream>

Evento_mover::Evento_mover(int id, int dir) : direccion(dir){
	std::stringstream	s;
	s << "megaman" <<id;
	id_evento = s.str();
}

int Evento_mover::get_direccion(){
	return direccion;
}

void Evento_mover::ejecutar(Juego& j){
  std::cout << "me muevo en direcion " << direccion << "\n";
  j.personaje_mover(id_evento, direccion);
}

Evento_mover::~Evento_mover(){}
