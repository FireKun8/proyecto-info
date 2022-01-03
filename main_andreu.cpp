#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const int NP = 250;


typedef struct tDatos 
{
    int ref;
    int asilo;
    int IDP;
};

typedef tDatos mDatos[NP][NP];


int asignador(string aux)
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
    int i,j;
    mDatos mDatos2016, mDatos2017, mDatos2018, mDatos2019, mDatos2020, mDatos2021;
    
    if (datos.is_open())
    {
        while (getline(datos, line,'\n')) 
        {
            stringstream ss(line);
            getline(ss, aux, ',');
            if (stoi(aux)==2016)
            {
                getline(ss, aux, ',');
                getline(ss, aux, ',');
                i = asignador(aux);
                getline(ss, aux, ',');
                getline(ss, aux, ',');
                j = asignador(aux);
                getline(ss, mDatos2016[i][j].ref, ',');
                getline(ss, mDatos2016[i][j].asilo, ',');
                getline(ss, mDatos2016[i][j].IDP, ',');
                
            }
            
          
        }
        

    
    }

    
}

int main()
{
    leerDatos_ref();

    return 0;
}

