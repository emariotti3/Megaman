#ifndef CONEXION_CLIENTE_H
#define CONEXION_CLIENTE_H

#include "../../../Comun/socket.h"
#include "receiver_cliente.h"
#include "../../Modelo/juego.h"
#include "log.h"
#include "../Partida/estado.h"

#include <string>

class Servidor;

class Conexion_cliente{
  private:
    Socket* skt;
    int id_cliente;
    Receiver_cliente rcv;
    Juego* m;
  public:
    //Crea una conexion_cliente recibiendo como parametro un socket ya conecta-
    //do y un id que lo identifica.
    Conexion_cliente(Socket* conexion, int id, Juego *m, Servidor* s);
    //Inicia la ejecución, es decir, empieza a recibir información del cliente.
    void iniciar_ejecucion();
    //Le informa a la conexion_cliente que debe dejar de recibir datos.
    void terminar_ejecucion();
    //Le informa al conexion_cliente que se ha iniciado un nivel.
    void iniciar_nivel(int nivel);
    //Le informa al conexion_cliente que se ha terminado un nivel.
    void finalizar_nivel();
    //Destructor del Conexion_cliente.
    virtual ~Conexion_cliente();

    void update_estado(Estado estado);

  private:
    //Envia la informacion del mapa inicial.
    void enviar_mapa_inicial();
    //Obtiene el nombre del jugador.
    std::string obtener_nombre_jugador();
    //Envia el tamaño del mapa.
    void enviar_tamanio_mapa(Juego* m);
};

#endif //CONEXION_CLIENTE
