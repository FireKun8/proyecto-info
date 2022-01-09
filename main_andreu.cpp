#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const int NP = 250;

struct tDatos 
{
    int refu[6];
    int asilo[6];
    int IDP[6];
};

typedef tDatos mDatos[NP][NP];
typedef string tPaises[2][NP]; 

void leerDatos_paises(tPaises& tabPaises);
int  asignador(string ISO);
void rellenar(mDatos& mDatos20XX);
void leerDatos_refu(mDatos& mDatos20XX);
void imprimir(mDatos& mDatos20XX);

int main()
{
    cout<<"1"<<endl;
    mDatos mDatos20XX;
    leerDatos_refu(mDatos20XX);
    imprimir(mDatos20XX);
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

int asignador(string ISO)
{
    tPaises t;
    leerDatos_paises(t);
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
            for (int k=0; k<6 ; k++)
            {
            mDatos20XX[i][j].refu[k] = 0;
            mDatos20XX[i][j].asilo[k] = 0;
            mDatos20XX[i][j].IDP[k] = 0;
            }
        }
    }
}

void leerDatos_refu(mDatos& mDatos2016,mDatos& mDatos2017,mDatos& mDatos2018,mDatos& mDatos2019,mDatos& mDatos2020,mDatos& mDatos2021)
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
                    mDatos2016[i][j].refu = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2016[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2016[i][j].IDP = stoi(aux);
                    break;
                }
                case 2017 :
                {
                    getline(ss, aux, ',');
                    mDatos2017[i][j].refu = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2017[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2017[i][j].IDP = stoi(aux);
                    break;
                }
                case 2018 :
                {
                    getline(ss, aux, ',');
                    mDatos2018[i][j].refu = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2018[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2018[i][j].IDP = stoi(aux);
                    break;
                }
                case 2019 :
                {
                    getline(ss, aux, ',');
                    mDatos2019[i][j].refu = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2019[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2019[i][j].IDP = stoi(aux);
                    break;
                }
                case 2020 :
                {
                    getline(ss, aux, ',');
                    mDatos2020[i][j].refu = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2020[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2020[i][j].IDP = stoi(aux);
                    break;
                }
                case 2021 :
                {
                    getline(ss, aux, ',');
                    mDatos2021[i][j].refu = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2021[i][j].asilo = stoi(aux);
                    getline(ss, aux, ',');
                    mDatos2021[i][j].IDP = stoi(aux);
                    break;
                }
               
            }
            getline(ss, aux, ',');
            getline(ss, aux, ',');
            getline(ss, aux, ',');
                        
        }        

    
    }
    
}



void imprimir(mDatos& mDatos2016,mDatos& mDatos2017,mDatos& mDatos2018,mDatos& mDatos2019,mDatos& mDatos2020,mDatos& mDatos2021)
{
    string ISO_origen, ISO_dest;
    cout<<"Inserta el codigo ISO del pais de origen:"<<endl;
    cin>>ISO_origen;
    cout<<"Inserta el codigo ISO del pais de destinacion:"<<endl;
    cin>>ISO_dest;
    
    int i = asignador(ISO_origen);
    int j = asignador(ISO_dest);
    
    tPaises t;
    leerDatos_paises(t);

    if (i==j)
    {   
        cout<<" NUMERO DE DESPLAZADOS INTERNOS EN "<<t[0][i]<<" :"<<endl<<endl;
        cout<<"| "<<setw(10)<<left<<"2016"<<"| "<<setw(10)<<left<<"2017"<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 60; k++)
        {
            cout<<"-";
        }
        cout<<endl<<"| "<<setw(10)<<left<<mDatos2016[i][j].IDP<<"| "<<setw(10)<<left<<mDatos2017[i][j].IDP<<"| "<<setw(10)<<left<<mDatos2018[i][j].IDP<<"| "<<setw(10)<<left<<mDatos2019[i][j].IDP<<"| "<<setw(10)<<left<<mDatos2020[i][j].IDP<<"| "<<setw(10)<<left<<mDatos2021[i][j].IDP<<"| "<<endl;                 
    }

    else 
    {
        cout<<" NUMERO DE refuUGIADOS ORIGINARIOS DE "<<t[0][i]<<" EN "<<t[0][j]<<" :"<<endl<<endl;
        cout<<"| "<<setw(10)<<left<<"2016"<<"| "<<setw(10)<<left<<"2017"<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 60; k++)
        {
            cout<<"-";
        }
        cout<<endl<<"| "<<setw(10)<<left<<mDatos2016[i][j].refu<<"| "<<setw(10)<<left<<mDatos2017[i][j].refu<<"| "<<setw(10)<<left<<mDatos2018[i][j].refu<<"| "<<setw(10)<<left<<mDatos2019[i][j].refu<<"| "<<setw(10)<<left<<mDatos2020[i][j].refu<<"| "<<setw(10)<<left<<mDatos2021[i][j].refu<<"| "<<endl;  
        
        cout<<endl<<endl<<" NUMERO DE SOLICITANTES DE ASILO ORIGINARIOS DE "<<t[0][i]<<" EN "<<t[0][j]<<" :"<<endl<<endl;
        cout<<"| "<<setw(10)<<left<<"2016"<<"| "<<setw(10)<<left<<"2017"<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 60; k++)
        {
            cout<<"-";
        }
        cout<<endl<<"| "<<setw(10)<<left<<mDatos2016[i][j].asilo<<"| "<<setw(10)<<left<<mDatos2017[i][j].asilo<<"| "<<setw(10)<<left<<mDatos2018[i][j].asilo<<"| "<<setw(10)<<left<<mDatos2019[i][j].asilo<<"| "<<setw(10)<<left<<mDatos2020[i][j].asilo<<"| "<<setw(10)<<left<<mDatos2021[i][j].asilo<<"| "<<endl;      
    
    
    }

}



