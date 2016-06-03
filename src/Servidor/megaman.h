#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "personaje.h"
#include "bala.h"

class Arma;

class Megaman: public Personaje{
	private:
		Mapa *mapa;
		std::vector<Arma*> armas;
		size_t arma_act;
	public:
		Megaman(Mapa *mapa, Coordenada c, std::string id);
		virtual void atacar(int dir, Mapa* mapa);
		virtual void mover(size_t tiempo, Mapa* mapa);
		virtual void recibir_ataque(Bala* ataque);
		virtual void update(size_t tiempo);
};

#endif //MEGAMAN_H
