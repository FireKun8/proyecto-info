#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
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

struct tListador
{
    int codigo;
    string localizacion;
    mPobl poblTotal;
};

typedef tDatos mIndex[NLOC];
typedef tLocalizaciones mGestorLoc[NLOC];

void leerDatos(mIndex& mMigraciones, mGestorLoc& mLocalizaciones, vector<int>& vLocPadre);
void listadorDatos(mIndex mMigraciones, mGestorLoc mLocalizaciones, vector<tListador>& vLista, vector<int> vDemandado);
void imprimirDatos(vector<tListador>& vLista, int intro);
void menu(vector<tListador> vLista, vector<int> vDemandado, mIndex mDatos, mGestorLoc mLocalizaciones);


int main(){
    ifstream datos("migraciones.csv");

    mIndex mMigraciones;
    mGestorLoc mLocalizaciones;
    vector<int> vLocPadre;
    vector<tListador> vLista;
    vector<int> vDemandado;

    leerDatos(mMigraciones, mLocalizaciones, vLocPadre);

    menu(vLista, vDemandado, mMigraciones, mLocalizaciones);

    return 0;
}

void leerDatos(mIndex& mMigraciones, mGestorLoc& mLocalizaciones, vector<int>& vLocPadre){
    ifstream datos("migraciones.csv");

    string linea;
    int ref, codigo;
    string aux;
    string localizacion;
    int numDatos[3][7];
    int contador = 0;

    if(datos.is_open()){
        while(getline(datos, linea)){ 
            bool temp = false;
            stringstream ss(linea);
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            mLocalizaciones[contador].localizacion = aux;
            if(aux[2] >= 65 && aux[2] <= 90){
                temp = true;
            }
            getline(ss, aux, ',');
            mMigraciones[contador].lCodigo = stoi(aux);
            if(temp == true){
                vLocPadre.push_back(stoi(aux));
            }
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
}

void listadorDatos(mIndex mMigraciones, mGestorLoc mLocalizaciones, vector<tListador>& vLista, vector<int> vDemandado){
    for(int i = 0; i < vDemandado.size(); i++){
        vLista.push_back(tListador());
        bool encontrado = false;
        int index = 0;
        while(!encontrado){
            if(vDemandado[i] == mLocalizaciones[index].codigo){
                vLista[i].codigo = mLocalizaciones[index].codigo;
                vLista[i].localizacion = mLocalizaciones[index].localizacion;
                encontrado = true;
            }
            index++;
        }
        for(int j = 0; j < NCAT; j++){
            for(int k = 0; k < NANOS; k++){
                vLista[i].poblTotal[k][j] = mMigraciones[i].poblTotal[k][j];
            }
        }
    }
}

void imprimirDatos(vector<tListador>& vLista, int intro){
    cout << "| " << setw(50) << left << "TERRITORIO" << "| " << setw(10) << "CODIGO" << "| " << setw(12) << 1990 << "| " << setw(12) << 1995  << "| " << setw(12) << 2000 << "| " << setw(12) << 2005 << "| " << setw(12) << 2010 << "| " << setw(12) << 2015 << "| " << setw(12) << 2020 << endl;
    for(int i = 0; i < 159; i++){
        if(i == 0){
            cout << "| ";
        }
        else{
            cout << "-";
        }
    }
    cout << endl;
    for(int i = 0; i < vLista.size(); i++){
        cout << "| " << setw(50) << vLista[i].localizacion << "| " << setw(10) << vLista[i].codigo; 
        for(int j = 0; j < NANOS; j++){
            if(intro == 1){
                cout << "| " << setw(12) << vLista[i].poblTotal[j][0];
            }
            if(intro == 2){
                cout << "| " << setw(12) << vLista[i].poblTotal[j][1];
            }
            if(intro == 3){
                cout << "| " << setw(12) << vLista[i].poblTotal[j][2];
            }
        }
        cout << endl;
    }
}

void menu(vector<tListador> vLista, vector<int> vDemandado, mIndex mDatos, mGestorLoc mLocalizaciones){
    cout << "1. Listar todo" << endl;
    cout << "2. Buscar por codigo" << endl;
    cout << "3. Comparar localizaciones" << endl;
    int opcion;
    cin >> opcion;
    system("cls");

    int codigo;

    switch(opcion)
    {
    case 1:
        for(int i = 0; i < NLOC; i++){
            vDemandado.push_back(mDatos[i].lCodigo);
        }
        listadorDatos(mDatos, mLocalizaciones, vLista, vDemandado);
        imprimirDatos(vLista, 1);
        break;
    case 2:
        system("cls");
        cout << "Introducir el codigo de la localizacion a buscar: ";
        cin >> codigo;
        vDemandado.push_back(codigo);
        listadorDatos(mDatos, mLocalizaciones, vLista, vDemandado);
        imprimirDatos(vLista, 1);
        break;
    case 3:
        system("cls");
        cout << "Introducir los codigos de las localizaciones a comparar: " << endl;
        cout << "- ";
        cin >> codigo; 
        while(codigo != -1){
            vDemandado.push_back(codigo);
            cout << "- ";
            cin >> codigo;
        }
        listadorDatos(mDatos, mLocalizaciones, vLista, vDemandado);
        imprimirDatos(vLista, 1);
        break;
    default:
        break;
    }
}