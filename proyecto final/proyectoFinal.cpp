#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "colors.h"  
#include <limits>
using namespace std;

const int DISTANCIA_CARRERA = 100;
const int MAX_PARTICIPANTES = 10;

struct participante {
    string nombre;
    char identificador;
};

void posicion(int horsePositions[], participante participantes[], int numCaballos) {
    for (int i = 0; i < numCaballos; i++) {
        for (int j = 0; j < horsePositions[i]; j++) {
            cout << "-";
        }
        cout << "> (""Caballo de: "<< participantes[i].nombre << ") " << i + 1 << endl;
    }
    cout << endl;
}

void esperar(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

int main() {
    srand(time(0));
    int opcion, numeroParticipante = 0, victoriasUsuario = 0;
    participante participantes[MAX_PARTICIPANTES];

    cout << "\n\033[1;36mCARRERA DE CABALLOS\033[0m\n";
    do {
        cout << GREEN << "\n1) Inscribe los participantes";
        cout << BLUE << "\n2) Para jugar (Antes de jugar debes inscribir participantes)\n";
        cout << GRAY << "3) Para ver sus resultados\n";
        cout << ORANGE << "4) Desarrolladores\n";
        cout << RED << "5) Para salir\n";
        cout << WHITE << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 2:
            {
                if (numeroParticipante == 0) {
                    cout << "Primero debe inscribir a los participantes.\n";
                    break;
                }

                int eleccionUsuario;
                cout << "Elija el numero del caballo que cree que va a ganar (1 a " << numeroParticipante << "): ";
                cin >> eleccionUsuario;

                int* caballosPosiciones = new int[numeroParticipante](); // Array for horse positions
                bool raceOver = false;
                int caballoGanador = -1;

                while (!raceOver) {
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                    for (int i = 0; i < numeroParticipante; i++) {
                        if (caballosPosiciones[i] < DISTANCIA_CARRERA) {
                            caballosPosiciones[i] += rand() % 3; // Random advance 0-2 steps
                        }
                        if (caballosPosiciones[i] >= DISTANCIA_CARRERA && caballoGanador == -1) {
                            caballoGanador = i + 1;
                            raceOver = true;
                        }
                    }

                    posicion(caballosPosiciones, participantes, numeroParticipante);
                    esperar(200);
                }
                cout << "El caballo ganador es el numero " << caballoGanador << ". ¡Gana!" << endl;

                if (eleccionUsuario == caballoGanador) {
                    cout << "Enhorabuena! El caballo seleccionado ha ganado.\n";
                    victoriasUsuario++;
                } else {
                    cout << "El caballo seleccionado no ha ganado. Suerte para la proxima\n";
                }

                delete[] caballosPosiciones;
            }
            break;
        case 3:
            cout << (victoriasUsuario == 1 ? "Has ganado 1 vez." : "Has ganado " + to_string(victoriasUsuario) + " veces.") << endl;
            break;
        case 4:
            {
                const int width = 25;
                cout << left << setw(width) << "\nNombres"
                     << setw(width) << "Apellidos"
                     << setw(width) << "Carnet" << endl;
                cout << setfill('-') << setw(width * 3) << "" << setfill(' ') << endl;
                cout << setw(width) << "Gerson Alejandro"
                     << setw(width) << "Nerio Melgar"
                     << setw(width) << "00132024" << endl;
                cout << setw(width) << "Erick Alejandro"
                     << setw(width) << "Mejicanos Mariona"
                     << setw(width) << "00057324" << endl;
                cout << setw(width) << "Edwin Daniel"
                     << setw(width) << "Leiva Barrera"
                     << setw(width) << "00136124" << endl;
            }
            break;
        case 1:
            {
                cout << "Ingrese el numero de participantes (hasta un maximo de " << MAX_PARTICIPANTES << "): ";
                while (!(cin >> numeroParticipante) || numeroParticipante < 1 || numeroParticipante > MAX_PARTICIPANTES) {
                    if (cin.fail()) {
                        cin.clear();
                        cout << "Entrada invalida. Por favor, ingrese un numero entre 1 y " << MAX_PARTICIPANTES << ": ";
                    } else {
                        cout << "El numero debe estar entre 1 y " << MAX_PARTICIPANTES << ". Intente de nuevo: ";
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                for (int i = 0; i < numeroParticipante; i++) {
                    cout << "Ingrese el nombre del participante " << i + 1 << ": ";
                    cin >> ws;
                    getline(cin, participantes[i].nombre);
                    cout << "Ingrese un caracter identificativo para " << participantes[i].nombre << ": ";
                    cin >> participantes[i].identificador;
                }
                cout << "Participantes inscritos:\n";
                for (int i = 0; i < numeroParticipante; i++) {
                    cout << "Nombre: " << participantes[i].nombre << ", Identificador: " << participantes[i].identificador << endl;
                }
            }
            break;
        case 5:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "No existe un valor para dicho numero\n";
            break;
        }
    } while (opcion != 5);

    return 0;
}
