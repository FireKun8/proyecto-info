#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const int NP = 250;
typedef struct mDatos[NP][NP];

mDatos mDatos2016, mDatos2017, mDatos2018, mDatos2019, mDatos2020, mDatos2021;

struct linea 
{
    int any;
    string origen;
    string ISO_or;
    string destino;
    string ISO_dest;
    int refugiados;
    int asilo;
    int IDP;
};


int asignador()
{
    int asign;
    ifstream ISO("asign_ISO.csv");
    string line;
    if (asign_ISO.is_open())
    {

    }
    
}

void leerDatos_ref()
{
    ifstream datos("refugiados.csv");
    string line;
    string aux;
    
    if (datos.is_open())
    {
        while (getline(datos, line,'\n')) 
        {
            stringstream ss(line);
            getline(ss, aux, ',');
            
            getline(datos, line, '\n');
            cout << line <<endl;
        }
        

    
    }

    
}

int main()
{
    leerDatos_ref();

    return 0;
}

