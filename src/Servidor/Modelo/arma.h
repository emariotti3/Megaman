#ifndef ARMA_H
#define ARMA_H

#include "bala.h"
#include "factory_observador_ubicable.h"

class Arma{
	protected:
		int balas_creadas;
		Factory_observador_ubicable *fact_ubicables;
	public:
		Arma(Factory_observador_ubicable *fact_ubicables):
		fact_ubicables(fact_ubicables){};
		//Ataca, es decir, crea una bala.
		virtual Bala* atacar(int dir_x, int dir_y, Coordenada c) = 0;
		//Destructor de la arma.
		virtual ~Arma() {}
};

#endif //ARMA_H
