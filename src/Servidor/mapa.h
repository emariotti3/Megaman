#ifndef MAPA_H
#define MAPA_H

#include <map>
#include <vector>
#include "coordenada.h"
#include "actualizable.h"

class Personaje;
class Megaman;
class Elemento;
class Bala;

class Mapa{
  private:
    std::vector<Coordenada> bloques;
    std::vector<Bala*> balas;
    std::map<std::string, Personaje*> personajes;
    size_t tam;
  public:
    //Dado un tamanio, crea un mapa
    //con tantas divisiones como indique el tamanio.
    Mapa(size_t tamanio);
    //Devuelve true si la coordenada pertenece al mapa y false en el caso con-
    //trario.
    bool tiene_coordenada(Coordenada coordenada);
    //Dada una coordenada central y el ancho y el alto de un objeto, determina
    //si el mismo puede ocupar dicho espacio.
    bool puede_ubicarse_en(Coordenada coord, size_t alto, size_t ancho);
    /*//Dada una coordenada central origen y una coordenada central destino, el
    //ancho y el alto de un objeto, determina si el mismo puedo hacer ese movi-
    //miento.
    void puede_moverse_a(Coordenada *origen, Coordenada *destino, size_t alto,
    size_t ancho);*/
    //Dado el id de un personaje, lo devuelve.
    Personaje *obtener_pj(std::string id_pj);
    //Devuelve un vector con todos los actualizables que se ubican en el mapa.
    std::vector<Actualizable*> obtener_actualizables();
    //Devuelve true si abajo de un objeto de un alto determinado hay aire, false
    //en caso contrario.
    bool esta_en_aire(Coordenada coord, size_t alto);
    //Devuelve true si hay tierra en dicha coordenada, false en caso contrario.
    bool hay_tierra(Coordenada coord);
  private:
    //Carga un mapa, por ahora, una versión por defecto chica.
    void cargar();
    //Recibe un elemento y las coordenadas donde se desea posicionar al mismo.
    void ocupar_elemento(Elemento& elem, std::vector<Coordenada> &coordenadas);
    //Recibe un vector con coordenadas de donde se quieran agregar las celdas;
    void ocupar_tierra(std::vector<Coordenada> &coordenadas);
    void cargar_personajes(std::vector<Coordenada*> &coordenadas);

};

#endif //MAPA_H
