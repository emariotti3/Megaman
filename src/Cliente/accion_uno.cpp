#include "accion_uno.h"

Accion_uno::Accion_uno(Socket* conexion){
  skt = conexion;
  Gtk::Button boton("Click 2");
  boton.signal_clicked().connect(sigc::ptr_fun(&on_button_clicked));
}

void Accion_uno::on_button_clicked(){
  std::string mensaje = "Me hicieron un click (1)!";
  std::cout << mensaje << std::endl;
  skt.send(mensaje.c_str(), mensaje.size());
}

Gtk::Button Accion_uno::devolver_boton(){
  return boton;
}