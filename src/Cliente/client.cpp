#include "../Comun/socket.h"
#include "window.h"

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[]){
	char* hostname = argv[1];
	char* puerto = argv[2];
	Socket* cliente = new Socket(NULL, puerto);

	// INICIALIZO TODO LO QUE TENGA QUE VER CON SDL
	SDL_Init(SDL_INIT_EVERYTHING);	
	
	//Me conecto al servidor
	if ((*cliente).conect(hostname, puerto) < 0){
		std::cout << "Problema en conect \n";
		printf("%s \n", strerror(errno));
		return 0;
	}

	char buffer[4];
	cliente->send("Hola", 4);
	cliente->receive(buffer, 4);

	std::cout << buffer << "\n";
	
	(*cliente).shutdown(SHUT_RDWR);
	delete cliente;
	
	// POR AHORA SOLO CORRE UNA VENTANA QUE IMPRIME POR 
	// STDOUT LAS TECLAS INGRESADAS
	Window main_window(WIDTH,HEIGHT);
	main_window.run();



	SDL_Quit();

	return 0;
}
