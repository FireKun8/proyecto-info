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
typedef tDatosPobl mDatosPobl[NLOC]; //array refug. (aleix)
typedef tDatosISO mISO[NLOC]; //array ISO

//DEF. SUBRPOGRAMAS------------------------------------------------------------------------------------------
void leerDatosISO(mISO& tabISO);
int asignador(string ISO, const mISO tabISO);
void leerDatosRefug(mDatosRefug& mDatos20XX, const mISO tabISO);
void insertar_ISO(int& i, int& j, const mISO tabISO);
void imprimirRefug(mDatosRefug& mDatos20XX, const mISO tabISO);
void imprimirISO(const mISO tabISO, int x);
int maximoRefug(const mDatosRefug mDatos20XX,const int i, const int any);
void rankingRefug(mDatosRefug& mDatos20XX, const mISO tabISO);
void rankingIDP(mDatosRefug& mDatos20XX, const mISO tabISO, const int any);
bool comprovarISO(string ISO, mISO tabISO);

void leerDatosPobl(mDatosPobl& mDatos, mISO tabISO, string fichero);
void listadorDatos(mDatosPobl mDatos, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void imprimirDatosPobl(vector<tListador>& vLista, int intro);
void percMigrVSPobl(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, vector<string> vDemandado, int sexo, mISO tabISO);

//DEF. SUBPROGRAMAS MENU------------------------------------------------------------------------
void menu_principal(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu1(mDatosPobl mDatos, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void menu2(mDatosPobl mDatos, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado);
void gotoxy(int x, int y);


//MAIN------------------------------------------------------------------------------------------------
int main()
{
    //DECLARACION VARIABLES PRINCIPALES
    mDatosRefug mDatosRefug20XX;
    mDatosPobl mDatosPobl, mDatosMigr;
    mISO tabISO;
    vector<tListador> vLista;
    vector<string> vDemandado;
    vector<int> vDemandado1 = {1, 7, 9, 10, 14};
    leerDatosISO(tabISO);

    leerDatosPobl(mDatosMigr, tabISO, "migraciones.csv");
    leerDatosPobl(mDatosPobl, tabISO, "poblacion.csv");
    leerDatosRefug(mDatosRefug20XX, tabISO);

    //VARIABLES DEL MENU----------------------------
    
    //SWITCH DEL MENU PRINCIPAL--------------------------------------------------------------------
    menu_principal(mDatosPobl, mDatosMigr, mDatosRefug20XX, tabISO, vLista, vDemandado);

    
    //imprimirRefug(mDatosRefug20XX, tabISO);
    

    //listadorDatos(mDatosPobl, tabISO, vLista, vDemandado);
    //imprimirDatosPobl(vLista, 1);
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
    int i,j, aux;
    bool IDP = false;

    i = asignador(vDemandado[0],tabISO);

    cout<<endl<<endl<<" NUMERO DE REFUGIADOS Y SOLICITANTES DE ASILO ORIGINARIOS DE "<<tabISO[i].pais<<" EN FUNCION DEL DESTINO: "<<endl<<endl;
    cout<<"| "<<setw(60)<<left<<"DESTINO"<<"| "<<setw(10)<<left<<"2018"<<"| "<<setw(10)<<left<<"2019"<<"| "<<setw(10)<<left<<"2020"<<"| "<<setw(10)<<left<<"2021"<<"|"<<endl;
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
        cout<<"-";
    }
    cout<<endl;

    if (IDP)
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
void rankingRefug(mDatosRefug& mDatos20XX, const mISO tabISO, vector<string> vDemandado)
{
    int j_max[NA];

    for(int m = 0; m < vDemandado.size(); m++)
    {
        int i = asignador(vDemandado[m],tabISO);

        for (int k=0; k<NA ; k++)
        {
            j_max[k] = maximoRefug(mDatos20XX, i, k);
        }

        cout<<endl<<endl<<"RANKING DE PASIES CON MAS REFUGIADOS PROVENIENTES DE "<<tabISO[i].pais<<endl<<endl;
        cout<<"| "<<setw(6)<<left<<"ANO"<<"| "<<setw(60)<<left<<"PAIS "<<"| "<<setw(11)<<left<<"REFUGIADOS"<<"|"<<endl;
        for(int k = 0; k < 84; k++)
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
        for(int k = 0; k < 84; k++)
        {
            cout<<"-";
        }
        cout<<endl;
    }
}

//Encontrar número de refugiados máximo de un origen dado
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

//Ranking de los 30 paises con más desplazados internos (IDP) en función del año

void rankingIDP(mDatosRefug& mDatos20XX, const mISO tabISO, const int any)
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

    cout<<"LISTA DE LOS 30 PAISES CON MAS DESPLAZADOS INTERNOS (IDP) EN "<<any<<endl<<endl;
    cout<<"| "<<setw(5)<<left<<"RANK"<<"| "<<setw(45)<<left<<"PAIS "<<"| "<<setw(9)<<left<<"IDPs"<<"|"<<endl;
    for(int k = 0; k < 66; k++)
    {
        cout<<"-";
    }
    cout<<endl;

    for (int k=0; k < 30; k++)
    {
        cout<<"| "<<setw(5)<<left<<k+1<<"| "<<setw(45)<<left<<tabISO[paises_orden[k]].pais<<"| "<<setw(9)<<left<<IDPs_orden[k]<<"|"<<endl;
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

void percMigrVSPobl(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr, vector<string> vDemandado, int sexo, mISO tabISO){
    vector<tListador> vListaDemo, vListaMigr;
    cout<<"PORCENTAJES DE MIGRANTES RESPECTO POBLACION TOTAL EN FUNCION DEL PAIS Y DEL ANO"<<endl<<endl;
    cout << "| " << setw(45) << left << "TERRITORIO" << "| " << setw(7) << 1990 << "| " << setw(7) << 1995  << "| " << setw(7) << 2000 << "| " << setw(7) << 2005 << "| " << setw(7) << 2010 << "| " << setw(7) << 2015 << "| " << setw(7) << 2020 <<"| "<< endl;
    for(int k = 0; k < 111; k++)
    {
        cout<<"-";
    }
    cout<<endl;
    listadorDatos(mDatosDemo, tabISO, vListaDemo, vDemandado);
    listadorDatos(mDatosMigr, tabISO, vListaMigr, vDemandado);
    for(int i = 0; i < vListaDemo.size(); i++){
        cout << "| " << setw(45) << left << vListaDemo[i].pais;
        for(int j = 0; j < NANOS; j++){
            float aux =((float(vListaMigr[i].poblTotal[j][sexo])) / (float(vListaDemo[i].poblTotal[j][sexo]) * 1000)) * 100;
            aux = (int)(aux * 100 + .5);
            cout << "| " << setw(6) <<left<< (float)aux / 100 << "%"; 
        }
        cout <<"| "<< endl;
    }
}

//Imprimir datos poblaciones y migraciones
void imprimirDatosPobl(vector<tListador>& vLista, int intro){
    cout << "| " << setw(60) << left << "TERRITORIO" << "| " << setw(10) << "CODIGO" << "| " << setw(12) << 1990 << "| " << setw(12) << 1995  << "| " << setw(12) << 2000 << "| " << setw(12) << 2005 << "| " << setw(12) << 2010 << "| " << setw(12) << 2015 << "| " << setw(12) << 2020 << endl;
    for(int i = 0; i < 179; i++){
        if(i == 0){
            cout << "| ";
        }
        else{
            cout << "-";
        }
    }
    cout << endl;
    for(int i = 0; i < vLista.size(); i++){
        cout << "| " << setw(60) << vLista[i].pais << "| " << setw(10) << vLista[i].ISO; 
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
}

void menu_principal(mDatosPobl mDatosDemo, mDatosPobl mDatosMigr,mDatosRefug mDatosRefugiados, mISO tabISO, vector<tListador>& vLista, vector<string> vDemandado){
    saltomenup:
    
    //Limpieza de vectores
    vLista.clear();
    vDemandado.clear();
    
    system("cls");
    gotoxy(5, 2);cout << "|1| - Consultar datos demograficos de un pais";
    gotoxy(5, 3);cout << "|2| - Consultar datos migratorios de un pais";
    gotoxy(5, 4);cout << "|3| - Listar paises por maximos y minimos de poblacion, migracion y refugiados";
    gotoxy(5, 5);cout << "|4| - Calcular porcentajes de migracion respecto totales";
    gotoxy(5, 6);cout << "|5| - Buscar paises de destino mas frecuente en funcion del pais de origen del refugiado";
    gotoxy(5, 7);cout << "|6| - Estadisticas de tendencias sobre migraciones";
    gotoxy(5, 8);cout << "|7| - Ver la lista de codigos ISO de cada pais";
    gotoxy(5, 9);cout << "|0| - Salir";
    gotoxy(5, 12);cout <<"Elija una opcion";
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
        case '3':
            opcion = ' ';
            while (opcion != '0'){
                //opcion = menu3(aux1);
            }

            break;

        case '4':{
            percMigrVSPobl(mDatosDemo, mDatosMigr, vDemandado = {"ESP", "USA", "PRK"}, 1, tabISO);
            break;
        }
        case '5':

            //menu5();
            
            break;

        case '6':
            //menu6();
            

            break;
        case '7':{
            imprimirISO(tabISO, 5);
            cout << "Para volver al menu principal: ";
            system("pause"); 
            goto saltomenup;
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
            for(int i = 0; i < NLOC; i++){
                vDemandado.push_back(tabISO[i].ISO);
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
            for(int i = 0; i < NLOC; i++){
                vDemandado.push_back(tabISO[i].ISO);
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

        default:{
            system("cls");
            gotoxy(5, 2); cout << "Introduzca una opcion valida";
            gotoxy(5, 4); system("pause"); cout << "Presione una tecla.. para retroceder" << endl;
            goto saltom2;
            break;
        }
    }

}

char menu3(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "LISTAR PAISES POR MAXIMOS Y MINIMOS DE POBLACION, MIGRACION Y REFUGIADOS";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;

}

char menu4(int aux_pais){
    string pais;
    char option; system("cls");
    gotoxy(5, 2); cout << "CALCULAR PORCENTAJES DE MIGRACION RESPECTO TOTALES";
    gotoxy(5, 5); cout << "Sobre que pais sobre el que quieres consultar los datos? (INTRODUCE SU ISO)";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    /*cin >> pais;*/
    option = getche();

    return /*aux_pais*/ option;

}

void menu5(string& pais_origen){
    char option; system("cls");
    gotoxy(5, 2); cout << "BUSCAR PAISES DE DESTINO MAS FRECUENTES EN FUNCION DEL PAIS DE ORIGEN DEL REFUGIADO";
    gotoxy(5, 5); cout << "Introduzca el ISO del pais de origen de los refugiados";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais: ";
    cin >> pais_origen;
}

void menu6(string& pais_origen, string& pais_destino){
    char option; system("cls");
    gotoxy(5, 2); cout << "ESTADISTICAS DE TENDENCIAS SOBRE MIGRACIONES";
    gotoxy(5, 5); cout << "Introduce el ISO del pais de origen y de destino de los refugiados";
    gotoxy(5, 6); cout << "Ejemplo: Afganistan --> AFG";
    gotoxy(5, 8); cout << "Si desea consultar la lista del ISO de cada pais, escriba: ISO";
    gotoxy(5, 10); cout << "Pais de Origen: ";
    cin >> pais_origen;
    gotoxy(5, 12); cout << "Pais de Destino: ";
    cin >> pais_destino;

}