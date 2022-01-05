#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

int main (){



    return 0;
}

void gotoxy(int x, int y){
HANDLE consola; COORD posicion;
consola = GetStdHandle(STD_OUTPUT_HANDLE);
posicion.X = x; posicion.Y = y;
SetConsoleCursorPosition(consola, posicion);
}

char menu(){
    char opción; system("cls");
    system("cls");
    gotoxy(5, 2);
    cout << "Elija una opción";
    cout << "\n\n 1.- Listar datos demograficos y migratorios de un pais";
    cout << "\n 2.- Listar paises por maximos y minimos de poblacion, migracion y refugiados";
    cout << "\n 3.- Calcular porcentajes de migracion respecto totales";
    cout << "\n 4.- Buscar paises de destino mas frecuente en funcion del pais de origen del refugiado";
    cout << "\n 5.- Estadisticas de tendencias sobre migraciones";
    cout << "\n 0-. Salir";
    opcion = getche();
    system("cls");
    return opción;
}