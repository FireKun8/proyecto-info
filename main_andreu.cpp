#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const int NP = 250;

struct tDatos 
{
    int ref;
    int asilo;
    int IDP;
};

typedef tDatos mDatos[NP][NP];
typedef string tPaises[2][NP]; 

void leerDatos_paises(tPaises& tabPaises)
{
    ifstream codi("asign_ISO.csv");
    string line, aux;
    int cont=0;

    if (codi.is_open())
    {
        while (getline(codi, line))
        {
            stringstream ss(line);
            getline (ss, aux, ';');
            getline (ss, tabPaises[0][cont], ';');
            getline (ss, tabPaises[1][cont], ';'); 
            cont++;
        }
    }
}

int asignador(string ISO)
{
    tPaises t;
    for (int j = 0; j <NP; j++)
    {
        if (ISO==t[1][j])
        {
            return j;
        }
    }
}

void rellenar(mDatos& mDatos20XX)
{
    for (int i=0;i<NP; i++)
    {
        for (int j=0;j<NP; j++)
        {
            mDatos20XX[i][j].ref = 0;
            mDatos20XX[i][j].asilo = 0;
            mDatos20XX[i][j].IDP = 0;
        }
    }
}

void leerDatos_ref(mDatos& mDatos2016,mDatos& mDatos2017,mDatos& mDatos2018,mDatos& mDatos2019,mDatos& mDatos2020,mDatos& mDatos2021)
{
    ifstream datos("refugiados.csv");
    string line;
    string aux,any;
    int i, j;
    rellenar(mDatos2016);
    rellenar(mDatos2017);
    rellenar(mDatos2018);
    rellenar(mDatos2019);
    rellenar(mDatos2020);
    rellenar(mDatos2021);
        
    if (datos.is_open())
    {
        while (getline(datos, line,'\n')) 
        {
            stringstream ss(line);
            getline(ss, any, ',');
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            i = asignador(aux);
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            j = asignador(aux);
            
            int any_n = stoi(any);

            switch (any_n)
            {
                case 2016 : 
                {
                    getline(ss, aux, ',');
                    mDatos2016[i][j].ref = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2016[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2016[i][j].IDP = stoi(aux);
                    break;
                }
                case 2017 :
                {
                    getline(ss, aux, ',');
                    mDatos2017[i][j].ref = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2017[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2017[i][j].IDP = stoi(aux);
                    break;
                }
                case 2018 :
                {
                    getline(ss, aux, ',');
                    mDatos2018[i][j].ref = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2018[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2018[i][j].IDP = stoi(aux);
                    break;
                }
                case 2019 :
                {
                    getline(ss, aux, ',');
                    mDatos2019[i][j].ref = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2019[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2019[i][j].IDP = stoi(aux);
                    break;
                }
                case 2020 :
                {
                    getline(ss, aux, ',');
                    mDatos2020[i][j].ref = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2020[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2020[i][j].IDP = stoi(aux);
                    break;
                }
                case 2021 :
                {
                    getline(ss, aux, ',');
                    mDatos2021[i][j].ref = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2021[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2021[i][j].IDP = stoi(aux);
                    break;
                }
               
            }
                        
        }        

    
    }
    
}



void imprimir()
{
    //cout << "| " << setw(50) << left << "TERRITORIO" << "| " << setw(10) << "CODIGO" << "| " << setw(12) << 1990 << "| " << setw(12) << 1995  << "| " << setw(12) << 2000 << "| " << setw(12) << 2005 << "| " << setw(12) << 2010 << "| " << setw(12) << 2015 << "| " << setw(12) << 2020 << endl;
    for(int i = 0; i < 159; i++){
        if(i == 0){
            //cout << "| ";
        }
        else{
            //cout << "-";
        }
    }
    for (int k=0; k <NP; k++)
    {
        //cout<< "| "<< setw(12)<< internal << 
    }
}

int main()
{
    tPaises t;
    leerDatos_paises(t);
    for(int i=0; i <2; i++)
    {
        for(int j = 0; j <NP; j++)
        {
            cout<<"| "<<setw(20)<<internal<<t[i][j];
        }
        cout<<endl;
    }
    
    return 0;
}

