#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;

const int NLOC = 283;
const int NANOS = 7;
const int NCAT = 3;

typedef int mPobl[NANOS][NCAT];

struct tLocalizaciones
{
    int codigo;
    string localizacion;
};

struct tDatos
{
    int lCodigo;
    mPobl poblTotal;
};

typedef tDatos mIndex[NLOC];


int main(){
    ifstream datos("migraciones.txt");

    mIndex mMigraciones;

    string linea;
    int ref, codigo;
    string aux;
    string localizacion;
    int numDatos[3][7];
    int contador = 0;

    if(datos.is_open()){
        while(getline(datos, linea)){
            stringstream ss(linea);
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            mMigraciones[contador].lCodigo = stoi(aux);
            for(int i = 0; i < NCAT; i++){
                for(int j = 0; j < NANOS; j++){
                    getline(ss, aux, ',');
                    mMigraciones[contador].poblTotal[j][i] = stoi(aux);
                }
            }
            contador++;
        }
    }
}