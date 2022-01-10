#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

const int NP = 250;
const int NA = 4;

struct tDatos
{
    int refu[NA] ;
    int IDP[NA] ;
};

typedef tDatos mDatos[NP][NP];
typedef string tPaises[2][NP];

void leerDatos_paises(tPaises& tabPaises);
int  asignador(string ISO, const tPaises t);
void rellenar(mDatos& mDatos20XX);
void leerDatos_refu(mDatos& mDatos20XX, const tPaises t);
void insertar_ISO(int& i, int& j, const tPaises t);
int maximo(const mDatos mDatos20XX,const int i, const int any);
void ranking(mDatos& mDatos20XX, const tPaises t);
void imprimir(mDatos& mDatos20XX, const tPaises t);


int main()
{
    mDatos mDatos20XX;
    tPaises t;
    leerDatos_paises(t);
    rellenar(mDatos20XX);
    leerDatos_refu(mDatos20XX, t);
    imprimir(mDatos20XX, t);
    ranking(mDatos20XX, t);

    return 0;
}

void leerDatos_paises(tPaises& tabPaises)
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
            getline (ss, tabPaises[0][cont], ';');
            getline (ss, tabPaises[1][cont], ';');
            cont++;
        }
    }
}

int asignador(string ISO, const tPaises t)
{
    int asign;
    bool trobat = false;
    for (int j = 0; j <NP && !trobat; j++)
    {
        if (ISO==t[1][j])
        {
            asign = j;
            trobat = true;
        }
    }
    return asign;
}

void rellenar(mDatos& mDatos20XX)
{
    for (int i=0; i<NP ; i++)
    {
        for (int j=0; j<NP ; j++)
        {

            for (int k=0; k<NA ; k++)
            {
                mDatos20XX[i][j].refu[k] = 0;
                mDatos20XX[i][j].IDP[k] = 0;
            }
        }
    }
}

void leerDatos_refu(mDatos& mDatos20XX, const tPaises t)
{
    ifstream datos("refugiados.csv");
    string line;
    string aux,any;
    int i, j;

    if (datos.is_open())
    {
        while (getline(datos, line,'\n'))
        {
            stringstream ss(line);
            getline(ss, any, ',');
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            i = asignador(aux,t);
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            j = asignador(aux,t);

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

void imprimir(mDatos& mDatos20XX, const tPaises t)
{
    int i=252, j=252;

    insertar_ISO(i,j,t);

    if (i==j)
    {
        cout<<endl<<endl<<" NUMERO DE DESPLAZADOS INTERNOS EN "<<t[0][i]<<" :"<<endl<<endl;
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
        cout<<endl<<endl<<" NUMERO DE REFUGIADOS Y SOLICITANTES DE ASILO ORIGINARIOS DE "<<t[0][i]<<" EN "<<t[0][j]<<" :"<<endl<<endl;
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


void insertar_ISO(int& i, int& j, const tPaises t)
{
    string ISO_origen, ISO_dest;

    while(!((i<251 && i>=0) && (j<251 && j>=0)))
    {

        cout<<"Inserta el codigo ISO del pais de origen:"<<endl;
        cin>>ISO_origen;
        cout<<"Inserta el codigo ISO del pais de destinacion:"<<endl;
        cin>>ISO_dest;

        i = asignador(ISO_origen,t);
        j = asignador(ISO_dest,t);

        if (!((i<251 && i>=0) && (j<251 && j>=0)))
        {
            cout<<"**No es una referencia valida. Recuerda usar mayusculas al insertar los codigos ISO.**"<<endl<<endl;
        }
    }
}



void ranking(mDatos& mDatos20XX, const tPaises t)
{
    string ISO_origen, ISO_dest;
    int j_max[NP];
    int i=252, j=252;
    while(!(i<251 && i>=0))
    {
        cout<<"Inserta el codigo ISO del pais de origen:"<<endl;
        cin>>ISO_origen;
        i = asignador(ISO_origen,t);
        if (!(i<251 && i>=0))
        {
            cout<<"**No es una referencia valida. Recuerda usar mayusculas al insertar los codigos ISO.**"<<endl<<endl;
        }
    }
    for (int k=0; k<NA ; k++)
    {
        j_max[k] = maximo(mDatos20XX, i, k);
    }

    cout<<endl<<endl<<"RANKING DE PASIES CON MAS REFUGIADOS PROVENIENTES DE "<<t[0][i]<<endl<<endl;
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
        else cout<<"| "<<setw(6)<<left<<2018+k<<"| "<<setw(60)<<left<<t[0][j_max[k]]<<"| "<<setw(11)<<left<<mDatos20XX[i][j_max[k]].refu[k]<<"|"<<endl;
    }
    for(int k = 0; k < 89; k++)
    {
        cout<<"-";
    }
    cout<<endl;
}

int maximo(const mDatos mDatos20XX,const int i, const int any)
{
    int aux=0, j_maxi=0, cont=0;

    for (int j=0; j<NP ; j++)
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

