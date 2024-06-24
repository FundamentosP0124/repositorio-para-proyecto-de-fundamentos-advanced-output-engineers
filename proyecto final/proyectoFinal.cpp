#include <iostream> // Biblioteca para operaciones de entrada/salida
#include <cstdlib> // Biblioteca para funciones generales como rand() y srand()
#include <ctime> // Biblioteca para funciones relacionadas con el tiempo como time()

using namespace std; // Usar el espacio de nombres estándar

// Definir la longitud de la carrera
const int RACE_LENGTH = 100;

// Función para mostrar la posición actual de cada caballo en la consola
void displayRace(int horsePositions[], int numHorses) {
    for (int i = 0; i < numHorses; i++) { // Iterar sobre cada caballo
        for (int j = 0; j < horsePositions[i]; j++) { // Mostrar la posición del caballo
            cout << "-"; // Mostrar un guion por cada paso del caballo
        }
        cout <<"> "<<i + 1 << endl; // Mostrar el número del caballo
    }
    cout << endl; // Línea en blanco para separar cada actualización de la carrera
}

// Función para esperar una cantidad específica de milisegundos
void sleep(int milliseconds) {
    clock_t start_time = clock(); // Registrar el tiempo de inicio
    while (clock() < start_time + milliseconds); // Esperar hasta que haya transcurrido el tiempo especificado
}

int main() {
    srand(time(0)); // Inicializar el generador de números aleatorios con la hora actual

    int numHorses; // Variable para almacenar el número de caballos
    cout << "Ingrese el número de caballos: "; // Solicitar al usuario que ingrese el número de caballos
    cin >> numHorses; // Leer el número de caballos ingresado por el usuario

    // Crear un arreglo dinámico para almacenar la posición de cada caballo
    int *horsePositions = new int[numHorses](); // Inicializar el arreglo con ceros
    
    bool raceOver = false; // Variable para determinar si la carrera ha terminado
    while (!raceOver) { // Bucle principal de la carrera
        // Limpiar la pantalla
        #ifdef _WIN32
            system("cls"); // Limpiar pantalla en Windows
        #else
            system("clear"); // Limpiar pantalla en otros sistemas operativos
        #endif

        // Actualizar las posiciones de los caballos
        for (int i = 0; i < numHorses; i++) { // Iterar sobre cada caballo
            if (horsePositions[i] < RACE_LENGTH) { // Si el caballo no ha terminado la carrera
                horsePositions[i] += rand() % 3; // Movimiento aleatorio: 0, 1, o 2 pasos
            }
            if (horsePositions[i] >= RACE_LENGTH) { // Si el caballo ha llegado a la meta
                raceOver = true; // Marcar la carrera como terminada
            }
        }

        // Mostrar la carrera actualizada
        displayRace(horsePositions, numHorses); // Llamar a la función para mostrar la carrera

        // Esperar un poco antes de la siguiente actualización
        sleep(200); // Esperar 200 milisegundos
    }

    // Anunciar el caballo ganador
    for (int i = 0; i < numHorses; i++) { // Iterar sobre cada caballo
        if (horsePositions[i] >= RACE_LENGTH) { // Si el caballo ha llegado a la meta
            cout << "¡El caballo " << i + 1 << " gana!" << endl; // Anunciar al ganador
        }
    }

    delete[] horsePositions; // Liberar la memoria asignada dinámicamente
    return 0; // Terminar el programa
}
