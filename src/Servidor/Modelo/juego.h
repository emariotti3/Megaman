#ifndef JUEGO_H
#define JUEGO_H

#include "../../Comun/mutex.h"
#include "actualizable.h"
#include "mapa.h"
#include "juego_observable.h"
#include "megaman_factory.h"
#include <string>
#include <iosfwd>
#include <cstddef>
class PersonajeFactory;
class MegamanFactory;

class Juego:
public Juego_observable{
	private:
		Mapa *mundo;
		Mutex proteccion;
		bool fin_partida;
		int cant_jugadores;
		std::map<std::string, MegamanFactory*> factories;

	public:
		//Dado un tamanio, crea un juego nuevo.
		Juego(size_t long_x, size_t long_y);
		//Dada una cantidad de jugadores, inicializa una partida.
		void inicializar_partida(int cant_jugadores);
		//Implementa el ciclo del juego.
		void jugar();
		//Termina la partida en marcha.
		void terminar_partida();
		//Dado un determinado tiempo, actualiza al juego.
		virtual void update(size_t tiempo);
		
		void notificar_observadores();
		virtual void update(Observable *obs);
		//Dado el id de un personaje, hace que el mismo ataque en una direccion
		//dada.
		void personaje_atacar(int id_pj, int direccion);
		//Dado el id de un personaje, hace que el mismo se mueva en una direccion
		//dada.
		void personaje_mover(int id_pj, int direccion);
		//Dado el id de un personaje, hace que el mismo se deje de mover en una
		//direccion dada.
		void personaje_parar(int id_pj, int direccion);
		//Dado el id de un personaje y un numero de arma, hace que el mismo cambie a
		//la misma.
		void personaje_cambiar_arma(int id_pj, int arma);

		int long_y_mapa();
		int long_x_mapa();

		//Quita un observador del juego.
		void quitar_observador(Observador_juego *observador);
		//Agrega un observador al juego.
		void agregar_observador(Observador_juego *observador);
		//Notifica a los observadores que finalizo la partida.
		void notificar_termino_partida();
		//Notifica a los observadores que se produjo un gameover.
		void notificar_gameover(int id);
		//Notifica a los observadores que murio un determinado pj.
		void notificar_murio_personaje(int tipo, int id);
		//Notifica a los observadores que se modifico la cantidad de vidas de un
		//personaje.
		void notificar_cantidad_vidas(int tipo, int id, int vidas);
		//Notifica a los observadores que se modifico el porcentaje de vida de un
		//personaje.
		void notificar_porcentaje_vida(int tipo, int id, int cant_vida);
		//Notifica a los observadores que se modifico el porcentaje de energia de un
		//personaje.
		void notificar_energia(int tipo, int id, int energia);
		//Notifica a los observadores que se modifico la posicion de un personaje.
		void notificar_posicion(int tipo, int id, int x, int y);
		//Recibe id y tipo correspondiente a un personaje y
		//notifica al servidor de la muerte del mismo.
		void murio_personaje(int tipo, int id);
		//Recibe id y tipo correspondiente a un personaje y
		//una cantidad de vidas y notifica al servidor 
		//de la nueva cantidad de vidas del mismo.
		void actualizo_cantidad_vidas(int tipo, int id, int vidas);
		//Recibe id y tipo correspondiente a un personaje y
		//un porcentaje de vida y notifica al servidor 
		//cantidad de vida del mismo.
		void actualizo_porcentaje_vida(int tipo, int id, int cant_vida);
		//Recibe id y tipo correspondiente a un personaje y
		//un porcentaje de energia y notifica al servidor 
		//cantidad de energia del mismo.
		void actualizo_energia(int tipo, int id, int energia);
		//Recibe id y tipo correspondiente a un personaje y
		//su posicion actual y notifica al servidor de
		//la nueva posicion.
		void actualizo_posicion(int tipo, int id, int x, int y);

		std::vector<Coordenada> bloques();

		//Destructor de juego.
		~Juego();
};

#endif //JUEGO_H