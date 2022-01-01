#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
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
typedef tLocalizaciones mGestorLoc[NLOC];

void imprimirDatos(mIndex mMigraciones, mGestorLoc mLocalizaciones, int intro);


int main(){
    ifstream datos("migraciones.csv");

    mIndex mMigraciones;
    mGestorLoc mLocalizaciones;

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
            mLocalizaciones[contador].localizacion = aux;
            getline(ss, aux, ',');
            mMigraciones[contador].lCodigo = stoi(aux);
            mLocalizaciones[contador].codigo = stoi(aux);
            for(int i = 0; i < NCAT; i++){
                for(int j = 0; j < NANOS; j++){
                    getline(ss, aux, ',');
                    if(aux != ".."){
                        mMigraciones[contador].poblTotal[j][i] = stoi(aux);
                    }
                    else{
                        mMigraciones[contador].poblTotal[j][i] = -1;
                    }
                }
            }
            contador++;
        }
    }

    imprimirDatos(mMigraciones, mLocalizaciones, 1);
    return 0;
}

void imprimirDatos(mIndex mMigraciones, mGestorLoc mLocalizaciones, int intro){
    cout << setw(45) << left << "TERRITORIO|" << setw(10) << "CODIGO|" << setw(12) << 1990 << "|" << setw(12) << 1995 << "|" << setw(12) << 2000 << "|" << setw(12) << 2005 << "|" << setw(12) << 2010 << "|" << setw(12) << 2015 << "|" << setw(12) << 2020 << "|" << endl;
    for(int i = 0; i < 139; i++){
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < NLOC; i++){
        cout << setw(45) << mLocalizaciones[i].localizacion << setw(10) << mMigraciones[i].lCodigo;
        for(int j = 0; j < NANOS; j++){
            if(intro == 1){
                cout << setw(12) << mMigraciones[i].poblTotal[j][0] << "|";
            }
            if(intro == 2){
                cout << setw(12) << mMigraciones[i].poblTotal[j][1] << "|";
            }
            if(intro == 3){
                cout << setw(12) << mMigraciones[i].poblTotal[j][2] << "|";
            }
        }
        cout << endl;
    } 
}