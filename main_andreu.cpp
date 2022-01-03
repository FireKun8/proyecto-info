#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

void leerDatos_ref()
{
    ifstream datos;
    datos.open("refugiados.csv");

    while (datos.good()) 
    {
        string line;
        getline(datos, line, '\n');
        cout << line <<endl;

    }

}

int main()
{
    leerDatos_ref();
    
    return 0;
}