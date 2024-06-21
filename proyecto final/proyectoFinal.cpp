#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread> // Para std::this_thread::sleep_for
#include <chrono> // Para std::chrono::milliseconds

using namespace std;

// Definir la longitud de la carrera
const int RACE_LENGTH = 100;

// Función para mostrar la posición actual de cada caballo en la consola
void displayRace(int horsePositions[], int numHorses) {
    for (int i = 0; i < numHorses; i++) {
        for (int j = 0; j < horsePositions[i]; j++) {
            cout << "-";
        }
        cout << i + 1 << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0)); // Inicializar el generador de números aleatorios

    int numHorses;
    cout << "Ingrese el número de caballos: ";
    cin >> numHorses;

    // Crear un arreglo dinámico para almacenar la posición de cada caballo
    int *horsePositions = new int[numHorses]();
    
    bool raceOver = false; // Variable para determinar si la carrera ha terminado
    while (!raceOver) {
        // Limpiar la pantalla
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Actualizar las posiciones de los caballos
        for (int i = 0; i < numHorses; i++) {
            if (horsePositions[i] < RACE_LENGTH) {
                horsePositions[i] += rand() % 3; // Movimiento aleatorio: 0, 1, o 2 pasos
            }
            if (horsePositions[i] >= RACE_LENGTH) {
                raceOver = true; // Si un caballo cruza la meta, la carrera termina
            }
        }

        // Mostrar la carrera actualizada
        displayRace(horsePositions, numHorses);

        // Esperar un poco antes de la siguiente actualización
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    // Anunciar el caballo ganador
    for (int i = 0; i < numHorses; i++) {
        if (horsePositions[i] >= RACE_LENGTH) {
            cout << "¡El caballo " << i + 1 << " gana!" << endl;
        }
    }

    delete[] horsePositions; // Liberar la memoria asignada dinámicamente
    return 0;
}
