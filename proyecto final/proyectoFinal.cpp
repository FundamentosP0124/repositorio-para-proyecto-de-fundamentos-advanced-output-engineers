#include <iostream> // Incluye la biblioteca estándar de entrada y salida
#include <cstdlib>  // Incluye funciones de utilidad general como generación de números aleatorios
#include <ctime>    // Incluye funciones relacionadas con el manejo de tiempo (para srand)
#include <iomanip>  // Incluye herramientas para manipular la salida de datos formateados
#include "colors.h" // Supone un archivo de encabezado personalizado para manejar colores en la consola
#include <limits>   // Incluye definiciones de características de tipos fundamentales, como los límites de los tipos numéricos

using namespace std; // Evita la necesidad de prefijar las funciones de la biblioteca estándar con 'std::'

const int DISTANCIA_CARRERA = 100; // Constante para la longitud de la carrera
const int MAX_PARTICIPANTES = 10;  // Constante para el número máximo de participantes
// Definición de la estructura para almacenar los datos de cada participante
struct participante
{
    string nombre;      // Nombre del participante
    char identificador; // Identificador único para el participante
};
// Funcion para Inscribir jugadores
void inscribirParticipantes(participante participantes[], int& numeroParticipante)
{
    // Permite al usuario inscribir participantes
    cout << "Ingrese el numero de participantes (hasta un maximo de " << MAX_PARTICIPANTES << "): ";
    while (!(cin >> numeroParticipante) || numeroParticipante < 1 || numeroParticipante > MAX_PARTICIPANTES)
    {
        if (cin.fail())
        {
            cin.clear();
            cout << "Entrada invalida. Por favor, ingrese un numero entre 1 y " << MAX_PARTICIPANTES << ": ";
        }
        else
        {
            cout << "El numero debe estar entre 1 y " << MAX_PARTICIPANTES << ". Intente de nuevo: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (int i = 0; i < numeroParticipante; i++)
    {
        cout << "Ingrese el nombre del participante " << i + 1 << ": ";
        cin >> ws;
        getline(cin, participantes[i].nombre);
        cout << "Ingrese un caracter identificativo para " << participantes[i].nombre << ": ";
        cin >> participantes[i].identificador;
    }
    cout << "Participantes inscritos:\n";
    for (int i = 0; i < numeroParticipante; i++)
    {
        cout << "Nombre: " << participantes[i].nombre << ", Identificador: " << participantes[i].identificador << endl;
    }
}
// Función para mostrar la posición de cada participante en la carrera
void posicion(int horsePositions[], participante participantes[], int numCaballos)
{
    for (int i = 0; i < numCaballos; i++)
    {
        for (int j = 0; j < horsePositions[i]; j++)
        {
            cout << "-"; // Imprime un guión por cada unidad de distancia recorrida
        }
        cout << "> ("
                "Caballo de"
             << participantes[i].nombre << ") " << i + 1 << endl; // Muestra el nombre y el número del participante
    }
    cout << endl; // Imprime una línea en blanco después de la salida de todos los participantes
}
// Función para simular una pausa o espera en la ejecución del programa
void esperar(int milliseconds)
{
    clock_t start_time = clock(); // Toma el tiempo de inicio
    while (clock() < start_time + milliseconds)
        ; // Bucle vacío que dura el número de milisegundos especificado
}
// funcion para iniciar la carrera
void jugarCarrera(participante participantes[], int numeroParticipante, int& victoriasUsuario)
{
    if (numeroParticipante == 0)
    {
        cout << "Primero debe inscribir a los participantes.\n"; // Verifica que haya participantes
        inscribirParticipantes(participantes, numeroParticipante);
    }
    int eleccionUsuario;
    cout << "Elija el numero del caballo que cree que va a ganar (1 a " << numeroParticipante << "): ";
    cin >> eleccionUsuario; // Permite al usuario seleccionar un caballo

    int *caballosPosiciones = new int[numeroParticipante](); // Crea un array para las posiciones de los caballos
    bool raceOver = false;
    int caballoGanador = -1;

    while (!raceOver)
    {
#ifdef _WIN32
        system("cls"); // Limpia la pantalla en Windows
#else
        system("clear"); // Limpia la pantalla en otros sistemas operativos
#endif
        for (int i = 0; i < numeroParticipante; i++)
        {
            if (caballosPosiciones[i] < DISTANCIA_CARRERA)
            {
                caballosPosiciones[i] += rand() % 3; // Avanza aleatoriamente cada caballo
            }
            if (caballosPosiciones[i] >= DISTANCIA_CARRERA && caballoGanador == -1)
            {
                caballoGanador = i + 1; // Determina el ganador
                raceOver = true;
            }
        }
        posicion(caballosPosiciones, participantes, numeroParticipante); // Muestra las posiciones actuales
        esperar(200);                                                    // Espera 200 milisegundos antes de actualizar la pantalla
    }
    cout << "El caballo ganador es el numero " << caballoGanador << ". Gana!" << endl;

    if (eleccionUsuario == caballoGanador)
    {
        cout << "Enhorabuena! El caballo seleccionado ha ganado.\n";
        victoriasUsuario++; // Incrementa el contador de victorias del usuario
    }
    else
    {
        cout << "El caballo seleccionado no ha ganado. Suerte para la proxima\n";
    }

    delete[] caballosPosiciones; // Libera la memoria asignada dinámicamente
}
//Funcion Para mostrar los resultados
void mostrarResultados(int victoriasUsuario) {
    cout << (victoriasUsuario == 1 ? "Has ganado 1 vez." : "Has ganado " + to_string(victoriasUsuario) + " veces.") << endl;
}
//funcion para mostrar los nombres del equipo
void mostrarDesarrolladores() {
    cout << left << setw(25) << "\nNombres" << setw(25) << "Apellidos" << setw(25) << "Carnet" << endl;
    cout << setfill('-') << setw(75) << "" << setfill(' ') << endl;
    cout << setw(25) << "Gerson Alejandro" << setw(25) << "Nerio Melgar" << setw(25) << "00132024" << endl;
    cout << setw(25) << "Erick Alejandro" << setw(25) << "Mejicanos Mariona" << setw(25) << "00057324" << endl;
    cout << setw(25) << "Edwin Daniel" << setw(25) << "Leiva Barrera" << setw(25) << "00136124" << endl;
}

int main(){

    srand(time(0));                                           // Inicializa el generador de números aleatorios
    int opcion, numeroParticipante = 0, victoriasUsuario = 0; // Variables para controlar opciones y estado del juego
    participante participantes[MAX_PARTICIPANTES];            // Array para almacenar los participantes

    cout << GRAY << "\n------------------------CARRERA DE CABALLOS----------------------\n"; // titulo
    do
    {
        // Muestra las opciones del menú principal
        cout << GREEN << "\n1) Inscribe los participantes";
        cout << BLUE << "\n2) Para jugar (Antes de jugar debes inscribir participantes)\n";
        cout << ROSE << "3) Para ver sus resultados\n";
        cout << ORANGE << "4) Desarrolladores\n";
        cout << RED << "5) Para salir\n";
        cout << WHITE << "\nSeleccione una opcion: ";
        cin >> opcion; // Lee la opción elegida por el usuario

        // Procesa la opción seleccionada
        switch (opcion)
        {
        case 1:
            inscribirParticipantes(participantes, numeroParticipante); // Llama a la función para inscribir participantes
            break;
        case 2:
            jugarCarrera(participantes, numeroParticipante, victoriasUsuario); // llama a la funcion para iniciar carrera
             break;
        case 3:
            mostrarResultados(victoriasUsuario); // Muestra el número de veces que el usuario ha ganado
            break;
        case 4:
            // Muestra información de los desarrolladores
           mostrarDesarrolladores();
            break;

        case 5:
            // Sale del programa
            cout << "Saliendo..." << endl;
            break;
        default:
            // Gestiona entradas no válidas
            cout << "No existe un valor para dicho numero\n";
            break;
        }
    } while (opcion != 5); // Continúa mostrando el menú hasta que se seleccione la opción de salir

    return 0; // Termina la ejecución del programa
}
