#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include "unistd.h"

#include "servidor.h"
#include <string>

#define POS_PUERTO 1

int main(int argc, char *argv[]){
  Servidor server(argv[POS_PUERTO]);
  server.aceptar_clientes();

  while (!server.termino_ejecucion()){
    /*server.actualizar_mundo();
    server.enviar_datos();
    clock*/
  }

  return 0;
}
