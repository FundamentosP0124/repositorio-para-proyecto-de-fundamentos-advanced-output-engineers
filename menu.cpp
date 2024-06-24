#include <iostream>
using namespace std;
int main()
{
    int opcion;

    do
    {
        cout << "Seleccione una opcion:\n";
        cout << "1) Para jugar\n";
        cout << "2) Para ver sus resultados\n";
        cout << "3) Para salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        break;
        case 2:
        break;
        case 3:
        cout << "Saliendo...";
        break;
        default:
        cout << "No existen valor para dichon numero";
        }
    } while (opcion !=3);
    
    return 0;

}