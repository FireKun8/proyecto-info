#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

char menu_principal();
void menu1();
char menu2(int aux_pais);
char menu3(int aux_pais);
char menu4(int aux_pais);
char menu5(int aux_pais);
char menu6(int aux_pais);
void gotoxy(int x, int y);

int main (){


    char opcion = ' ';
    int aux1;
    while (opcion != '0') {
    opcion = menu_principal();

    switch (opcion){

        case '1':
            opcion = ' ';
            while (opcion != '0'){
                menu1();

            }
            
             break;

        case '2':
            opcion = ' ';
            while (opcion != '0'){
                opcion = menu2(aux1);
            }
            break;

        case '3':
            opcion = ' ';
            while (opcion != '0'){
                opcion = menu3(aux1);
            }

            break;

        case '4':
            opcion = ' ';
            while (opcion != '0'){
                opcion = menu4(aux1);
            }

            break;

        case '5':
            opcion = ' ';
            while (opcion != '0'){
                opcion = menu5(aux1);
            }

            break;

        case '6':
            opcion = ' ';
            while (opcion != '0'){
                opcion = menu6(aux1);
            }

            break;

        case '0':
            gotoxy(5, 2); cout << "Gracias por usar este programa" << endl;
            break;
    
        default:
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para volver al menu principal" << endl;
            break;
    }

    if (opcion != 0) gotoxy(5, 2); cout << "Gracias por usar este programa" << endl;







    }

    return 0;
}


void gotoxy(int x, int y){
HANDLE consola; COORD posicion;
consola = GetStdHandle(STD_OUTPUT_HANDLE);
posicion.X = x; posicion.Y = y;
SetConsoleCursorPosition(consola, posicion);
}



char menu_principal(){
    char option; system("cls");
    gotoxy(5, 2);cout << "|1| - Consultar datos demograficos de un pais";
    gotoxy(5, 3);cout << "|2| - Consultar datos migratorios de un pais";
    gotoxy(5, 4);cout << "|3| - Listar paises por maximos y minimos de poblacion, migracion y refugiados";
    gotoxy(5, 5);cout << "|4| - Calcular porcentajes de migracion respecto totales";
    gotoxy(5, 6);cout << "|5| - Buscar paises de destino mas frecuente en funcion del pais de origen del refugiado";
    gotoxy(5, 7);cout << "|6| - Estadisticas de tendencias sobre migraciones";
    gotoxy(5, 8);cout << "|0| - Salir";
    gotoxy(5, 11);cout <<"Elija una opcion";
    option = getche();
    system("cls");
    return option;
}


    void menu1(){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "DATOS DEMOGRAFICOS";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    cin >> pais;

}

char menu2(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "DATOS MIGRATORIOS";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;

}

char menu3(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "LISTAR PAISES POR MAXIMOS Y MINIMOS DE POBLACION, MIGRACION Y REFUGIADOS";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;

}

char menu4(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "CALCULAR PORCENTAJES DE MIGRACION RESPECTO TOTALES";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;

}

char menu5(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "BUSCAR PAISES DE DESTINO MAS FRECUENTESEN FUNCION DEL PAIS DE ORIGEN DEL REFUGIADO";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;
}

char menu6(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "ESTADISTICAS DE TENDENCIAS SOBRE MIGRACIONES";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;

}