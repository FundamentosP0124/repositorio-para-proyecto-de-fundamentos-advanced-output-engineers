#include <iostream> // Biblioteca para operaciones de entrada/salida
#include <cstdlib>  // Biblioteca para funciones generales como rand() y srand()
#include <ctime>    // Biblioteca para funciones relacionadas con el tiempo como time()

using namespace std; // Usar el espacio de nombres estándar

// Definir la longitud de la carrera
const int DISTANCIA_CARRERA = 100;

// Función para mostrar la posición actual de cada caballo en la consola
void posicion(int horsePositions[], int numCaballos)
{
    for (int i = 0; i < numCaballos; i++)
    { // Iterar sobre cada caballo
        for (int j = 0; j < horsePositions[i]; j++)
        {                // Mostrar la posición del caballo
            cout << "-"; // Mostrar un guion por cada paso del caballo
        }
        cout << "> " << i + 1 << endl; // Mostrar el número del caballo
    }
    cout << endl; // Línea en blanco para separar cada actualización de la carrera
}

// Función para esperar una cantidad específica de milisegundos
void esperar(int milliseconds)
{
    clock_t start_time = clock(); // Registrar el tiempo de inicio
    while (clock() < start_time + milliseconds)
        ; // Esperar hasta que haya transcurrido el tiempo especificado
}

int main()
{
    srand(time(0)); // Inicializar el generador de números aleatorios con la hora actual

    int numCaballos;                           // Variable para almacenar el número de caballos
    cout << "Ingrese el numero de caballos: "; // Solicitar al usuario que ingrese el número de caballos
    cin >> numCaballos;                        // Leer el número de caballos ingresado por el usuario

    int eleccionUsuario;
    cout << "Elija el número del caballo que cree que va a ganar (1 a " << numCaballos << "): ";
    cin >> eleccionUsuario;
    // Crear un arreglo dinámico para almacenar la posición de cada caballo
    int *caballosPosiciciones = new int[numCaballos](); // Inicializar el arreglo con ceros

    bool raceOver = false;   // Variable para determinar si la carrera ha terminado
    int caballoGanador = -1; // Variable para almacenar el número del caballo ganador

    while (!raceOver)
    { // Bucle principal de la carrera
// Limpiar la pantalla
#ifdef _WIN32
        system("cls"); // Limpiar pantalla en Windows
#else
        system("clear"); // Limpiar pantalla en otros sistemas operativos
#endif

        // Actualizar las posiciones de los caballos
        for (int i = 0; i < numCaballos; i++)
        { // Iterar sobre cada caballo
            if (caballosPosiciciones[i] < DISTANCIA_CARRERA)
            {                                          // Si el caballo no ha terminado la carrera
                caballosPosiciciones[i] += rand() % 3; // Movimiento aleatorio: 0, 1, o 2 pasos
            }
            if (caballosPosiciciones[i] >= DISTANCIA_CARRERA && caballoGanador == -1)
            {                           // Si el caballo ha llegado a la meta
                caballoGanador = i + 1; // Almacenar el número del caballo ganador
                raceOver = true;        // Marcar la carrera como terminada
            }
        }

        // Mostrar la carrera actualizada
        posicion(caballosPosiciciones, numCaballos); // Llamar a la función para mostrar la carrera

        // Esperar un poco antes de la siguiente actualización
        esperar(200); // Esperar 200 milisegundos
    }
    // Anuncia el caballo ganador  
    cout << "El caballo ganador es el numero " << caballoGanador << " Gana!" << endl;

    // Verificar si el usuario selecciono el caballo ganador
    if (eleccionUsuario == caballoGanador)
    {
        cout << "Enhorabuena! El caballo seleccionado ha ganado.";
    }
    else
    {
        cout << "El caballo seleccionado no ha ganado. Suerte para la proxima";
    }
    
    delete[] caballosPosiciciones; // Liberar la memoria asignada dinámicamente
    return 0;                      // Terminar el programa
}
