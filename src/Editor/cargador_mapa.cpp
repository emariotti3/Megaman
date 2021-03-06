#include "cargador_mapa.h"
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>

#define NOMBRE_ARCH_MAPAS "mapa"
#define NOMBRE_ARCH_MAPAS_BOSS "mapa_boss"
#define EXTENSION_ARCH_MAPAS ".txt"
#define MIN_NIVELES 0
#define MAX_NIVELES 4
#define MULT_X 30
#define MULT_Y 30

enum codigos_personajes{MEGAMAN = 1, BUMBY, J_SNIPPER, MET, SNIPPER};
enum codigos_elementos{BLOQUE = 10, PUAS, ESCALERA, PUERTA_BOSS = 18};
enum codigos_bosses{BOMBMAN = 20, MAGNETMAN, SPARKMAN, RINGMAN, FIREMAN};

//---------------------->Auxiliares<-------------------//

std::vector<std::string> Cargador_mapa::parsear_cadena_palabras(std::string cadena){
  std::istringstream cadena_parseada(cadena);
  std::string palabra;
  std::vector<std::string> v;

  while (cadena_parseada >> palabra){
    v.push_back(palabra);
  }
  return v;
}

//-----------------------------------------------------//

Cargador_mapa::Cargador_mapa(const char *root):
root_path(root),
boss(0),
id_mapa_elegido(1),
ancho_mapa(0),
alto_mapa(0),
coordenada_puerta_boss(0,0),
es_predefinido(false){}

void Cargador_mapa::cargar_mapa(int id_mapa){
	id_mapa_elegido = id_mapa;
	std::stringstream id;
	id << id_mapa;
	std::string nombre_arch(NOMBRE_ARCH_MAPAS);
	std::string extension_arch(EXTENSION_ARCH_MAPAS);
	std::string path = root_path + nombre_arch + id.str() + extension_arch;
	cargar(path);
}

void Cargador_mapa::cargar(std::string path){
	ancho_mapa = 0;
	alto_mapa = 0;
	limpiar_mapa();
	mapa_arch.open(path.c_str());
	cargar_coordenadas();
	mapa_arch.close();
	if (id_mapa_elegido >= MIN_NIVELES && id_mapa_elegido <= MAX_NIVELES){
		es_predefinido = true;
	}
}

void Cargador_mapa::agregar_objeto(int codigo_obj, int x, int y){
	Coordenada *coordenada = new Coordenada(x , y);
    switch(codigo_obj){
		case MEGAMAN:
			coordenada_megaman.push_back(coordenada);
			break;
		case BUMBY:
			coordenadas_bumby.push_back(coordenada);
			break;
		case J_SNIPPER:
			coordenadas_j_snippers.push_back(coordenada);
			break;
		case MET:
			coordenadas_mets.push_back(coordenada);
			break;
		case SNIPPER:
			coordenadas_snippers.push_back(coordenada);
			break;
		case BLOQUE:
			coordenadas_bloques.push_back(coordenada);
			break;
		case ESCALERA:
			coordenadas_escaleras.push_back(coordenada);
			break;
		case PUAS:
			coordenadas_puas.push_back(coordenada);
			break;
		case PUERTA_BOSS:
			coordenada_puerta_boss = *coordenada;
			break;
		case BOMBMAN:
			boss = BOMBMAN;
			coordenada_boss.push_back(coordenada);
			break;
		case MAGNETMAN:
			boss = MAGNETMAN;
			coordenada_boss.push_back(coordenada);
			break;
		case SPARKMAN:
			boss = SPARKMAN;
			coordenada_boss.push_back(coordenada);
			break;
		case RINGMAN:
			boss = RINGMAN;
			coordenada_boss.push_back(coordenada);
			break;
		case FIREMAN:
			boss = FIREMAN;
			coordenada_boss.push_back(coordenada);
			break;
	}
}

void Cargador_mapa::cargar_coordenadas(){
	std::string linea;
	getline(mapa_arch, linea);
	int x = 0, y = 0, codigo_obj = 0;
	//Primero obtengo las dimensiones del mapa
	std::vector<std::string> linea_parseada = parsear_cadena_palabras(linea);
	ancho_mapa = atoi(linea_parseada[0].c_str())*MULT_X;
	alto_mapa = atoi(linea_parseada[1].c_str())*MULT_Y;
  
	//Ahora obtengo las coordenadas de los objetos del mapa.
	while (getline(mapa_arch, linea)){
		linea_parseada = parsear_cadena_palabras(linea);
		if (linea_parseada.size() < 3){ //necesito un código + 2 coordenadas.
			//excepcion!
			return;
		}
		codigo_obj = atoi(linea_parseada[0].c_str());
		x = atoi(linea_parseada[1].c_str());
		y = atoi(linea_parseada[2].c_str());
		agregar_objeto(codigo_obj, x, y);
	}
}

void Cargador_mapa::limpiar_mapa(){
	coordenada_boss.clear();
	coordenadas_escaleras.clear();
	coordenadas_bloques.clear();
	coordenadas_puas.clear();
	coordenadas_mets.clear();
	coordenadas_bumby.clear();
	coordenadas_j_snippers.clear();
	coordenadas_snippers.clear();
	boss = 0;
	alto_mapa = 0;
	ancho_mapa = 0;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenada_boss(){
	return coordenada_boss;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenada_megamans(){
	return coordenada_megaman;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_mets(){
	return coordenadas_mets;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_bloques(){
	return coordenadas_bloques;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_puas(){
	return coordenadas_puas;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_escaleras(){
	return coordenadas_escaleras;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_snippers(){
	return coordenadas_snippers;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_j_snippers(){
	return coordenadas_j_snippers;
}

std::vector<Coordenada*> Cargador_mapa::get_coordenadas_bumby(){
	return coordenadas_bumby;
}

Coordenada Cargador_mapa::get_coordenada_puerta_boss(){
	return coordenada_puerta_boss;
}

int Cargador_mapa::get_ancho_mapa(){
	return ancho_mapa;
}

int Cargador_mapa::get_alto_mapa(){
	return alto_mapa;
}

int Cargador_mapa::get_boss(){
	return boss;
}

bool Cargador_mapa::mapa_es_predefinido(){
	return es_predefinido;
}
