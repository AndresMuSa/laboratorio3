#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <memory>
#include <limits>
#include "SteamFighter.h"
#include "Batalla.h"

using namespace std;

const int MAX_LUCHADORES = 20;

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para crear un nuevo luchador con opción de poderes aleatorios
unique_ptr<SteamFighter> crearNuevoLuchador() {
    string nombre;
    int defensa;
    array<Ataque, 4> ataques;

    cout << "Nombre del nuevo luchador: ";
    getline(cin >> ws, nombre);
    
    cout << "Ingresa la defensa del luchador (0-20): ";
    cin >> defensa;
    while (cin.fail() || defensa < 0 || defensa > 20) {
        cout << "Error: Valor de defensa invalido. Ingresa un numero entre 0 y 20: ";
        cin.clear();
        limpiarBuffer();
        cin >> defensa;
    }
    limpiarBuffer();

    // Opción para elegir danio de poderes
    cout << "¿Como deseas asignar el danio de los poderes?\n";
    cout << "1. Asignar manualmente (0-100)\n";
    cout << "2. Asignar de forma aleatoria (0-100)\n";
    cout << "Elige una opcion: ";
    int opcion;
    cin >> opcion;

    while (cin.fail() || (opcion != 1 && opcion != 2)) {
        cout << "Error: Opcion invalida. Por favor, elige 1 o 2: ";
        cin.clear();
        limpiarBuffer();
        cin >> opcion;
    }
    limpiarBuffer();

    for (int i = 0; i < 4; i++) {
        cout << "Nombre del ataque #" << (i + 1) << ": ";
        getline(cin, ataques[i].nombre);
        if (ataques[i].nombre.empty()) ataques[i].nombre = "Ataque_sin_nombre";

        if (opcion == 1) { // Manual
            cout << "Danio base para " << ataques[i].nombre << " (0-100): ";
            cin >> ataques[i].danoBase;
            while (cin.fail() || ataques[i].danoBase < 0 || ataques[i].danoBase > 100) {
                cout << "Error: Valor de danio invalido. Ingresa un numero entre 0 y 100: ";
                cin.clear();
                limpiarBuffer();
                cin >> ataques[i].danoBase;
            }
        } else { // Aleatorio
            ataques[i].danoBase = rand() % 101;
            cout << "El danio de " << ataques[i].nombre << " ha sido asignado aleatoriamente a " << ataques[i].danoBase << ".\n";
        }
        // El costo de estamina ha sido eliminado
        ataques[i].costoStamina = 0; 
        limpiarBuffer();
    }

    return make_unique<SteamFighter>(nombre, defensa, ataques[0], ataques[1], ataques[2], ataques[3]);
}

// Función para mostrar los luchadores disponibles
void mostrarLuchadores(const vector<unique_ptr<SteamFighter>>& lista) {
    cout << "\nLuchadores disponibles:\n";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << i + 1 << ". " << lista[i]->nombre << "\n";
    }
}

int main() {
    srand(time(0));

    vector<unique_ptr<SteamFighter>> lista;

    // Agregar luchadores predefinidos
    lista.push_back(make_unique<SteamFighter>("Aquaman", 15, Ataque{"Tridente Marino", 25, 0}, Ataque{"Oleada Acuatica", 30, 0}, Ataque{"Golpe de Marea", 15, 0}, Ataque{"Llamado de Tiburones", 40, 0}));
    lista.push_back(make_unique<SteamFighter>("Lucario", 10, Ataque{"Esfera Aural", 30, 0}, Ataque{"Puno Incremento", 20, 0}, Ataque{"Velocidad Extrema", 15, 0}, Ataque{"Onda Vacio", 35, 0}));
    lista.push_back(make_unique<SteamFighter>("Mewtwo", 5, Ataque{"Psicocorte", 35, 0}, Ataque{"Bola Sombra", 25, 0}, Ataque{"Confusion", 10, 0}, Ataque{"Poder Oculto", 40, 0}));
    lista.push_back(make_unique<SteamFighter>("Pikachu", 8, Ataque{"Impactrueno", 25, 0}, Ataque{"Rayo", 30, 0}, Ataque{"Placaje", 15, 0}, Ataque{"Trueno", 40, 0}));
    lista.push_back(make_unique<SteamFighter>("Spiderman", 12, Ataque{"Telarana", 10, 0}, Ataque{"Golpe Acrobatico", 25, 0}, Ataque{"Patada Giratoria", 20, 0}, Ataque{"Lanzamiento de Telarana", 30, 0}));
    lista.push_back(make_unique<SteamFighter>("Elastigirl", 18, Ataque{"Golpe Extensible", 20, 0}, Ataque{"Patada Flexible", 25, 0}, Ataque{"Lazo Elastico", 15, 0}, Ataque{"Bloqueo Estirable", 10, 0}));
    lista.push_back(make_unique<SteamFighter>("Goku", 15, Ataque{"Kamehameha", 40, 0}, Ataque{"Golpe del Dragon", 35, 0}, Ataque{"Puno Meteoro", 25, 0}, Ataque{"Genki Dama", 50, 0}));

    while (true) {
        cout << "\n--- Menu principal ---\n";
        cout << "1. Agregar nuevo luchador\n";
        cout << "2. Mostrar luchadores disponibles\n";
        cout << "3. Iniciar batalla (elegir luchadores)\n";
        cout << "4. Iniciar batalla aleatoria\n";
        cout << "5. Salir\n";
        cout << "Elige una opcion: ";
        int opcion;
        cin >> opcion;

        if (cin.fail()) {
            cout << "Error: Entrada invalida. Por favor, ingresa un numero.\n";
            cin.clear();
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        switch (opcion) {
            case 1: {
                if (lista.size() < MAX_LUCHADORES) {
                    lista.push_back(crearNuevoLuchador());
                    cout << "Luchador agregado exitosamente.\n";
                } else {
                    cout << "No se pueden agregar mas luchadores. Capacidad maxima alcanzada.\n";
                }
                break;
            }
            case 2:
                mostrarLuchadores(lista);
                break;
            case 3: {
                if (lista.size() < 2) {
                    cout << "No hay suficientes luchadores para iniciar una batalla.\n";
                    break;
                }
                int luchador1_index, luchador2_index;
                mostrarLuchadores(lista);
                cout << "Elige el primer luchador (1-" << lista.size() << "): ";
                cin >> luchador1_index;
                cout << "Elige el segundo luchador (1-" << lista.size() << "): ";
                cin >> luchador2_index;

                while (cin.fail() || luchador1_index < 1 || luchador1_index > lista.size() || 
                       luchador2_index < 1 || luchador2_index > lista.size() || luchador1_index == luchador2_index) {
                    cout << "Error: Seleccion de luchador invalida. Intenta de nuevo.\n";
                    cin.clear();
                    limpiarBuffer();
                    mostrarLuchadores(lista);
                    cout << "Elige el primer luchador (1-" << lista.size() << "): ";
                    cin >> luchador1_index;
                    cout << "Elige el segundo luchador (1-" << lista.size() << "): ";
                    cin >> luchador2_index;
                }
                limpiarBuffer();

                Batalla batalla(*lista[luchador1_index - 1], *lista[luchador2_index - 1]);
                batalla.iniciarBatalla();
                break;
            }
            case 4: {
                if (lista.size() < 2) {
                    cout << "No hay suficientes luchadores para iniciar una batalla.\n";
                    break;
                }

                int index1 = rand() % lista.size();
                int index2;
                do {
                    index2 = rand() % lista.size();
                } while (index1 == index2);

                Batalla batalla(*lista[index1], *lista[index2]);
                batalla.iniciarBatalla();
                break;
            }
            case 5:
                cout << "Saliendo del programa...\n";
                return 0;
            default:
                cout << "Error: Opcion no valida. Por favor, elige una opcion del 1 al 5.\n";
        }
    }
}