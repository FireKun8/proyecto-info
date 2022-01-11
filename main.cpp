#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

//CONSTANTS------------------------------------------------------------------------------------------------
const int NLOC = 250; //Numero paises
const int NANOS = 7; //Numero años pobl. y migr. (aleix)
const int NCAT = 3; //Numero categorias pobl. y migr. (aleix)
const int NA = 4; //Numero años refug. (andreu)

//DEF. PARA STRUCTS
typedef int mPobl[NANOS][NCAT]; //

//STRUCTS--------------------------------------------------------------------------------------------------
//struct datos ISO
struct tDatosISO
{
    string ISO;
    string pais;
};

//struct datos refug.
struct tDatosRefug
{
    int refu[NA];
    int IDP[NA];
};

//struct datos pobl. y migr.
struct tDatosPobl
{
    string ISO;
    mPobl poblTotal;
};

//struct datos listador
struct tListador
{
    string ISO;
    string pais;
    mPobl poblTotal;
};

//DEF.
typedef tDatosRefug mDatosRefug[NLOC][NLOC]; //matriz refug. (andreu)
typedef tDatosPobl mDatosPobl[NLOC]; //array refug. (aleix)
typedef tDatosISO mISO[NLOC]; //array ISO

//DEF. SUBRPOGRAMAS------------------------------------------------------------------------------------------
void leerDatosISO(mISO& tabISO);
int asignador(string ISO, const mISO tabISO);
void leerDatosRefug(mDatosRefug& mDatos20XX, const mISO tabISO);
void insertar_ISO(int& i, int& j, const mISO tabISO);
void imprimirRefug(mDatosRefug& mDatos20XX, const mISO tabISO);
int maximoRefug(const mDatosRefug mDatos20XX,const int i, const int any);
void rankingRefug(mDatosRefug& mDatos20XX, const mISO tabISO);

void leerDatosPobl(mDatosPobl& mDatos, mISO tabISO, string fichero);
void listadorDatos(mDatosPobl mDatos, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void imprimirDatosPobl(vector<tListador>& vLista, int intro);


//MAIN------------------------------------------------------------------------------------------------
int main()
{
    mDatosRefug mDatosRefug20XX;
    mDatosPobl mDatosPobl, mDatosMigr;
    mISO tabISO;
    vector<tListador> vLista;
    vector<string> vDemandado = {"ESP"};
    leerDatosISO(tabISO);
    
    //leerDatosRefug(mDatosRefug20XX, tabISO);
    //imprimirRefug(mDatosRefug20XX, tabISO);
    
    leerDatosPobl(mDatosMigr, tabISO, "migraciones.csv");
    leerDatosPobl(mDatosPobl, tabISO, "poblacion.csv");
    listadorDatos(mDatosPobl, tabISO, vLista, vDemandado);
    imprimirDatosPobl(vLista, 1);
}

//SUBPROGRAMAS GLOBALES------------------------------------------------------------------------------------------------

//Lector codigo ISO
void leerDatosISO(mISO& tabISO)
{
    ifstream codi("asign_ISO.csv");
    string line, aux;
    int cont=0;

    if (codi.is_open())
    {
        while (getline(codi, line))
        {
            stringstream ss (line);
            getline (ss, aux, ';');
            getline (ss, tabISO[cont].pais, ';');
            getline (ss, tabISO[cont].ISO, ';');
            cont++;
        }
    }
}

//SUBPROGRAMAS ANDREU------------------------------------------------------------------------------------------------

//Asignador ISO
int asignador(string ISO, const mISO tabISO)
{
    int asign;
    bool trobat = false;
    for (int j = 0; j <NLOC && !trobat; j++)
    {
        if (ISO==tabISO[j].ISO)
        {
            asign = j;
            trobat = true;
        }
    }
    return asign;
}

//Leer Datos Refugiados
void leerDatosRefug(mDatosRefug& mDatos20XX, const mISO tabISO)
{
    ifstream datos("refugiados.csv");
    string line;
    string aux,any;
    int i, j;

    for (int i=0; i<NLOC ; i++)
    {
        for (int j=0; j<NLOC ; j++)
        {

            for (int k=0; k<NA ; k++)
            {
                mDatos20XX[i][j].refu[k] = 0;
                mDatos20XX[i][j].IDP[k] = 0;
            }
        }
    }

    if (datos.is_open())
    {
        while (getline(datos, line,'\n'))
        {
            stringstream ss(line);
            getline(ss, any, ',');
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            i = asignador(aux,tabISO);
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            j = asignador(aux,tabISO);

            int any_n = stoi(any);
            int k = any_n-2018;

            getline(ss, aux, ',');
            mDatos20XX[i][j].refu[k] = stoi(aux);
            getline(ss, aux, ',');
            mDatos20XX[i][j].refu[k] += stoi(aux);
            getline(ss, aux, ',');
            mDatos20XX[i][j].IDP[k] = stoi(aux);

            getline(ss, aux, ',');
            getline(ss, aux, ',');
            getline(ss, aux, ',');
        }
    }
}

//Imprimir Datos Refugiados
void imprimirRefug(mDatosRefug& mDatos20XX, const mISO tabISO, vector<string> vDemandado)
{
    int i,j;
    insertar_ISO(i,j,tabISO);

    if (i==j)
    {
        cout<<endl<<endl<<" NUMERO DE DESPLAZADOS INTERNOS EN "<<tabISO[i].pais<<" :"<<endl<<endl;
        cout<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 49; k++)
        {
            cout<<"-";
        }
        cout<<endl;
        for (int k=0; k < NA; k++)
        {
            cout<<"| "<<setw(10)<<left<<mDatos20XX[i][j].IDP[k];
        }
        cout<<"| "<<endl;
    }

    else
    {
        cout<<endl<<endl<<" NUMERO DE REFUGIADOS Y SOLICITANTES DE ASILO ORIGINARIOS DE "<<tabISO[i].pais<<" EN "<<tabISO[j].pais<<" :"<<endl<<endl;
        cout<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 49; k++)
        {
            cout<<"-";
        }
        cout<<endl;
        for (int k=0; k < NA; k++)
        {
            cout<<"| "<<setw(10)<<left<<mDatos20XX[i][j].refu[k];
        }
        cout<<"| "<<endl;
    }

}

//Insertar codigo ISO (cin)
void insertar_ISO(int& i, int& j, const mISO tabISO)
{
    i=252, j=252;
    string ISO_origen, ISO_dest;

    while(!((i<251 && i>=0) && (j<251 && j>=0)))
    {

        cout<<"Inserta el codigo ISO del pais de origen:"<<endl;
        cin>>ISO_origen;
        cout<<"Inserta el codigo ISO del pais de destinacion:"<<endl;
        cin>>ISO_dest;

        i = asignador(ISO_origen,tabISO);
        j = asignador(ISO_dest,tabISO);

        if (!((i<251 && i>=0) && (j<251 && j>=0)))
        {
            cout<<"*!*No es una referencia valida. Recuerda usar mayusculas al insertar los codigos ISO.*!*"<<endl<<endl;
        }
    }
}

//Ranking
void rankingRefug(mDatosRefug& mDatos20XX, const mISO tabISO, vector<string> vDemandado)
{
    for(int m = 0; m < vDemandado.size(); m++)
    {
        string ISO_origen, ISO_dest;
        int j_max[NLOC];
        int i=252, j=252;
        while(!(i<251 && i>=0))
        {
            cout<<"Inserta el codigo ISO del pais de origen:"<<endl;
            cin>>ISO_origen;
            i = asignador(ISO_origen,tabISO);
            if (!(i<251 && i>=0))
            {
                cout<<"*!*No es una referencia valida. Recuerda usar mayusculas al insertar los codigos ISO.*!*"<<endl<<endl;
            }
        }
        
        for (int k=0; k<NA ; k++)
        {
            j_max[k] = maximoRefug(mDatos20XX, i, k);
        }

        cout<<endl<<endl<<"RANKING DE PASIES CON MAS REFUGIADOS PROVENIENTES DE "<<tabISO[i].pais<<endl<<endl;
        cout<<"| "<<setw(6)<<left<<"ANO"<<"| "<<setw(60)<<left<<"PAIS "<<"| "<<setw(11)<<left<<"REFUGIADOS"<<"|"<<endl;
        for(int k = 0; k < 89; k++)
        {
            cout<<"-";
        }
        cout<<endl;
        for (int k=0; k < NA; k++)
        {
            if (j_max[k] == -1)
            {
                cout<<"| "<<setw(6)<<left<<2018+k<<"| "<<setw(60)<<left<<"No hay ningun pais con refugiados de este origen"<<"| "<<setw(11)<<left<<"-------"<<"|"<<endl;
            }
            else cout<<"| "<<setw(6)<<left<<2018+k<<"| "<<setw(60)<<left<<tabISO[j_max[k]].pais<<"| "<<setw(11)<<left<<mDatos20XX[i][j_max[k]].refu[k]<<"|"<<endl;
        }
        for(int k = 0; k < 89; k++)
        {
            cout<<"-";
        }
        cout<<endl;
        }
    }

    

//Encontrar número de refugiados máximo
int maximoRefug(const mDatosRefug mDatos20XX,const int i, const int any)
{
    int aux=0, j_maxi=0, cont=0;

    for (int j=0; j<NLOC ; j++)
    {
        if (aux < mDatos20XX[i][j].refu[any])
        {
            j_maxi = j;
            aux = mDatos20XX[i][j].refu[any];
        }
    }
    if (aux == 0) return -1;
    else return j_maxi;
}

//SUBPROGRAMAS ALEIX-------------------------------------------------------------------------------------------

//Leer datos poblaciones y migraciones
void leerDatosPobl(mDatosPobl& mDatos, mISO tabISO, string fichero){
    ifstream datos(fichero);

    string linea;
    string aux;
    int numDatos[3][7];
    int cont = 0;
    
    if(datos.is_open()){
        while(getline(datos, linea)){
            stringstream ss(linea);
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            mDatos[cont].ISO = aux;
            for(int i = 0; i < NCAT; i++){
                for(int j = 0; j < NANOS; j++){
                    getline(ss, aux, ',');
                    if(aux != ".."){
                        mDatos[cont].poblTotal[j][i] = stoi(aux);
                    }
                    else{
                        mDatos[cont].poblTotal[j][i] = 0;
                    }
                }
            }
            cont++;
        }
    }
}

//Listar datos poblaciones y migraciones
void listadorDatos(mDatosPobl mDatos, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    for(int i = 0; i < vDemandado.size(); i++){
        vLista.push_back(tListador());
        bool encontrado = false;
        int index = 0;
        while(!encontrado){
            if(vDemandado[i] == tabISO[index].ISO){
                vLista[i].ISO = tabISO[index].ISO;
                vLista[i].pais = tabISO[index].pais;
                encontrado = true;
            }
            else if(index == NLOC){
                cout << "ISO no encontrado." << endl;
                encontrado = true;
            }
            index++;
        }
        for(int j = 0; j < NCAT; j++){
            for(int k = 0; k < NANOS; k++){
                vLista[i].poblTotal[k][j] = mDatos[i].poblTotal[k][j];
            }
        }
    }
}

//Imprimir datos poblaciones y migraciones
void imprimirDatosPobl(vector<tListador>& vLista, int intro){
    cout << "| " << setw(20) << left << "TERRITORIO" << "| " << setw(10) << "CODIGO" << "| " << setw(12) << 1990 << "| " << setw(12) << 1995  << "| " << setw(12) << 2000 << "| " << setw(12) << 2005 << "| " << setw(12) << 2010 << "| " << setw(12) << 2015 << "| " << setw(12) << 2020 << endl;
    for(int i = 0; i < 139; i++){
        if(i == 0){
            cout << "| ";
        }
        else{
            cout << "-";
        }
    }
    cout << endl;
    for(int i = 0; i < vLista.size(); i++){
        cout << "| " << setw(20) << vLista[i].pais << "| " << setw(10) << vLista[i].ISO; 
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
