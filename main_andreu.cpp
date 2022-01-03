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
    string any, aux;
    int i,j;
    mDatos mDatos2016, mDatos2017, mDatos2018, mDatos2019, mDatos2020, mDatos2021;
    
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

            swithc (stoi(any))
            {
                case 2016 : 
                {
                    getline(ss, mDatos2016[i][j].ref, ',');
                    getline(ss, mDatos2016[i][j].asilo, ',');
                    getline(ss, mDatos2016[i][j].IDP, ',');
                    break;
                }
                case 2017 :
                {
                    getline(ss, mDatos2017[i][j].ref, ',');
                    getline(ss, mDatos2017[i][j].asilo, ',');
                    getline(ss, mDatos2017[i][j].IDP, ',');
                    break;
                }
                case 2018 :
                {
                    getline(ss, mDatos2018[i][j].ref, ',');
                    getline(ss, mDatos2018[i][j].asilo, ',');
                    getline(ss, mDatos2018[i][j].IDP, ',');
                    break;
                }
                case 2019 :
                {
                    getline(ss, mDatos2019[i][j].ref, ',');
                    getline(ss, mDatos2019[i][j].asilo, ',');
                    getline(ss, mDatos2019[i][j].IDP, ',');
                    break;
                }
                case 2020 :
                {
                    getline(ss, mDatos2020[i][j].ref, ',');
                    getline(ss, mDatos2020[i][j].asilo, ',');
                    getline(ss, mDatos2020[i][j].IDP, ',');
                    break;
                }
                case 2021 :
                {
                    getline(ss, mDatos2021[i][j].ref, ',');
                    getline(ss, mDatos2021[i][j].asilo, ',');
                    getline(ss, mDatos2021[i][j].IDP, ',');
                    break;
                }
                
            }
            
            
          
        }
        

    
    }

    
}

int main()
{
    leerDatos_ref();

    return 0;
}

