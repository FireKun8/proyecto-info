#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <cmath>
using namespace std;

//CONSTANTES------------------------------------------------------------------------------------------------
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
typedef tDatosPobl mDatosPobl[NLOC]; //array poblacion (aleix)
typedef tDatosISO mISO[NLOC]; //array ISO

//DEF. SUBRPOGRAMAS------------------------------------------------------------------------------------------
void leerDatosISO(mISO& tabISO);
int asignador(string ISO, const mISO tabISO);
void leerDatosRefug(mDatosRefug& mDatos20XX, const mISO tabISO);
void imprimirRefug(mDatosRefug mDatos20XX, const mISO tabISO);
void imprimirISO(const mISO tabISO, int x);
void rankingRefug(mDatosRefug mDatos20XX, const mISO tabISO, vector<string> vDemandado);
void rankingIDP(mDatosRefug mDatos20XX, const mISO tabISO, const int any);
bool comprovarISO(string ISO, mISO tabISO);

void leerDatosPobl(mDatosPobl& mDatos, mISO tabISO, string fichero);
void listadorDatos(mDatosPobl mDatos, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void imprimirDatosPobl(vector<tListador>& vLista, int intro);
void percMigrVSPobl(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, vector<string> vDemandado, int sexo, mISO tabISO);
void percRefugVSMigr(mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, vector<string> vDemandado, mISO tabISO);
void rankingPobl(mDatosPobl mDatosDemo, mISO tabISO, vector<string> vDemandado, int cat, int ano, int tipo);

//DEF. SUBPROGRAMAS MENU------------------------------------------------------------------------
void menu_principal(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu1(mDatosPobl mDatos, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu2(mDatosPobl mDatos, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu3(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu4(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu5(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu6(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu7(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu9(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void gotoxy(int x, int y);
void limpiadorLinea(int posX, int posY, int longitud);


//MAIN------------------------------------------------------------------------------------------------
int main()
{
    //DECLARACION VARIABLES PRINCIPALES
    mDatosRefug mDatosRefug20XX;
    mDatosPobl mDatosPobl, mDatosMigr;
    mISO tabISO;
    vector<tListador> vLista;
    vector<string> vDemandado;

    leerDatosISO(tabISO);
    leerDatosPobl(mDatosMigr, tabISO, "migraciones.csv");
    leerDatosPobl(mDatosPobl, tabISO, "poblacion.csv");
    leerDatosRefug(mDatosRefug20XX, tabISO);

    //VARIABLES DEL MENU----------------------------
    
    //SWITCH DEL MENU PRINCIPAL--------------------------------------------------------------------
    system("cls");
    gotoxy(10, 3); cout << "************************************************";
    gotoxy(10, 4);cout << "*DATOS ONU DE POBLACION, MIGRACION Y REFUGIADOS*";
    gotoxy(10, 5);cout << "************************************************" << endl << endl << endl;
    gotoxy (10, 8); system("Pause");
    system("cls");
    menu_principal(mDatosPobl, mDatosMigr, mDatosRefug20XX, tabISO, vLista, vDemandado);

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
void imprimirRefug(mDatosRefug mDatos20XX, const mISO tabISO, vector<string> vDemandado)
{
    int i,j, aux;
    bool IDP = false;
    i = asignador(vDemandado[0],tabISO);
    j = asignador(vDemandado[1],tabISO);
    
    if (vDemandado.size() == 2 && i == j) 
    {
        IDP = true;
        aux = i;
    }
    
    if (!IDP)
    {
        cout << endl<<endl<<" NUMERO DE REFUGIADOS Y SOLICITANTES DE ASILO ORIGINARIOS DE "<<tabISO[i].pais<<" EN FUNCION DEL DESTINO: "<<endl<<endl;
        cout <<"| "<<setw(60)<<left<<"DESTINO"<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 111; k++)
        {
            cout<<"-";
        }
        cout<<endl;

        for(int m=1; m<vDemandado.size(); m++)
        {
            j = asignador(vDemandado[m],tabISO);
             
            if (i==j)
            {
                aux = j;
                IDP = true;
            }

            else
            {
                cout<<"| "<<setw(60)<<left<<tabISO[j].pais;
                for (int k=0; k < NA; k++)
                {
                    cout<<"| "<<setw(10)<<left<<mDatos20XX[i][j].refu[k];
                }
                cout<<"| "<<endl;
            }
        }
        
        for(int k = 0; k < 111; k++)
        {
            cout << "-";
        }
        cout << endl;
    }
    

    if (IDP)
    {
        cout<<endl<<endl<<"NUMERO DE DESPLAZADOS INTERNOS EN "<<tabISO[i].pais<<" :"<<endl<<endl;
        cout<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
        for(int k = 0; k < 49; k++)
        {
            cout<<"-";
        }
        cout<<endl;
        for (int k=0; k < NA; k++)
        {
            cout<<"| "<<setw(10)<<left<<mDatos20XX[i][aux].IDP[k];
        }
        cout<<"| "<<endl;
    }
}

//Comprovar ISO
bool comprovarISO(string ISO, mISO tabISO){
    bool encontrado = false;
    for(int i = 0; (i < NLOC) && (encontrado == false); i++){
        if(ISO == tabISO[i].ISO || ISO == "---"){
            encontrado = true;
        }
    }
    return encontrado;  
}

//Ranking de paises con más refugiados originarios de un pais dado
void rankingRefug(mDatosRefug mDatos20XX, const mISO tabISO, vector<string> vDemandado)
{
    int aux = 0;
    int j_max[NA];

    for(int m = 0; m < vDemandado.size(); m++)
    {
        int i = asignador(vDemandado[m],tabISO);

        for (int k = 0; k<NA ; k++)
        {
            int aux=0, cont=0;

            for (int j = 0; j < NLOC ; j++)
            {
                if (aux < mDatos20XX[i][j].refu[k])
                {
                    j_max[k] = j;
                    aux = mDatos20XX[i][j].refu[k];
                }
            }
            if (aux == 0) j_max[k] = -1;
            
        }

        gotoxy(5,m*10 + 2); cout<<"RANKING DE PASIES CON MAS REFUGIADOS PROVENIENTES DE "<<tabISO[i].pais;
        gotoxy(5,m*10 + 4); cout<<"| "<<setw(6)<<left<<"ANO"<<"| "<<setw(60)<<left<<"PAIS "<<"| "<<setw(11)<<left<<"REFUGIADOS"<<"|";
        gotoxy(5,m*10 + 5); cout << "|";
        for(int k = 0; k < 82; k++)
        {
            cout<<"-";
        }
        cout << "|";
        for (int k = 0; k < NA; k++)
        {
            if (j_max[k] == -1)
            {
                gotoxy(5,m*10 + k + 6); cout<<"| "<<setw(6)<<left<<2018+k<<"| "<<setw(60)<<left<<"No hay ningun pais con refugiados de este origen"<<"| "<<setw(11)<<left<<"-------"<<"|";
            }
            else gotoxy(5,m*10 + k + 6);  cout<<"| "<<setw(6)<<left<<2018+k<<"| "<<setw(60)<<left<<tabISO[j_max[k]].pais<<"| "<<setw(11)<<left<<mDatos20XX[i][j_max[k]].refu[k]<<"|";
        }
        aux++;
    }
    gotoxy(5,10*aux + 2);
}


//Ranking de los 30 paises con más desplazados internos (IDP) en función del año

void rankingIDP(mDatosRefug mDatos20XX, const mISO tabISO, const int any)
{
    vector<int> IDPs, IDPs_orden;
    vector<int> paises_orden;

    for (int i=0; i<NLOC; i++)
    {
        IDPs.push_back(mDatos20XX[i][i].IDP[any-2018]);
    }

    sort(IDPs.begin(), IDPs.end());

    for (int k = IDPs.size(); k > NLOC-30; k--)
    {
        IDPs_orden.push_back(IDPs[k-1]);
    }

    for(int k = 0; k < IDPs_orden.size(); k++)
    {
        bool encontrado = false;

        for (int i=0; i< NLOC && !encontrado; i++ )
        {
            if(IDPs_orden[k] == mDatos20XX[i][i].IDP[any-2018])
            {
                paises_orden.push_back(i);
                encontrado = true;
            }
        }
    }

    gotoxy(5, 2); cout << "LISTA DE LOS 30 PAISES CON MAS DESPLAZADOS INTERNOS (IDP) EN "<< any;
    gotoxy(5, 4); cout<<"| "<<setw(5)<<left<<"RANK"<<"| "<<setw(45)<<left<<"PAIS "<<"| "<<setw(9)<<left<<"IDPs"<<"|"<<endl;
    gotoxy(5, 5);
    for(int k = 0; k < 66; k++)
    {
        cout<<"-";
    }

    for (int k=0; k < 30; k++)
    {
        gotoxy(5, 6 + k); cout<<"| "<<setw(5)<<left<<k+1<<"| "<<setw(45)<<left<<tabISO[paises_orden[k]].pais<<"| "<<setw(9)<<left<<IDPs_orden[k]<<"|"<<endl;
    }
}

//Imprimir tabla de los codigos ISO para consultar

void imprimirISO(const mISO tabISO, int x)
{
    gotoxy(x,2);cout<< "LISTA DE CODIGOS ISO ORDENADOS ALFABETICAMENTE" <<endl<<endl;
    gotoxy(x,3);for(int k = 0; k < 80; k++)
    {
        cout<<"-";
    }
    cout<<endl;
    gotoxy(x,4);cout<<"| "<<setw(5)<<left<<"ISO"<<"| "<<setw(70)<<left<<"PAIS"<<"| "<<endl;
    gotoxy(x,5);for(int k = 0; k < 80; k++)
    {
        cout<<"-";
    }
    cout<<endl;
    for (int i = 0; i < NLOC; i++)
    {
        gotoxy(x,6+i);cout<<"| "<<setw(5)<<left<<tabISO[i].ISO<<"| "<<setw(70)<<left<<tabISO[i].pais<<"| "<<endl;
    }
    gotoxy(x,6+NLOC);for(int k = 0; k < 80; k++)
    {
        cout<<"-";
    }
    cout<<endl;
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
        bool encontrado1 = false;
        bool encontrado2 = false;
        vLista.push_back(tListador());
        for(int j = 0; j < NLOC && !encontrado1; j++){
            if(vDemandado[i] == mDatos[j].ISO){
                encontrado1 = true;
                for(int k = 0; k < NLOC && !encontrado2; k++){
                    if(mDatos[j].ISO == tabISO[k].ISO){
                        encontrado2 = true;
                        vLista[i].ISO = tabISO[k].ISO;
                        vLista[i].pais = tabISO[k].pais;
                        for(int t = 0; t < NCAT; t++){
                            for(int n = 0; n < NANOS; n++){
                                vLista[i].poblTotal[n][t] = mDatos[j].poblTotal[n][t];
                            }
                        }
                    }
                }
            }
        }
    }
}

void percMigrVSPobl(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, vector<string> vDemandado, int sexo, mISO tabISO){
    int aux = 7;
    vector<tListador> vListaDemo, vListaMigr;
    gotoxy(5,2); cout<<"PORCENTAJES DE MIGRANTES RESPECTO POBLACION TOTAL EN FUNCION DEL PAIS Y DEL ANO";
    gotoxy(5,4); cout << "| " << setw(45) << left << "TERRITORIO" << "| " << setw(7) << 1990 << "| " << setw(7) << 1995  << "| " << setw(7) << 2000 << "| " << setw(7) << 2005 << "| " << setw(7) << 2010 << "| " << setw(7) << 2015 << "| " << setw(7) << 2020 <<"| ";
    gotoxy(5,5); cout << "|";
    for(int k = 0; k < 109; k++)
    {
        cout<<"-";
    }
    cout << "|";
    listadorDatos(mDatosDemo, tabISO, vListaDemo, vDemandado);
    listadorDatos(mDatosMigr, tabISO, vListaMigr, vDemandado);
    for(int i = 0; i < vListaDemo.size(); i++){
        gotoxy(5,6 + i); cout << "| " << setw(45) << left << vListaDemo[i].pais;
        for(int j = 0; j < NANOS; j++){
            float aux =((float(vListaMigr[i].poblTotal[j][sexo])) / (float(vListaDemo[i].poblTotal[j][sexo]) * 1000)) * 100;
            aux = (int)(aux * 100 + .5);
            cout << "| " << setw(6) <<left<< (float)aux / 100 << "%"; 
        }
        cout <<"| ";
        aux++;
    }
    gotoxy(5,aux);
}

void percRefugVSMigr(mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, vector<string> vDemandado, mISO tabISO){
    int aux = 7;
    vector<tListador> vListaMigr;
    gotoxy(5,2); cout << "PORCENTAJES DE REFUGIADOS RESPECTO MIGRACION TOTAL EN FUNCION DEL PAIS EN 2020";
    gotoxy(5,4); cout<< "| " << setw(45) << left << "TERRITORIO" << "| " << setw(12) << "REFUGIADOS" << "| " << setw(12) << "MIGRANTES" << "| " << setw(7) << "%" << "| ";
    gotoxy(5,5); cout << "|";
    for(int k = 0; k < 83; k++)
    {
        cout<<"-";
    }
    cout << "|";
    for (int m = 0; m < vDemandado.size(); m++)
    {
        int j = asignador(vDemandado[m], tabISO);
        int suma_refug = 0;
        listadorDatos(mDatosMigr, tabISO, vListaMigr, vDemandado);

        for (int i = 0; i < NLOC; i++)
        {
            suma_refug += mDatosRefugiados[i][j].refu[2];
        }
        
        float porcent = ((float(suma_refug)) / (float(vListaMigr[m].poblTotal[6][0]))) * 100;
        porcent = (int)(porcent * 100 + .5);

        gotoxy(5,6 + m); cout<< "| " << setw(45) << left << tabISO[j].pais << "| " << setw(12) << suma_refug << "| " << setw(12) << vListaMigr[m].poblTotal[6][0] << "| " << setw(5) << porcent / 100 << " %" <<  "| " ;
        aux++;
    }
    gotoxy(5, aux);
}

void updateDatos(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, int archivo, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){ //1 -> Demografico   2 -> Migragracion   3 -> Refugiados
    if(archivo == 1 || archivo == 2){
        string ISOdemandado;
        char aux;
        int categoria, ano, valor;
        bool encontrado = false;
        system("cls");
        imprimirISO(tabISO, 100);
        if(archivo == 1){
            gotoxy(5,2); cout<<"MODIFICAR DATOS DE POBLACION";
        }
        else if(archivo == 2){
            gotoxy(5,2); cout<<"MODIFICAR DATOS DE MIGRACION";
        }

        gotoxy(5, 5); cout << "Introduzca el ISO del pais a modificar:";
        gotoxy(5, 6); cout << "- ";
        cin >> ISOdemandado;
        while (!comprovarISO(ISOdemandado ,tabISO))
        {
            gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
            gotoxy(5, 6);
            limpiadorLinea(7, 6, ISOdemandado.size() + 1);
            gotoxy(8, 6);
            cin >> ISOdemandado;
        }
        limpiadorLinea(5, 4, 33);
        gotoxy(5, 9); cout << "Categoria del dato a modificar: ";
        gotoxy(5, 10); cout << "|1| - Total    |2| - Masculino    |3| - Femenino";
        gotoxy(5, 11); cout << "Escoja una opcion: ";
        aux = getche();
        while(aux != '1' && aux != '2' && aux != '3'){
            gotoxy(5, 8);cout << "(Introduzca una opcion valida)";
            limpiadorLinea(24, 11, 1);
            gotoxy(24, 11); aux = getche();
        }
        limpiadorLinea(5, 8, 30);
        categoria = aux - 49;
        gotoxy(5, 14); cout << "Ano a modificar: ";
        gotoxy(5, 15); cout << "|1| - 1990    |2| - 1995    |3| - 2000    |4| - 2005";
        gotoxy(5, 16); cout << "|5| - 2010    |6| - 2015    |7| - 2020";
        gotoxy(5, 17); cout << "Escoja una opcion: ";
        aux = getche();
        while(aux < '1' || aux > '7'){
            gotoxy(5, 13);cout << "(Introduzca una opcion valida)";
            limpiadorLinea(24, 17, 1);
            gotoxy(24, 17); aux = getche();
        }
        limpiadorLinea(5, 13, 30);
        ano = aux - 49;
        gotoxy(5, 20); cout << "Inserte el nuevo valor (en forma de entero): ";
        gotoxy(5, 21); cout <<  "- ";
        cin >> valor;
        system("cls");
        gotoxy(5, 2); cout << "DATOS A MODIFICAR: ";
        gotoxy(5, 3); cout << "- Pais: " << ISOdemandado;
        if(categoria == 0){
            gotoxy(5, 4); cout << "- Categoria: "<< "Total";
        }
        else if(categoria == 1){
            gotoxy(5, 4); cout << "- Categoria: "<< "Masculino";
        }
        else if(categoria == 2){
            gotoxy(5, 4); cout << "- Categoria: "<< "Femenino";
        }
        gotoxy(5, 5); cout << "- Ano: "<< 1990 + ano*5;
        gotoxy(5, 6); cout << "- Valor a actualizar: " << valor;

        gotoxy(5, 9); cout << "Esta seguro que desea modificar el valor?";
        gotoxy(5, 10); cout << "|1| - SI    |2| - NO";
        aux = getche();
        limpiadorLinea(25, 10, 1);
        while(aux != '1' && aux != '2'){
            gotoxy(5, 8);cout << "(Introduzca una opcion valida)";
            gotoxy(25, 10);
            aux = getche();
            limpiadorLinea(25, 10, 1);
        }
        if(aux == '1'){
            if(archivo == 1){
                for(int i = 0; i < NLOC && !encontrado; i++){
                    if(mDatosDemo[i].ISO == ISOdemandado){
                        encontrado = true;
                        mDatosDemo[i].poblTotal[ano][categoria] = valor;
                    }
                }
            }
            else if(archivo == 2){
                for(int i = 0; i < NLOC && !encontrado; i++){
                    if(mDatosMigr[i].ISO == ISOdemandado){
                        encontrado = true;
                        mDatosMigr[i].poblTotal[ano][categoria] = valor;
                    }
                }  
            }
            system("cls");
            gotoxy(5,2); cout << "Datos actualizados correctamente." << endl;
            gotoxy(5,3); cout << "Para volver al menu principal: ";
            system("pause");
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
        }
        
        else if(aux == '2'){
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
        }
    }
    
    else if(archivo == 3){
        char aux1, aux2;
        string ISO_origen, ISO_destinacion;
        int ano, valor;
        system("cls");
        gotoxy(5, 2); cout << "Elija el tipo de dato a modificar: ";
        gotoxy(5, 3); cout << "|1| - Refugiados   |2| - Desplazados Internos (IDP) ";
        gotoxy(5, 4); cout << "Escoja una opcion: ";
        aux1 = getche();
        while(aux1 != '1' && aux1 != '2')
        {
            gotoxy(5, 1); cout << "(Introduzca una opcion valida)";
            limpiadorLinea(24, 4, 1);
            gotoxy(24, 4); aux1 = getche();
        }
        limpiadorLinea(5, 1, 30);
        system("cls");
        
        if (aux1 == '1')
        {
            gotoxy(5,2); cout<<"MODIFICAR DATOS DE REFUGIADOS";
            imprimirISO(tabISO, 100);
            gotoxy(5, 5); cout << "Introduzca el ISO del pais de origen:";
            gotoxy(5, 6); cout << "- ";
            cin >> ISO_origen;
            while (!comprovarISO(ISO_origen ,tabISO))
            {
                gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
                gotoxy(5, 6);
                limpiadorLinea(7, 6, ISO_origen.size() + 1);
                gotoxy(5, 6);cout << "- ";
                cin >> ISO_origen;
            }
            limpiadorLinea(5, 4, 33);
            gotoxy(5, 9); cout << "Introduzca el ISO del pais de destino:";
            gotoxy(5, 10); cout << "- ";
            cin >> ISO_destinacion;
            while (!comprovarISO(ISO_destinacion,tabISO))
            {   
                gotoxy(5, 8);cout << "(Introduzca un codigo ISO valido)";
                gotoxy(5, 10);
                limpiadorLinea(7, 10, ISO_destinacion.size() + 1);
                gotoxy(5, 10);cout << "- ";
                cin >> ISO_origen;
            }
            limpiadorLinea(5, 8, 33);
            gotoxy(5, 12); cout << "Escoja el ano del dato a modificar: ";
            gotoxy(5, 13); cout << "|1| - 2018    |2| - 2019    |3| - 2020    |4| - 2021 ";
            gotoxy(5, 14); cout << "Escoja una opcion: ";
            aux2 = getche();
            while(aux2 != '1' && aux2 != '2' && aux2 != '3' && aux2 != '4')
            {
                gotoxy(5, 11); cout << "Introduzca una opcion valida: ";
                limpiadorLinea(24, 14, 1);
                gotoxy(24, 14); aux2 = getche();
            }
            ano = aux2 - 49;
            ano = ano + 2017;
            limpiadorLinea(5, 11, 30);
            int i = asignador(ISO_origen, tabISO);
            int j = asignador(ISO_destinacion, tabISO);
            gotoxy(5, 16); cout << "Inserta el nuevo valor (en forma de entero): ";
            gotoxy(5,17); cout << "- ";
            cin>> valor;
            system("cls");
            gotoxy(5, 2); cout << "DATOS A MODIFICAR: ";
            gotoxy(5, 3); cout << "- Tipo de datos: Refugiados";
            gotoxy(5, 4); cout << "- Pais origen: " << tabISO[i].pais;
            gotoxy(5, 5); cout << "- Pais destino: "<< tabISO[j].pais;
            gotoxy(5, 6); cout << "- Ano: "<< ano;
            gotoxy(5, 7); cout << "- Valor a actualizar: " << valor;

            gotoxy(5,10); cout << "Esta seguro que desea modificar el valor?";
            gotoxy(5, 11); cout << "|1| - SI    |2| - NO";
            aux2 = getche();
            limpiadorLinea(25, 11, 1);
            while(aux2 != '1' && aux2 != '2'){
                gotoxy(5, 9);cout << "(Introduzca una opcion valida) ";
                gotoxy(25, 11);
                aux2 = getche();
                limpiadorLinea(25, 11, 1);
            }
            if(aux2 == '1'){
                mDatosRefugiados[i][j].refu[ano-2018] = valor;
                system("cls");
                gotoxy(5, 2); cout << "Datos actualizados correctamente." << endl;
                gotoxy(5, 3); cout << "Para volver al menu principal: ";
                system("pause");
                menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            }
            else if(aux2 == '2'){
                menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            }
            
        }

        if (aux1 == '2')
        {
            gotoxy(5,2); cout<<"MODIFICAR DATOS DE DESPLAZADOS INTERNOS (IDP)";
            imprimirISO(tabISO, 100);
            gotoxy(5, 5); cout << "Introduzca el ISO del pais:";
            gotoxy(5, 6); cout << "- ";
            cin >> ISO_origen;
            while (!comprovarISO(ISO_origen ,tabISO))
            {
                gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
                gotoxy(5, 6);
                limpiadorLinea(7, 6, ISO_origen.size());
                gotoxy(5, 6);cout << "- ";
                cin >> ISO_origen;
            }
            limpiadorLinea(5, 4, 33);
            int i = asignador(ISO_origen, tabISO);
            gotoxy(5, 9); cout << "Escoja el ano del dato a modificar: ";
            gotoxy(5, 10); cout << "|1| - 2018    |2| - 2019    |3| - 2020    |4| - 2021 ";
            gotoxy(5, 11); cout << "Escoja una opcion: ";
            aux2 = getche();
            while(aux2 != '1' && aux2 != '2' && aux2 != '3' && aux2 != '4')
            {
                gotoxy(5, 8); cout << "(Introduzca una opcion valida)";
                limpiadorLinea(24, 11, 1);
                gotoxy(24, 11); aux2 = getche();
            }
            limpiadorLinea(5, 8, 30);
            ano = aux2 - 48;
            ano = ano + 2017;
            gotoxy(5, 12); cout << "Inserta el nuevo valor (en forma de entero): ";
            gotoxy(5, 13); cout << "- ";
            cin>> valor;
            system("cls");
            gotoxy(5, 2); cout << "DATOS A MODIFICAR: ";
            gotoxy(5, 3); cout << "- Tipo de datos: Desplazados Internos (IDP)";
            gotoxy(5, 4); cout << "- Pais: " << tabISO[i].pais;
            gotoxy(5, 5); cout << "- Ano: "<< ano;
            gotoxy(5, 6); cout << "- Valor a actualizar: " << valor;

            gotoxy(5,10); cout << "Esta seguro que desea modificar el valor?";
            gotoxy(5, 11); cout << "|1| - SI    |2| - NO";
            aux2 = getche();
            limpiadorLinea(25, 11, 1);
            while(aux2 != '1' && aux2 != '2'){
                gotoxy(5, 9);cout << "Introduzca una opcion valida: ";
                gotoxy(25, 11);
                aux2 = getche();
                limpiadorLinea(25, 11, 1);
            }

            if(aux2 == '1'){
                mDatosRefugiados[i][i].IDP[ano-2018] = valor;
                system("cls");
                gotoxy(5, 2); cout << "Datos actualizados correctamente." << endl;
                gotoxy(5, 3); cout << "Para volver al menu principal: ";
                system("pause");
                menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            }
            else if(aux2 == '2'){
                menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            }
        }
    }
}

void rankingPobl(mDatosPobl mDatosDemo, mISO tabISO, vector<string> vDemandado, int cat, int ano, int tipo){
    vector<tListador> vLista;
    vector<int> ranking;
    string sexo[3] = {"TOTAL", "MASCULINA", "FEMENINA"};
    for(int i = 0; i < NLOC; i++){
        ranking.push_back(mDatosDemo[i].poblTotal[ano][cat]);
    }
    sort(ranking.begin(), ranking.end());
    for(int i = ranking.size(); i > ranking.size() - 31; i--){
        bool encontrado = false;
        for(int j = 0; j < NLOC && !encontrado; j++){
            if(ranking[i] == mDatosDemo[j].poblTotal[ano][cat]){
                vDemandado.push_back(mDatosDemo[j].ISO);
                encontrado = true;
            }
        }
    }
    listadorDatos(mDatosDemo, tabISO, vLista, vDemandado);
    if(tipo == 1){
        gotoxy(5, 2); cout << "LISTA DE LOS 30 PAISES CON MAS POBLACION EN " << sexo[cat] << " " << 1990 + 5*ano << " (en miles)";
    }
    if(tipo == 2){
        gotoxy(5, 2); cout << "LISTA DE LOS 30 PAISES CON MAS MIGRACION EN " << sexo[cat] << " " << 1990 + 5*ano;
    }
    gotoxy(5, 4); cout<<"| "<<setw(5)<<left<<"RANK"<<"| "<<setw(59)<<left<<"PAIS "<<"| "<<setw(9)<<left<<"POBL."<<"|"<<endl;
    gotoxy(5, 5); 
    for(int k = 0; k < 80; k++){
        cout<<"-";
    }
    for (int k = 1; k < 31; k++){
        gotoxy(5, 5 + k); cout<<"| "<<setw(5)<<left<<k<<"| "<<setw(59)<<left<<vLista[k].pais<<"| "<<setw(9)<<left<<vLista[k].poblTotal[ano][cat]<<"|"<<endl;
    }
}


//Imprimir datos poblaciones y migraciones
void imprimirDatosPobl(vector<tListador>& vLista, int intro){
    int aux = 0;
    gotoxy(5,2); cout << "| " << setw(60) << left << "TERRITORIO" << "| " << setw(10) << "CODIGO" << "| " << setw(12) << 1990 << "| " << setw(12) << 1995  << "| " << setw(12) << 2000 << "| " << setw(12) << 2005 << "| " << setw(12) << 2010 << "| " << setw(12) << 2015 << "| " << setw(12) << 2020;
    gotoxy(5,3);
    for(int i = 0; i < 171; i++){
        if(i == 0){
            cout << "| ";
        }
        else{
            cout << "-";
        }
    }
    cout << endl;
    for(int i = 0; i < vLista.size(); i++){
        gotoxy(5,4 + i); cout << "| " << setw(60) << vLista[i].pais << "| " << setw(10) << vLista[i].ISO; 
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
        aux = i;
    }
    gotoxy(5, aux + 6);
}

//SUBPROGRAMAS ROBERTO-------------------------------------------------------------------------------------------

void gotoxy(int x, int y){
    HANDLE consola; COORD posicion;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    posicion.X = x; posicion.Y = y;
    SetConsoleCursorPosition(consola, posicion);
}

//Limpiar una linea
void limpiadorLinea(int posX, int posY, int longitud){
    gotoxy(posX, posY);
    for(int i = 0; i < longitud; i++){
        cout << " ";
    }
    gotoxy(posX, posY);
}

void menu_principal(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltomenup:
    
    //Limpieza de vectores
    vLista.clear();
    vDemandado.clear();
    
    system("cls");
    gotoxy(5, 2);cout << "|1| - Consultar datos demograficos de un pais";
    gotoxy(5, 3);cout << "|2| - Consultar datos migratorios de un pais";
    gotoxy(5, 4);cout << "|3| - Consultar TOP 30 datos";
    gotoxy(5, 5);cout << "|4| - Calcular porcentajes de migracion respecto totales";
    gotoxy(5, 6);cout << "|5| - Calcular porcentajes de refugiados respecto migracion";
    gotoxy(5, 7);cout << "|6| - Buscar paises de destino mas frecuente en funcion del pais de origen del refugiado";
    gotoxy(5, 8);cout << "|7| - Estadisticas de tendencias sobre refugiados";
    gotoxy(5, 9);cout << "|8| - Ver la lista de codigos ISO de cada pais";
    gotoxy(5, 10);cout << "|9| - Modificar datos";
    gotoxy(5, 11);cout << "|0| - Salir";
    gotoxy(5, 13);cout <<"Elija una opcion: ";
    char opcion;
    opcion = getche();
    system("cls");
    
    switch (opcion){

        case '1':{
            
            menu1(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            
            break;
        }
        case '2':{
            
            menu2(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);

            break;
        }
        case '3':{
            
            menu3(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);

            break;
        }
        case '4':{

            menu4(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            
            break;
        }
        case '5':{

            menu5(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            
            break;
        }
        case '6':

            menu6(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            
            break;

        case '7':
            
            menu7(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);

            break;
        case '8':{
            imprimirISO(tabISO, 5);
            cout << "Para volver al menu principal: ";
            system("pause"); 
            goto saltomenup;
            break;
        }
        case '9':{
            
            menu9(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            
            break;
        }

        case '0':
            gotoxy(5, 2); cout << "Gracias por usar este programa" << endl;
            break;
    
        default:
            system("cls");
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause");
            goto saltomenup;
            break;
    }
}


void menu1(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltom1:
    char opcion; system("cls");
    gotoxy(5, 2); cout << "DATOS DEMOGRAFICOS";
    gotoxy(5, 5); cout << "|1| - Buscar por codigo ISO";
    gotoxy(5, 6); cout << "|2| - Listar todos los paises";
    gotoxy(5, 7); cout << "(Tenga en cuenta que los datos son expresados en miles)";
    gotoxy(5, 8); cout << "(Si desea volver atras, pulse r)";
    gotoxy(5, 10); cout << "Escoje una opcion:";
    opcion = getche();

    switch(opcion){
        

        case '1':{
            char aux;
            int valor;
            bool aux1 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "|1| - Consultar los datos totales";
                gotoxy(5, 3); cout << "|2| - Consultar los datos sobre los hombres";
                gotoxy(5, 4); cout << "|3| - Consultar los datos sobre las mujeres";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom1;
                valor = aux - 48;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause");
                }
                else{
                    aux1 = true;
                }
            }
            system("cls");
            string ISOdemandado;
            int index = 5;
            imprimirISO(tabISO, 100);
            gotoxy(5, 2); cout << "Introduzca el codigo ISO, en mayusculas, de los paises a consultar";
            gotoxy(5, 3); cout << "(Cuando no quieras introducir mas paises, escribe: ---)";
            while(ISOdemandado != "---"){
                gotoxy(5, index);cout << "- ";
                cin >> ISOdemandado;
                while (!comprovarISO(ISOdemandado ,tabISO))
                {
                    gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
                    gotoxy(7, index);
                    limpiadorLinea(7, index, ISOdemandado.size());
                    gotoxy(5, index);cout << "- ";
                    cin >> ISOdemandado;
                }
                limpiadorLinea(5, 4, 33);
                vDemandado.push_back(ISOdemandado);              
                index++;
            }
            vDemandado.pop_back();
            system("cls");
            listadorDatos(mDatosDemo, tabISO, vLista, vDemandado);
            imprimirDatosPobl(vLista, valor);
            cout << "Para volver al menu principal: ";
            system("pause"); 
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case '2':{
            char aux;
            int valor;
            bool aux1 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "|1| - Consultar los datos totales";
                gotoxy(5, 3); cout << "|2| - Consultar los datos sobre los hombres";
                gotoxy(5, 4); cout << "|3| - Consultar los datos sobre las mujeres";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom1;
                valor = aux - 48;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux1 = true;
                }
            }
            system("cls");
            for(int i = 0; i < 234; i++){
                vDemandado.push_back(mDatosDemo[i].ISO);
            }
            listadorDatos(mDatosDemo, tabISO, vLista, vDemandado);
            imprimirDatosPobl(vLista, valor);
            cout << "Para volver al menu principal: ";
            system("pause");
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        
        case 'r': {
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }

        default:{
            system("cls");
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para retroceder" << endl;
            goto saltom1;
            break;
        }
    }
}

void menu2(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltom2:
    char opcion; system("cls");
    gotoxy(5, 2); cout << "DATOS MIGRATORIOS";
    gotoxy(5, 5); cout << "|1| - Buscar por codigo ISO";
    gotoxy(5, 6); cout << "|2| - Listar todos los paises";
    gotoxy(5, 7); cout << "(Si desea volver atras, pulse r)";
    gotoxy(5, 9); cout << "Escoje una opcion:";
    opcion = getche();

    switch(opcion){
        case '1':{
            char aux;
            int valor;
            bool aux1 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "|1| - Consultar los datos totales";
                gotoxy(5, 3); cout << "|2| - Consultar los datos sobre los hombres";
                gotoxy(5, 4); cout << "|3| - Consultar los datos sobre las mujeres";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                gotoxy(5, 7); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom2;
                valor = aux - 48;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux1 = true;
                }
            }
            system("cls");
            string ISOdemandado;
            int index = 5;
            imprimirISO(tabISO, 100);
            gotoxy(5, 2); cout << "Introduzca el codigo ISO, en mayusculas, de los paises a consultar";
            gotoxy(5, 3); cout << "(Cuando no quieras introducir mas paises, escribe: ---)";
            while(ISOdemandado != "---"){
                gotoxy(5, index);cout << "- ";
                cin >> ISOdemandado;
                while (!comprovarISO(ISOdemandado ,tabISO))
                {
                    gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
                    gotoxy(7, index);
                    limpiadorLinea(7, index, ISOdemandado.size());
                    gotoxy(5, index);cout << "- ";
                    cin >> ISOdemandado;
                }
                limpiadorLinea(5, 4, 33);
                vDemandado.push_back(ISOdemandado);              
                index++;
            }
            vDemandado.pop_back();
            system("cls");
            listadorDatos(mDatosMigr, tabISO, vLista, vDemandado);
            imprimirDatosPobl(vLista, valor);
            cout << "Para volver al menu principal: ";
            system("pause"); 
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case '2':{
            char aux;
            int valor;
            bool aux1 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "|1| - Consultar los datos totales";
                gotoxy(5, 3); cout << "|2| - Consultar los datos sobre los hombres";
                gotoxy(5, 4); cout << "|3| - Consultar los datos sobre las mujeres";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                gotoxy(5, 7); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom2;
                valor = aux - 48;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux1 = true;
                }
            }
            system("cls");
            for(int i = 0; i < 233; i++){
                vDemandado.push_back(mDatosMigr[i].ISO);
            }
            listadorDatos(mDatosMigr, tabISO, vLista, vDemandado);
            imprimirDatosPobl(vLista, valor);
            cout << "Para volver al menu principal: ";
            system("pause");
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        
        case 'r': {
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case 'R':{
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }

        default:{
            system("cls");
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para retroceder" << endl;
            goto saltom2;
            break;
        }
    }

}

void menu3(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltom3:
    char opcion; system("cls");
    gotoxy(5, 2); cout << "RANKINGS DE REFUGIADOS INTERNOS, POBLACION Y MIGRACION";
    gotoxy(5, 5); cout << "|1| - Ranking de paises con mas refugiados internos (IDP's)";
    gotoxy(5, 6); cout << "|2| - Ranking de paises con mas poblacion";
    gotoxy(5, 7); cout << "|3| - Ranking de paises con mas migracion";
    gotoxy(5, 8); cout << "(Si desea volver atras pulse r)";
    gotoxy(5, 10); cout << "Escoja una opcion: ";

    opcion = getche();
    system("cls");

    switch(opcion){
        case '1':{
            char aux;
            int valor;
            bool aux1 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "Elija un ano: ";
                gotoxy(5, 3); cout << "|1| - 2018";
                gotoxy(5, 4); cout << "|2| - 2019";
                gotoxy(5, 5); cout << "|3| - 2020";
                gotoxy(5, 6); cout << "|4| - 2021";
                gotoxy(5, 7); cout << "(Pulse r para retroceder)";
                gotoxy(5, 8); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom3;
                valor = aux - 49;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3' && aux != '4'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux1 = true;
                }
            }
            rankingIDP(mDatosRefugiados, tabISO, 2018 + valor);
            gotoxy(5, 38); cout << "Para volver al menu principal: ";
            system("pause");
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case '2':{
            char aux;
            int valor, valor2;
            bool aux1 = false;
            bool aux2 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "|1| - Consultar los datos totales";
                gotoxy(5, 3); cout << "|2| - Consultar los datos sobre los hombres";
                gotoxy(5, 4); cout << "|3| - Consultar los datos sobre las mujeres";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                gotoxy(5, 7); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom3;
                valor = aux - 49;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux1 = true;
                }
            }
            system("cls");
            while (!aux2){
                system("cls");
                gotoxy(5, 2); cout << "Sobre que ano desea hacer el ranking?";
                gotoxy(5, 3); cout << "|1| - 1990    |2| - 1995    |3| - 2000    |4| - 2005";
                gotoxy(5, 4); cout << "|5| - 2010    |6| - 2015    |7| - 2020";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                gotoxy(5, 7); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom3;
                valor2 = aux - 49;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3' && aux != '4' && aux != '5' && aux != '6' && aux != '7'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux2 = true;
                }
            }
            rankingPobl(mDatosDemo, tabISO, vDemandado, valor, valor2, 1);
            gotoxy(5, 38); cout << "Para volver al menu principal: ";
            system("pause");
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case '3':{
            char aux;
            int valor, valor2;
            bool aux1 = false;
            bool aux2 = false;
            while (!aux1){
                system("cls");
                gotoxy(5, 2); cout << "|1| - Consultar los datos totales";
                gotoxy(5, 3); cout << "|2| - Consultar los datos sobre los hombres";
                gotoxy(5, 4); cout << "|3| - Consultar los datos sobre las mujeres";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                gotoxy(5, 7); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom3;
                valor = aux - 49;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3' && aux != '4' && aux != '5' && aux != '6' && aux != '7'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux1 = true;
                }
            }
            system("cls");
            while (!aux2){
                system("cls");
                gotoxy(5, 2); cout << "Sobre que ano desea hacer el ranking?";
                gotoxy(5, 3); cout << "|1| - 1990    |2| - 1995    |3| - 2000    |4| - 2005";
                gotoxy(5, 4); cout << "|5| - 2010    |6| - 2015    |7| - 2020";
                gotoxy(5, 5); cout << "(Pulse r para retroceder)";
                gotoxy(5, 7); cout << "Escoja una opcion:";
                aux = getche();
                if (aux == 'r' || aux == 'R') goto saltom3;
                valor2 = aux - 49;
                system("cls");
                if (aux != '1' && aux != '2' && aux != '3'){
                    gotoxy(5, 2); cout << "Introduzca una opcion valida";
                    gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para continuar" << endl;
                }
                else{
                    aux2 = true;
                }
            }
            rankingPobl(mDatosMigr, tabISO, vDemandado, valor, valor2, 2);
            gotoxy(5, 38); cout << "Para volver al menu principal: ";
            system("pause");
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case 'r':{
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case 'R':{
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        default:{
            system("cls");
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para retroceder" << endl;
            goto saltom3;
            break;
        }
    }
}

void menu4(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltom4:
    char opcion; system("cls");
    int valor;
    gotoxy(5, 2); cout << "CALCULAR PORCENTAJES DE MIGRACION REPECTO TOTALES";
    gotoxy(5, 5); cout << "|1| - Consultar los datos totales";
    gotoxy(5, 6); cout << "|2| - Consultar los datos sobre los hombres";
    gotoxy(5, 7); cout << "|3| - Consultar los datos sobre las mujeres";
    gotoxy(5, 8); cout << "(Si desea volver atras, pulse r)";
    gotoxy(5, 10); cout << "Escoja una opcion:";
    opcion = getche();
    system("cls");
    if(opcion == 'r' || opcion == 'R'){
        menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
    }
    else if(opcion == '1' || opcion == '2' || opcion == '3'){
        valor = opcion - 49;

        string ISOdemandado;
        int index = 5;
        imprimirISO(tabISO, 100);
        gotoxy(5, 2); cout << "Introduzca el codigo ISO de los paises, en mayuscula, a consultar";
        gotoxy(5, 3); cout << "(Cuando no quieras introducir mas paises, escribe: ---)";
        while(ISOdemandado != "---"){
            gotoxy(5, index);cout << "- ";
            cin >> ISOdemandado;
            while (!comprovarISO(ISOdemandado ,tabISO))
            {
                gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
                gotoxy(7, index);
                limpiadorLinea(7, index, ISOdemandado.size());
                gotoxy(5, index);cout << "- ";
                cin >> ISOdemandado;
            }
            limpiadorLinea(5, 4, 33);
            vDemandado.push_back(ISOdemandado);              
            index++;
        }
        vDemandado.pop_back();
        system("cls");
        percMigrVSPobl(mDatosDemo, mDatosMigr, vDemandado, valor, tabISO);
        cout << "Para volver al menu principal: ";
        system("pause"); 
        menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
    }
    else{
        system("cls");
        gotoxy(5, 2); cout << "Introduzca una opcion valida";
        gotoxy(5, 4); system("pause");
        goto saltom4;
    }
}

void menu5(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    
    string ISOdemandado;
    system("cls");
    imprimirISO(tabISO, 100);
    gotoxy(5, 2); cout << "CALCULAR PORCENTAJE DE REFUGIADOS RESPECTO MIGRACION";
    gotoxy(5, 5); cout << "Introduzca el codigo ISO, en mayusculas, de los paises a consultar";
    gotoxy(5, 6); cout << "(Cuando no quieras introducir mas paises, escribe: ---)";
    int index = 7;
    while(ISOdemandado != "---"){
        gotoxy(5, index);cout << "- ";
        cin >> ISOdemandado;
        while (!comprovarISO(ISOdemandado ,tabISO))
        {
            gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
            gotoxy(7, index);
            limpiadorLinea(7, index, ISOdemandado.size());
            gotoxy(5, index);cout << "- ";
            cin >> ISOdemandado;
        }
        limpiadorLinea(5, 4, 33);
        vDemandado.push_back(ISOdemandado);              
        index++;
    }
    vDemandado.pop_back();
    system("cls");    
    percRefugVSMigr(mDatosMigr, mDatosRefugiados, vDemandado, tabISO);
    cout << "Para volver al menu principal: ";
    system("pause"); 
    menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
}

void menu6(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    
    string ISOdemandado;
    system("cls");
    imprimirISO(tabISO, 100);
    gotoxy(5, 2); cout << "BUSCAR PAISES DE DESTINO MAS FRECUENTES EN FUNCION DEL PAIS DE ORIGEN DEL REFUGIADO";
    gotoxy(5, 5); cout << "Introduzca el codigo ISO, en mayusculas, de los paises a consultar";
    gotoxy(5, 6); cout << "(Cuando no quieras introducir mas paises, escribe: ---)";
    int index = 7;
    while(ISOdemandado != "---"){
        gotoxy(5, index);cout << "- ";
        cin >> ISOdemandado;
        while (!comprovarISO(ISOdemandado ,tabISO))
        {
            gotoxy(5, 4);cout << "(Introduzca un codigo ISO valido)";
            gotoxy(7, index);
            limpiadorLinea(7, index, ISOdemandado.size());
            gotoxy(5, index);cout << "- ";
            cin >> ISOdemandado;
        }
        limpiadorLinea(5, 4, 33);
        vDemandado.push_back(ISOdemandado);              
        index++;
    }
    vDemandado.pop_back();
    system("cls");    
    rankingRefug(mDatosRefugiados, tabISO, vDemandado);
    cout << "Para volver al menu principal: ";
    system("pause"); 
    menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
}
 


void menu7(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    string ISOdemandado;
    system("cls");
    imprimirISO(tabISO, 100);
    char opcion;
    gotoxy(5, 2); cout << "ESTADISTICAS DE TENDENCIAS SOBRE REFUGIADOS";
    gotoxy(5, 3); cout << "Consultar datos de refugiados segun pais de origen y de destino";
    gotoxy(5, 7); cout<< "Introduce el codigo ISO, en mayusculas, del pais de origen: ";
    gotoxy(5, 8); cout << "- ";
    cin >> ISOdemandado; 
    int index = 8;

    while (!comprovarISO(ISOdemandado ,tabISO))
    {
        gotoxy(5, 6);cout << "(Introduzca un codigo ISO valido)";
        gotoxy(7, index);
        limpiadorLinea(7, index, ISOdemandado.size());
        cin >> ISOdemandado;
    }
    vDemandado.push_back(ISOdemandado);

    gotoxy(5, 10); cout << "Introduzca el codigo ISO, en mayusculas, de los paises de destino a consultar";
    gotoxy(5, 11); cout << "(Cuando no quieras introducir mas paises, escribe: ---)";
    index = 12;
    while(ISOdemandado != "---"){
        gotoxy(5, index);cout << "- ";
        cin >> ISOdemandado;
        while (!comprovarISO(ISOdemandado ,tabISO))
        {
            gotoxy(5, 9);cout << "(Introduzca un codigo ISO valido)";
            gotoxy(7, index);
            limpiadorLinea(7, index, ISOdemandado.size());
            gotoxy(5, index);cout << "- ";
            cin >> ISOdemandado;
        }
        limpiadorLinea(5, 9, 33);
        vDemandado.push_back(ISOdemandado);              
        index++;
    }
    vDemandado.pop_back();
    system("cls");    
    imprimirRefug(mDatosRefugiados, tabISO, vDemandado);
    cout << "Para volver al menu principal: ";
    system("pause"); 
    menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
}

void menu9(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltom9:
    char opcion; system("cls");
    gotoxy(5, 2); cout << "MODIFICAR DATOS";
    gotoxy(5, 5); cout << "|1| - Modificar datos sobre poblacion";
    gotoxy(5, 6); cout << "|2| - Modificar datos sobre migracion";
    gotoxy(5, 7); cout << "|3| - Modificar datos sobre refugiados";
    gotoxy(5, 8); cout << "(Si desea volver atras, pulse r)";
    gotoxy(5, 10); cout << "Escoja una opcion:";
    opcion = getche();
    switch (opcion){
        case '1':{
            updateDatos(mDatosDemo, mDatosMigr, mDatosRefugiados, 1, tabISO, vLista, vDemandado);
            break;
        }
        case '2':{
            updateDatos(mDatosDemo, mDatosMigr, mDatosRefugiados, 2, tabISO, vLista, vDemandado);
            break;
        }
        case '3':{
            updateDatos(mDatosDemo, mDatosMigr, mDatosRefugiados, 3, tabISO, vLista, vDemandado);
            break;
        }
        case 'r':{
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        case 'R':{
            menu_principal(mDatosDemo, mDatosMigr, mDatosRefugiados, tabISO, vLista, vDemandado);
            break;
        }
        default:{
            system("cls");
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause");
            goto saltom9;
            break;
        }
    }
}