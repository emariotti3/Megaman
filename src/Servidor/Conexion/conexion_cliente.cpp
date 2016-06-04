#include "conexion_cliente.h"
#include <sstream>

#include <iostream>
#include <stdio.h>
#include <string.h>

#define TAM_INT 4

enum Codigo {POSICION = 1, VIDA, ENERGIA, CANT_VIDAS, VICTORIA, DERROTA};

void Conexion_cliente::mandar_bloques(std::vector<Coordenada> b){
	int codigo_bloque = 100;
	int fin_mapa = 6666;
	for(size_t i = 0; i < b.size(); i++){
		int x = b[i].obtener_abscisa();
		int y = b[i].obtener_ordenada();
		skt->send((char*)&codigo_bloque, TAM_INT);
		skt->send((char*)&x, TAM_INT);
		skt->send((char*)&y, TAM_INT);
	}
	skt->send((char*)&fin_mapa, TAM_INT);
}

Conexion_cliente::Conexion_cliente(Socket* conexion, int id, Juego *m) : skt(conexion), id_cliente(id),
rcv(conexion, id, m) {
	obtener_nombre_jugador();
	skt->send((char*)&id, TAM_INT); //le envio al jugador su id
	enviar_mapa_inicial(m, id);
}

void Conexion_cliente::enviar_mapa_inicial(Juego* m, int id){
	enviar_tamanio_mapa(m);
	mandar_bloques(m->bloques());

	int megaman_x = 3; //hardcodeo para que axel pruebe hoy.
	int megaman_y = 6;
	skt->send((char*)&id, TAM_INT);
	skt->send((char*)&megaman_x, TAM_INT);
	skt->send((char*)&megaman_y, TAM_INT);

	/*
	std::vector<Ubicables*> ubicables = m->obtener_ubicables();
	for (size_t i = 0; i < ubicables.size(); i++){
		Ubicable* ubicable = ubicables[i];

		int id_clase = ubicable.devolver_id_clase();
		int id = ubicable.devolver_id();

		Coordenada central = ubicable.devolver_coordenada_central();
		int alto = ubicable.devolver_alto();
		int ancho = ubicable.devolver_ancho();
		Coordenada a_enviar = central.arriba(alto).izquierda(ancho);
		int coord_x = a_enviar.obtener_abscisa();
		int coord_y = a_enviar.obtener_ordenada();

		skt->send((char*)&id_clase, TAM_INT);
		skt->send((char*)&id, TAM_INT);
		skt->send((char*)&x, TAM_INT);
		skt->send((char*)&y, TAM_INT);
	}
	*/
}

std::string Conexion_cliente::obtener_nombre_jugador(){
	char largo_nombre[TAM_INT];
	skt->receive(largo_nombre, TAM_INT);
	int tam = *((int*) largo_nombre);
	char nombre[tam];
	skt->receive(nombre, tam);

	std::string nombre_j(nombre);
	return nombre_j;
}

void Conexion_cliente::enviar_tamanio_mapa(Juego* m){
	int long_y = m->long_y_mapa();
	int long_x = m->long_x_mapa();

	skt->send((char*)&long_x, TAM_INT);
	skt->send((char*)&long_y, TAM_INT);
}



void Conexion_cliente::iniciar_ejecucion(){
	rcv.start();
}

void Conexion_cliente::terminar_ejecucion(){
  rcv.terminar_ejecucion();
}

Conexion_cliente::~Conexion_cliente(){
  rcv.join();
}

void Conexion_cliente::enviar_cambio_posicion(int tipo, int id, int x, int y){
	int posicion = POSICION;
	std::stringstream pos_x, pos_y;
	pos_x << x;
	pos_y << y;
	std::string abscisa = pos_x.str();
	std::string ordenada = pos_y.str();
	skt->send((char*)&posicion, TAM_INT);
	skt->send((char*)&tipo, TAM_INT);
	skt->send((char*)&id, TAM_INT);
	skt->send((char*)&abscisa, TAM_INT);
	skt->send((char*)&ordenada, TAM_INT);
}

void Conexion_cliente::enviar_cantidad_vidas(int tipo, int id, int cantidad){
  int cant_vidas = CANT_VIDAS;
  skt->send((char*)&cant_vidas, TAM_INT);
  skt->send((char*)&tipo, TAM_INT);
  skt->send((char*)&id, TAM_INT);
  skt->send((char*)&cantidad, TAM_INT);
  skt->send("        ", TAM_INT);
  //Envio una cadena vacía de TAM_INT caracteres.
}

void Conexion_cliente::enviar_porcentaje_vida(int tipo, int id, int porcentaje){
  int vida = VIDA;
  skt->send((char*)&vida, TAM_INT);
  skt->send((char*)&tipo, TAM_INT);
  skt->send((char*)&id, TAM_INT);
  skt->send((char*)&porcentaje, TAM_INT);
  skt->send("        ", TAM_INT);
  //Envio una cadena vacía de TAM_INT caracteres.
}

void Conexion_cliente::enviar_porcentaje_energia(int tipo, int id, int porcentaje){
  int energia = ENERGIA;
  skt->send((char*)&energia, TAM_INT);
  skt->send((char*)&tipo, TAM_INT);
  skt->send((char*)&id, TAM_INT);
  skt->send((char*)&porcentaje, TAM_INT);
  skt->send("        ", TAM_INT);
  //Envio una cadena vacía de TAM_INT*2 caracteres.
}

void Conexion_cliente::enviar_victoria(){
  int victoria = VICTORIA;
  skt->send((char*)&victoria, TAM_INT);
  skt->send("            ", TAM_INT*3);
  //Envio una cadena vacía de TAM_INT*3 caracteres.
}

void Conexion_cliente::enviar_gameover(){
  int derrota = DERROTA;
  skt->send((char*)&derrota, TAM_INT);
  skt->send("            ", TAM_INT*3);
  //Envio una cadena vacía de TAM_INT*3 caracteres.
}