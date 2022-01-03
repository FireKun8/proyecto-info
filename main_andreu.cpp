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


int asignador(string ISO)
{
    int asign;
    ifstream ISO("asign_ISO.csv");
    string line, ISO1;

    if (asign_ISO.is_open())
    {
        bool trobat = false;
        while (getline(asign, line, '\n')&& !trobat)
        {
            stringstream ss(line);
            getline (ss, asign, ';');
            getline (ss, pais, ';');
            getline (ss, ISO1, ';');
            if (ISO1==ISO)
            {
                trobat=true;
            }
            
        }
        
    }
    return asign;
}

void leerDatos_ref(mDatos& mDatos2016,mDatos& mDatos2017,mDatos& mDatos2018,mDatos& mDatos2019,mDatos& mDatos2020,mDatos& mDatos2021;)
{
    ifstream datos("refugiados.csv");
    string line;
    string aux;
    int i, j, any;
        
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

