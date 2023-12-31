#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Mensaje {
public:
    string remitente;
    string contenido;
    time_t tiempo;

    Mensaje(const string& rem, const string& cont)
        : remitente(rem), contenido(cont), tiempo(std::time(nullptr)) {}
};

class Tarea {
public:
    string descripcion;
    vector<Mensaje> mensajes;

    Tarea(const string& desc) : descripcion(desc) {}

    void agregarMensaje(const string& remitente, const string& contenido) {
        mensajes.emplace_back(remitente, contenido);
    }

    void mostrarMensajes() const {
        cout << "Mensajes para la tarea '" << descripcion << "':" << endl;
        for (const auto& mensaje : mensajes) {
            cout << "[" << asctime(localtime(&mensaje.tiempo)) << "] "
                 << mensaje.remitente << ": " << mensaje.contenido << endl;
        }
    }
};

class TableroProyectos {
private:
    vector<Tarea> tareas;

public:
    void agregarTarea(const string& descripcion) {
        tareas.emplace_back(descripcion);
    }

    void agregarMensajeTarea(int indiceTarea, const string& remitente, const string& contenido) {
        if (indiceTarea >= 0 && indiceTarea < tareas.size()) {
            tareas[indiceTarea].agregarMensaje(remitente, contenido);
        } else {
            cout << "Error: Indice de tarea no valido." << endl;
        }
    }

    void mostrarTablero() const {
        cout << "Tablero de Proyectos:" << endl;
        for (size_t i = 0; i < tareas.size(); ++i) {
            cout << "Tarea " << i + 1 << ": " << tareas[i].descripcion << endl;
            tareas[i].mostrarMensajes();
            cout << endl;
        }
    }
};

void menuPrincipal(TableroProyectos& tablero);
void crearNuevaTarea(TableroProyectos& tablero);
void agregarMensajeATarea(TableroProyectos& tablero);

int main() {
    TableroProyectos tablero;
    menuPrincipal(tablero);
    return 0;
}

void menuPrincipal(TableroProyectos& tablero) {
    string opcionStr;
    int opcion;

    do {
        cout << "\n=== Menu Principal ===" << endl;
        cout << "1. Crear nueva tarea\n";
        cout << "2. Agregar mensaje a tarea\n";
        cout << "3. Mostrar tablero\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionStr;

        try {
            opcion = stoi(opcionStr);
        } catch (const invalid_argument& e) {
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                crearNuevaTarea(tablero);
                break;
            case 2:
                agregarMensajeATarea(tablero);
                break;
            case 3:
                tablero.mostrarTablero();
                break;
            case 0:
                cout << "Saliendo del programa. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opcion no valida. Intentelo de nuevo.\n";
        }
    } while (opcion != 0);
}

void crearNuevaTarea(TableroProyectos& tablero) {
    string descripcion;
    cout << "Ingrese la descripcion de la nueva tarea: ";
    cin.ignore();
    getline(cin, descripcion);
    tablero.agregarTarea(descripcion);
    cout << "Nueva tarea creada con exito.\n";
}

void agregarMensajeATarea(TableroProyectos& tablero) {
    int indiceTarea;
    string remitente, contenido;

    cout << "Ingrese el indice de la tarea a la que desea agregar un mensaje: ";
    cin >> indiceTarea;

    cout << "Ingrese su nombre (remitente del mensaje): ";
    cin >> remitente;

    cout << "Ingrese el contenido del mensaje: ";
    cin.ignore();
    getline(cin, contenido);

    tablero.agregarMensajeTarea(indiceTarea - 1, remitente, contenido);
    cout << "Mensaje agregado con exito a la tarea " << indiceTarea << ".\n";
}
