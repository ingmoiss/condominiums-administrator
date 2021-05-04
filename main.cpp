#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <windows.h>
#include <cstdlib> // Contiene prototipo del exit

int opcionMenu();
void ingresoClientes();//Función para el ingreso de clientes
void generarCobro();//Función para generar cobros mensuales
void consultaPago();//Función para consultar pagos pendiente
void realizarPago();//Función para generar algun pago
void ultimosPen();//Función para mostrar los ultimos 20 pendientes
void ultimosPagos();//Función para mostrar los ultimos 20 pagos realizados

using namespace std;

int main()
{
    int opcion=0;

    do{
        opcion=opcionMenu();

        switch(opcion){
            case 1:
                ingresoClientes();
                system("cls");
                break;

            case 2:
                generarCobro();
                system("cls");
                break;

            case 3:
                consultaPago();
                system("cls");
                break;
            case 4:
                realizarPago();
                break;
                system("cls");
            case 5:
                ultimosPen();
                break;
                system("cls");
            case 6:
                ultimosPagos();
                break;
                system("cls");
        }
    }while(opcion != 7);

    return 0;
}

//Metodo para solicitar al cliente un tramite
int opcionMenu(){
    int opcion=0;

        cout<<"\n\t\t*Bienvenido*\n"<<endl
            <<"\t[1] Ingreso de clientes"<<endl
            <<"\t[2] Generacion de cobro mensual"<<endl
            <<"\t[3] Consulta de pagos pendientes"<<endl
            <<"\t[4] Realizar pago mensual"<<endl
            <<"\t[5] Pagos pendientes"<<endl
            <<"\t[6] Pagos realizados"<<endl
            <<"\t[7] Salir del programa"<<fixed<<showpoint;

    do{
        cout<<"\n\n\tDigite el tramite deseado: ";
        cin>>opcion;
        system("cls");
    }while(opcion < 1 && opcion>7);

}
//Función para ingresar clientes

void ingresoClientes(){
    string opc;
    string nomDueno, numFilial;
    float monto;
    int longitud, valor;

    //Se crea el objeto ingresoFilal el cual contiene el registro de las filiales
    ofstream ingresoFilial;
    ingresoFilial.open("Registro.txt", ios::out|ios::app);

    if(!ingresoFilial){
        cerr<<"Se produjo un error al crear el archivo";
        exit(1);
    }

    do{
        //Algoritmo para validar numero de filial
        do{
            do{
                cout<<"\n\tIngrese los datos que se solicitan"<<endl;

                cout<<"\n\tDigite el numero de filial ##: ";cin>>numFilial;
                longitud=numFilial.size();
                system("cls");
            }while(longitud<0 || longitud>2 || longitud==1);
            valor=atoi(numFilial.c_str());
        }while(valor<0);

        cout<<"\n\tIngrese los datos que se solicitan"<<endl;
        cout<<"\n\tIngrese el nombre del dueño: ";cin>>nomDueno;
        system("cls");

        do{
            cout<<"\n\tIngrese los datos que se solicitan"<<endl;
            cout<<"\n\tIngrese el monto de cobro: ";cin>>monto;
            system("cls");
        }while(monto<=0);

        ingresoFilial<<numFilial<<" "<<nomDueno<<" "<<monto<<endl;
        system("cls");

        cout<<"\n\t**Desea agregar otro cliente**? [S/N]";
        cout<<"\n\t>";cin>>opc;
        system("cls");

    }while(opc == "S" || opc == "s");


    ingresoFilial.close();
}

//Funcion para generar los cobros mensuales
void generarCobro(){
    string mes, ano, nomDueno, numFilial;
    double monto;
    int longitud, mesAux, valor;

    //Se crear el objeto ingreso filial para leer los datos contenidos en el archivo
    ifstream ingresoFilial;
    ofstream cobro;

    ingresoFilial.open("Registro.txt", ios::in);
    cobro.open("Pendientes.txt", ios::out|ios::app);

    if(!ingresoFilial){
        cerr<<"\n**Hubo un error intente de nuevo**"<<endl;
        exit(1);
    }

    if(!cobro){
        cerr<<"No se puedo crear el archivo de cobros"<<endl;
        exit(1);
    }

    //Algoritmo para validar el formato corecto del año
    do{
        do{
            longitud=0;
            cout<<"\n\tDigite el ano YYYY: ";
            cin>>ano;
            system("cls");
            longitud = ano.size();
        }while(longitud<0 || longitud>4 || longitud==2 || longitud==1 || longitud==3);
        valor=atoi(ano.c_str());
    }while(valor<0);

    //Algoritmo para validar formato del mes
    do{
        do{
            longitud=0;
            cout<<"\n\tDigite el mes MM: ";
            cin>>mes;
            system("cls");
            longitud = mes.size();
        }while(longitud<0 ||longitud>2 || longitud==1);
         mesAux=atoi(mes.c_str());
    }while(mesAux<=0||mesAux>12);

    while(ingresoFilial>>numFilial>>nomDueno>>monto){
        cobro<<mes<<" "<<ano<<" "<<numFilial<<" "<<monto<<endl;
    }

        cout<<"\n\t**Se han generado cobros**"<<endl;
        Sleep(500);
    ingresoFilial.close();
    cobro.close();
}

//Función para consultar pagos pendientes por filial
void consultaPago(){
    string mes, ano;
    string numFilial, auxFilial;
    int longitud, valor;
    double monto;

    ifstream cobro;
    cobro.open("Pendientes.txt", ios::in);

    if(!cobro){
        cerr<<"No se pudo realizar el tramite intente de nuevo"<<endl;
        exit(1);
    }

    //Algoritmo para validar el formato del filial
    do{
        do{
            cout<<"\n\tIngrese los datos que se solicita"<<endl;
            cout<<"\n\tDigite el numero de filial ##: ";cin>>auxFilial;
            longitud=auxFilial.size();
        }while(longitud<0 || longitud>2 || longitud==1);
        valor=atoi(auxFilial.c_str());
    }while(valor<0);

    cout<<"\t---------------------------------";
    cout<<"\n\t"<<left<<setw(10)<<"Mes" <<setw(13)
    <<"Año"<<"Monto"<<endl;
    cout<<"\t---------------------------------"<<endl;

    while(cobro>>mes>>ano>>numFilial>>monto){

        if(auxFilial==numFilial){
        cout<<"\t"<<left<<setw(10)<<mes<<setw(13)<<ano
        <<setw(7)<<setprecision(2)<<right<<monto
        <<endl;
        }
    }

    cobro.close();
    system("pause");
}

//Función para realizar el pago segun su numero de filial
void realizarPago(){
    string mes, ano, numFilial;
    string auxMes,auxAno,auxFilial;
    double monto;
    int dia, valor, longitud;

    ifstream cobro;
    ofstream pagos;
    ofstream auxiliar;

    pagos.open("Pagos.txt", ios::out|ios::app);
    cobro.open("Pendientes.txt", ios::in);
    auxiliar.open("Auxiliar.txt", ios::out|ios::app);

    if(!cobro){
        cerr<<"No se encontro el archivo";
        exit(1);
    }

    if(!pagos){
        cerr<<"No se encontro el archivo";
        exit(1);
    }

    //Algoritmo para validar numero de filial
    do{
        do{
            longitud=0;
            cout<<"\n\tIngrese los datos que se solicita"<<endl;

            cout<<"\n\tDigite el la filial ##: ";cin>>auxFilial;
            longitud=auxFilial.size();
            system("cls");
            }while(longitud<0 || longitud>2 || longitud==1);
        valor=atoi(auxFilial.c_str());
    }while(valor<0);

    //Algoritmo para validar el formato correcto de mes
    do{
        do{
            longitud=0;
            cout<<"\n\tIngrese los datos que se solicita"<<endl;

            cout<<"\n\tDigite el mes MM: ";cin>>auxMes;
            longitud=auxMes.size();
            system("cls");
            }while(longitud<0 || longitud>2 || longitud==1);
        valor=atoi(auxMes.c_str());
    }while(valor<0 || valor>12);

    //Algoritmo para validar el formato corecto del año
    do{
        do{
            longitud=0;
            cout<<"\n\tIngrese los datos que se solicita"<<endl;

            cout<<"\n\tDigite el año YYYY: ";cin>>auxAno;
            system("cls");
            longitud = auxAno.size();
        }while(longitud<0 || longitud>4 || longitud==2 || longitud==1 || longitud==3);
        valor=atoi(auxAno.c_str());
    }while(valor<0);

    do{
    cout<<"\n\tDigite el dia a realizar el pago: ";cin>>dia;
    }while(dia<=0);

    while(cobro>>mes>>ano>>numFilial>>monto){

        if(mes==auxMes && ano==auxAno && numFilial==auxFilial){

            if(dia>10){
                monto=monto+(monto*(0.10));
            }
            pagos<<mes<<" "<<ano<<" "<<numFilial<<" "<<monto<<endl;

        }
        else{
            auxiliar<<mes<<" "<<ano<<" "<<numFilial<<" "<<monto<<endl;
        }
    }

    if(dia>10){
        cout<<"\n\t  *Pago realizado con exito*"<<endl
            <<"\n\tSe genero un cargo del 10% al no pagar"
            <<"\n\tantes del dia estimodo.\n"<<endl;
    }
    else{
        cout<<"\n\t*Pago realizado con exito*\n"<<endl;
    }

    pagos.close();
    cobro.close();
    auxiliar.close();

    remove("Pendientes.txt");
    rename("Auxiliar.txt", "Pendientes.txt");

    system("pause");
    system("cls");
}

//Función para mostrar los ultimos pagos pendientes
void ultimosPen(){
    string mes, ano, numFilial;
    double monto;
    int contador,cantidad, linea;

    ifstream cobro;
    cobro.open("Pendientes.txt", ios::in);
    if(!cobro){
        cerr<<"\n\t**No se encontro el archivo**"<<endl;
        exit(1);
    }

    while(cobro>>mes>>ano>>numFilial>>monto){
        contador++;
    }

    cantidad=contador-20;

    cobro.clear();
    cobro.seekg(0);

    cout<<"\n\t    **Ultimos pagos pendientes**\n";

    cout<<"\t--------------------------------------";
    cout<<"\n\t"<<left<<setw(8)<<"Mes" <<setw(10)
    <<"Año"<<setw(15)<<"## Filial"<<"Monto"
    <<endl;
    cout<<"\t--------------------------------------"<<endl;

    while(cobro>>mes>>ano>>numFilial>>monto){

        if(linea>cantidad-1){
        cout<<"\t"<<left<<setw(8)<<mes<<setw(13)<<ano
        <<setw(7)<<numFilial
        <<setw(10)<<setprecision(2)<<right<<monto
        <<endl;
        }

        linea++;
    }

    cobro.close();
    system("pause");
    system("cls");
}

//Función para mostrar los ultimos 20 pagos realizados
void ultimosPagos(){
    string mes, ano, numFilial;
    double monto;
    int contador,cantidad, linea;

    ifstream pagos;
    pagos.open("Pagos.txt", ios::in);
    if(!pagos){
        cerr<<"\n\t**No se encontro el archivo**"<<endl;
        exit(1);
    }


    while(pagos>>mes>>ano>>numFilial>>monto){
        contador++;
    }

    cantidad=contador-20;

    pagos.clear();
    pagos.seekg(0);

    cout<<"\n\t    **Ultimos pagos realizados**\n";

    cout<<"\t--------------------------------------";
    cout<<"\n\t"<<left<<setw(8)<<"Mes" <<setw(10)
    <<"Año"<<setw(15)<<"## Filial"<<"Monto"
    <<endl;
    cout<<"\t--------------------------------------"<<endl;

    while(pagos>>mes>>ano>>numFilial>>monto){

        if(linea>cantidad-1){
        cout<<"\t"<<left<<setw(8)<<mes<<setw(13)<<ano
        <<setw(7)<<numFilial
        <<setw(10)<<setprecision(2)<<right<<monto
        <<endl;
        }

        linea++;
    }

    pagos.close();
    system("pause");
    system("cls");
}



