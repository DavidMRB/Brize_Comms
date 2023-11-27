#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Mensaje {
public:
    Mensaje(const string& remitente, const string& contenido) : remitente(remitente), contenido(contenido) {}

    string obtenerRemitente() const {
        return remitente;
    }

    string obtenerContenido() const {
        return contenido;
    }

private:
    string remitente;
    string contenido;
};

class Usuario {
public:
    Usuario(const string& nombre) : nombre(nombre) {}

    string obtenerNombre() const {
        return nombre;
    }

    void enviarMensaje(Usuario& destinatario, const string& contenido) {
        Mensaje mensaje(nombre, contenido);
        destinatario.recibirMensaje(mensaje);
    }

    void recibirMensaje(const Mensaje& mensaje) {
        bandejaDeEntrada.push_back(mensaje);
    }

    void mostrarBandejaDeEntrada() const {
        cout << "Bandeja de entrada de " << nombre << ":\n";
        for (const auto& mensaje : bandejaDeEntrada) {
            cout << "De: " << mensaje.obtenerRemitente() << "\n";
            cout << "Mensaje: " << mensaje.obtenerContenido() << "\n\n";
        }
    }

private:
    string nombre;
    vector<Mensaje> bandejaDeEntrada;
};

int main() {
    // Crear usuarios
    Usuario usuario1("Juan");
    Usuario usuario2("Lizeth");

    // Enviar mensajes
    usuario1.enviarMensaje(usuario2, "Hola, como estas?");
    usuario2.enviarMensaje(usuario1, "Hola estoy bien, y tu?");

    // Mostrar bandejas de entrada
    usuario2.mostrarBandejaDeEntrada();
    usuario1.mostrarBandejaDeEntrada();

    return 0;
}
