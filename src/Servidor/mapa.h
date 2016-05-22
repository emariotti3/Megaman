#ifndef MAPA_H
#define MAPA_H

#include <map>
#include <vector>
#include "celda.h"
#include "coordenada.h"

class Elemento;

class Mapa{
  private:
    std::map<size_t, std::map<size_t, Celda*> > celdas;
    size_t tam;
  public:
    //Dado un tamanio, crea un mapa.
    Mapa(size_t tamanio);
    Celda* obtener_celda(Coordenada &coordenada);
  private:
    //Carga un mapa, por ahora, una versión por defecto chica.
    void cargar();
    //Recibe un elemento y las coordenadas donde se desea posicionar al mismo.
    void ocupar_elemento(Elemento& elem, std::vector<Coordenada> &coordenadas);
    //Recibe un vector con coordenadas de donde se quieran agregar las celdas;
    void ocupar_tierra(std::vector<Coordenada> &coordenadas);
    void ocupar_personajes(std::vector<Coordenada*> &coordenadas);
    //Inicializa las celdas aereas del mapa:
    void rellenar_aire();
};

#endif //MAPA_H
