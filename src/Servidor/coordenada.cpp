#include "coordenada.h"

#include <math.h>

Coordenada::Coordenada(size_t ordenada, size_t abscisa){
  x = ordenada;
  y = abscisa;
}

size_t Coordenada::obtener_ordenada(){
  return x;
}

size_t Coordenada::obtener_abscisa(){
  return y;
}

size_t Coordenada::obtener_distancia(Coordenada otra_coordenada){
  size_t xcuadrado = pow((x-otra_coordenada.x),2);
  size_t ycuadrado = por((y-otra_coordenada.y),2);
  return sqrt(xcuadrado+ycuadrado);
}