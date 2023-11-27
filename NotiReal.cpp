#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    cout << "Recibido mensaje: " << msg->get_payload() << endl;
}

int main() {
    // Crear el servidor WebSocket
    server servidor;

    // Configurar la función de callback para manejar mensajes recibidos
    servidor.set_message_handler(bind(&on_message, &servidor, placeholders::_1, placeholders::_2));

    try {
        // Habilitar el puerto 9002
        servidor.listen(9002);

        // Iniciar el servidor
        servidor.start_accept();

        cout << "Servidor WebSocket iniciado en el puerto 9002" << endl;

        // Ejecutar el servidor en bucle
        servidor.run();
    } catch (websocketpp::exception const & e) {
        cout << "Error en el servidor: " << e.what() << endl;
    } catch (...) {
        cout << "Error desconocido en el servidor" << endl;
    }

    return 0;
}