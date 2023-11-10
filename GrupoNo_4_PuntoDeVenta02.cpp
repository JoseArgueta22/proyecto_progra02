//***************************************
// Grupo : No 4                         *
// Programa: PUNTO DE VENTA             *
// Integrantes : Carlos Osorio          *
//               Oliver Ruiz            *
//               Jader Chocón           *
//               José Argueta           *
// Fecha  : 01/06/2021                  *
// Universidad Mariano Galvez           *
// Facultad de Ingenieria en Sistemas   *    
//***************************************

#include <time.h>	//funcion srand
#include <iostream>
#include <fstream>	//para los archivos 
#include <windows.h>
#include <stdio.h>
#include <conio.h>   
#include <string>
#include <cstdlib>
#include <vector> 

#define ARR GetAsyncKeyState(VK_UP)		//flecha arriba
#define ABJ GetAsyncKeyState(VK_DOWN)	//flecha abajo
#define ENT 13 	//enter
#define RET 8	//retroceso

using namespace std;

void gotoxy(int x,int y){	//Manejo de coordenadas
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;	dwPos.Y=y;	
	SetConsoleCursorPosition(hcon,dwPos);
}

void OcultarCursor(){		//Oculta el cursor
	CONSOLE_CURSOR_INFO cci={100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Menu();
void Login();

struct User{
	char nombre[25], clave[8];
	int Super, Altas, Cambios, Bajas, Factura;
};
struct User Datos;		//estructura para la creacion de nuevos usuarios y para la lectura de los existentes
struct User Activo;		//estructura para trasladar la informacion del usuario actual

main(){	
	OcultarCursor();
	while(1){
		Login();
	}
}

void Encabezado(){
	system("cls");
 	
	gotoxy(20,0);	cout<<"=============================================";
	gotoxy(23,1);	cout<<"UNIVERSIDAD MARIANO GALVEZ DE GUATEMALA"<<endl;
	gotoxy(25,2);	cout<<"FACULTAD DE INGENIER"<<char(214)<<"A EN SISTEMAS"<<endl;
	gotoxy(26,3);	cout<<"PROGRAMACI"<<char(224)<<"N 1 \"B\" | GRUPO NO. 4"<<endl;
	gotoxy(20,4);	cout<<"=============================================\n\n";
}

void NewUser(bool su){	
	char nomT[25], CTmp[8], CAux[8], caracter, rsi;
	int cont;
	bool coinciden=false;
	
	FILE*registrar;
	registrar=fopen("Usuarios.txt", "a+");
	
	if(registrar){
		do{
			Encabezado();
			memset(Datos.nombre, '\0', sizeof(Datos.nombre));
			memset(Datos.clave, '\0', sizeof(Datos.clave));
			
			if(su){
				Datos.Super=1;
				Datos.Altas=1;
				Datos.Bajas=1;
				Datos.Cambios=1;
				Datos.Factura=1;
				gotoxy(27,6);	cout<<"Configuraci"<<char(162)<<"n de super usuario";
			}	else{
					gotoxy(30,6);	cout<<"Creaci"<<char(162)<<"n de nuevo usuario";
				}
			
			gotoxy(25,8);	cout<<"Nombre de usuario: ";	cin.getline(nomT, 25, '\n');
			gotoxy(25,10);	cout<<"Contrase"<<char(164)<<"a: ";			
			
			fflush(stdin);
			cont=0;
									
			while(caracter=getch()){
				if(caracter==ENT){
					CTmp[cont]='\0';
					break;
				}	else{
						if(caracter!=RET){		
							CTmp[cont]=caracter;			
							cout<<"*";		
							cont++;									
						}	else{
								if(cont>0){
									cout<<"\b \b";
									cont--;
								}
							} 
					}
			}
						
			gotoxy(25,11);	cout<<"Confirme contrase"<<char(164)<<"a: ";	
		
			fflush(stdin);
			cont=0;
			
			while(caracter=getch()){
				if(caracter==ENT){
					CAux[cont]='\0';
					break;
				}	else{
						if(caracter!=RET){		
							CAux[cont]=caracter;			
							cout<<"*";		
							cont++;									
						}	else{
								if(cont>0){
									cout<<"\b \b";
									cont--;
								}
							} 
					}
			}
			
			if(strcmp(CTmp, CAux)==0){	
				if(!su){
					gotoxy(25,13);	cout<<"Es administrador? s/n: ";	
					fflush(stdin);	cin>>rsi;
					if(rsi=='S' || rsi=='s'){
						Datos.Altas=1;
						Datos.Bajas=1;
						Datos.Cambios=1;
						Datos.Factura=1;
					}	else{
							gotoxy(25,14);	cout<<"Acceso al modulo de altas? s/n: ";	
							fflush(stdin);	cin>>rsi;
							if(rsi=='S' || rsi=='s'){
								Datos.Altas=1;
							}	else{
									Datos.Altas=0;
								}
							gotoxy(25,15);	cout<<"Acceso al modulo de bajas? s/n: ";	
							fflush(stdin);	cin>>rsi;
							if(rsi=='S' || rsi=='s'){
								Datos.Bajas=1;
							}	else{
									Datos.Bajas=0;
								}
							gotoxy(25,16);	cout<<"Acceso al modulo de cambios? s/n: ";	
							fflush(stdin);	cin>>rsi;
							if(rsi=='S' || rsi=='s'){
								Datos.Cambios=1;
							}	else{
									Datos.Cambios=0;
								}
							gotoxy(25,17);	cout<<"Acceso al modulo de facturas? s/n: ";	
							fflush(stdin);	cin>>rsi;
							if(rsi=='S' || rsi=='s'){
								Datos.Factura=1;
							}	else{
									Datos.Factura=0;
								}
						}									
					Datos.Super=0;
				}
				strcpy(Datos.nombre, nomT);
				strcpy(Datos.clave, CTmp);			
				fwrite(&Datos, sizeof(User), 1, registrar);
				printf("\033[0;40;32m");
				gotoxy(28,19);	cout<<"Usuario registrado con exito";
				printf("\033[0m");
				gotoxy(20,20);	cout<<"<Presione cualquier tecla para volver al menu>";	getch();
				fclose(registrar);	
				coinciden=true;								
			}	else{
					printf("\033[0;40;31m");
					gotoxy(36,19);	cout<<"No Coinciden!!!";
					printf("\033[0m");	
					Sleep(1200);
					coinciden=false;		
				}	
		}while(!coinciden);		
	}	else{
			exit(1);
		}		
		
	if(su){
		strcpy(Activo.nombre, Datos.nombre);
		strcpy(Activo.clave, Datos.clave);		
		Activo.Super=Datos.Super;
		Activo.Altas=Datos.Altas;
		Activo.Bajas=Datos.Bajas;
		Activo.Cambios=Datos.Cambios;
		Activo.Factura=Datos.Factura;
		
		system("cls");
 		gotoxy(30,10);	cout<<"ACCEDIENDO AL SISTEMA"; 		
 		
 		gotoxy(20,12);	
 		printf("\033[0;40;32m");
		for(int i=0; i<41; i++){
			cout<<char(219);
			Sleep(50);
		}
		printf("\033[0m");
	}
		
	Menu();
}

bool Verif(char nombre[], char clave[]){
	bool Ver=false;
	FILE*usuarios;	
	usuarios=fopen("Usuarios.txt", "r");
	
	if(usuarios){
		fread(&Datos, sizeof(Datos), 1, usuarios);
		while(!feof(usuarios)){								
			if(strcmp(nombre, Datos.nombre)==0 && strcmp(clave, Datos.clave)==0){
				Ver=true;					
				break;
			}	else{
					Ver=false;								
				}			
			fread(&Datos, sizeof(Datos), 1, usuarios);		
		}
			
		fclose(usuarios);
	}	else{
		
		}
	
	return Ver;
}

void Login(){		
	char nom[25], contra[8], caracter;
	int cont, intento=0;
	bool ingresa=false;
	
	FILE*comp;
	comp=fopen("Usuarios.txt", "r");
	if(comp){
		fclose(comp);
	} else{	
		NewUser(1);		
	}
	
	do{		
		Encabezado();
		fflush(stdin);
		
		gotoxy(34, 6);	cout<<"INICIO DE SESI"<<char(224)<<"N";
		gotoxy(32, 8);	cout<<"USUARIO: ";	cin.getline(nom, 25, '\n');
		gotoxy(32, 9);	cout<<"CONTASE"<<char(165)<<"A: ";			
			
		cont=0;	!ENT;	
		while(caracter=getch()){
			if(caracter==ENT){
				contra[cont]='\0';
				break;
			}	else{
					if(caracter!=RET){		
						contra[cont]=caracter;			
						cout<<"*";		
						cont++;									
					}	else{
							if(cont>0){
								cout<<"\b \b";
								cont--;
							}
						} 
				}
		}
		
		if(Verif(nom, contra)){
			ingresa=true;
		}	else{
				intento++;
				if(intento<3){
					printf("\033[0;40;31m");	//secuencia ansi que cambia el color del texto a rojo
					gotoxy(27, 12);	cout<<"Usuario y/o clave incorrectos";	
					printf("\033[0m");	//secuencia ansi que regresa el color del texto al original
					Sleep(1000);
				}	else{
						printf("\033[0;40;31m");
						gotoxy(27, 12);	cout<<"Numero de intentos excedido!!";
						printf("\033[0m");	
						Sleep(1500);
						exit(1);
				}
				ingresa=false;	
			}		
	}while(!ingresa && intento<3);	
					
	if(ingresa){
		strcpy(Activo.nombre, Datos.nombre);
		strcpy(Activo.clave, Datos.clave);		
		Activo.Super=Datos.Super;
		Activo.Altas=Datos.Altas;
		Activo.Bajas=Datos.Bajas;
		Activo.Cambios=Datos.Cambios;
		Activo.Factura=Datos.Factura;
		
		system("cls");
 		gotoxy(30,10);	cout<<"ACCEDIENDO AL SISTEMA"; 		
 		
 		gotoxy(20,12);	
 		printf("\033[0;40;32m");
		for(int i=0; i<41; i++){
			cout<<char(219);
			Sleep(50);
		}
		printf("\033[0m");

		Menu();
	}
}

  //Ingresar datos 
void agregar(ofstream &Es){ 
	Encabezado();
    string nom;
	string dire;
	string muni; 
	string depa;
	string telef;
	string nit;
	string dpi;
	string tel_ofi;
	string pro_v;
	string paten;
	string repre; 
	string contac;
	Es.open("prueba.txt", ios::out | ios::app);
	cout<<"Ingrese los datos que se le solicitan"<<endl; 
	cout<<"Ingrese el nombre"<<endl; 
	cin>>nom;
	cout<<"Ingrese la direccion de residencia"<<endl; 
	cin>>dire; 
	cout<<"Ingrese el Municipio donde reside"<<endl;
	cin>>muni; 
	cout<<"Ingrese el departamento"<<endl;
	cin>>depa;
	cout<<"Ingrese el telefono"<<endl; 
	cin>>telef; 
	cout<<"Ingrese el NIT"<<endl;  
	cin>>nit; 
	cout<<"Ingrese el Documento de Identificacion Personal (DPI)"<<endl; 
	cin>>dpi; 
	cout<<"Ingrese el telefono de Oficina"<<endl; 
	cin>>tel_ofi; 
	cout<<"Ingrese el producto a vender"<<endl; 
	cin>>pro_v;
	cout<<"Ingrese la Patente de Comercio"<<endl; 
	cin>>paten;
	cout<<"Ingrese a su representante legal"<<endl; 
	cin>>repre;
	cout<<"Ingrese contacto de la empresa"<<endl; 
	cin>>contac;
	
	Es<<nom<<" " <<dire<<" "<<muni<<" "<<depa<<" "<<telef<<" "<<nit<<" "<<dpi<<" "<<tel_ofi<<" "<<pro_v<<" "<<paten<<" "<<repre<<" "<<contac<<endl; 
	
	system("cls");
 	gotoxy(30,10);	cout<<"AGREGANDO LOS DATOS"; 		
 		
 	gotoxy(20,12);	
 	printf("\033[0;40;32m");
	for(int i=0; i<41; i++){ //largo linea carga
		cout<<char(219);
		Sleep(50);
	}
	printf("\033[0m");
	Es.close();
	Menu();
}

//Ver Registros
void Verdatos(ifstream &Lec){
	Encabezado();
    string Nom;
	string Dire;
	string Muni; 
	string Depa;
	string Telef;
	string Nit;
	string Dpi;
	string Tel_ofi;
	string Pro_v;
	string Paten;
	string Repre; 
	string Contac;
	Lec.open("prueba.txt", ios::in);
	
	if(Lec.is_open()){ 
		cout<<"Registro de Clientes"<<endl;
		Lec>>Nom; 
		
		while (!Lec.eof()){
	        Lec>>Dire;
			Lec>>Muni;
			Lec>>Depa;
			Lec>>Telef;
			Lec>>Nit;
			Lec>>Dpi;
			Lec>>Tel_ofi;
			Lec>>Pro_v;
			Lec>>Paten;
			Lec>>Repre;
			Lec>>Contac; 
				
			cout<<"Nombre Cliente:"          <<" "<<Nom<<endl;
			cout<<"Direccion de residencia:" <<" "<<Dire<<endl; 
			cout<<"Municipio:"               <<" "<<Muni<<endl;
			cout<<"Departamento:"            <<" "<<Depa<<endl;
			cout<<"Telefono:"               <<" "<<Telef<<endl;
			cout<<"NIT:"                      <<" "<<Nit<<endl;
			cout<<"Documento de Identificaion (DPI):"<<" "<<Dpi<<endl; 
			cout<<"Telefono de la Oficina:"<<" "<<Tel_ofi<<endl;
			cout<<"Producto a vender:"       <<" "<<Pro_v<<endl;
			cout<<"Patente de Comercio:"     <<" "<<Paten<<endl;
			cout<<"Representante Legal:"     <<" "<<Repre<<endl;
			cout<<"Contacto registrado:"    <<" "<<Contac<<endl;	
			cout<<"          "<<endl; 
		    Lec>>Nom; 
		}
	     Lec.close();
	}   
	else
		{cout<<"Se produjo un error vuelva a intentarlo mas tarde"<<endl;}
	
	cout<<"\n<Presione una tecla para volver al menu>";	getch();
	Menu();
}

//Buscar cliente
void buscarcli(ifstream &Lec){
	Encabezado();
	Lec.open("prueba.txt", ios::in);
	bool encontrado = false;
	string nom,dire,muni,depa,telef,nit,dpi,tel_ofi,pro_v,paten,repre,contac,dpiaux,nomaux,direaux,muniaux,depaaux,telefaux,nitaux,tel_ofiaux,pro_vaux,patenaux,repreaux,contacaux;
	int opcion;
	int x,y,i;
	
	cout<<"     BUSQUEDA DE REGISTROS CLIENTES    "<<endl<<endl;
	cout<<"1. BUSCAR POR NOMBRE"<<endl;
	cout<<"2. BUSCAR POR DPI"<<endl;
	cout<<"3. BUSCAR POR TELEFONO"<<endl;
	cout<<"4. BUSCAR POR PRODUCTO"<<endl; 
	cout<<"INGRESE LA OPCION: ";cin>>opcion;
	      
	switch (opcion){
		case 1: // Busqueda por nombre
			cout<<"INGRESE EL NOMBRE: ";cin>>nomaux;
			cout<<"                "<<endl;
			    
			system("cls");
			gotoxy(30,10);	cout<<"BUSCANDO LOS DATOS"; 					 		
			gotoxy(20,12);	
			printf("\033[0;40;32m");
			
			for(int i=0; i<41; i++){ //largo linea carga
				cout<<char(219);
				Sleep(50);
			}
			
			printf("\033[0m");
			Encabezado();
				
			Lec>>nom;
			while(!Lec.eof() && !encontrado){
				Lec>>dire;
				Lec>>muni;
				Lec>>depa;
				Lec>>telef;
				Lec>>nit;
				Lec>>dpi;
				Lec>>tel_ofi;
				Lec>>pro_v;
				Lec>>paten;
				Lec>>repre;
				Lec>>contac;
				
				if(nom==nomaux){
					cout<<"         "<<endl;
					cout<<"NOMBRE:"          <<" "<<nom<<endl;
					cout<<"Direccion:"      <<" "<<dire<<endl;
					cout<<"Municipio:"      <<" "<<muni<<endl;
					cout<<"Departamento:"   <<" "<<depa<<endl;
					cout<<"Telefono:"      <<" "<<telef<<endl;
					cout<<"NIT:"             <<" "<<nit<<endl;
					cout<<"DPI:"             <<" "<<dpi<<endl;
					cout<<"Telefono de oficina:"<<" "<<tel_ofi<<endl;
					cout<<"Producto que vende:"   <<" "<<pro_v<<endl; 
					cout<<"Patente de comercio:"  <<" "<<paten<<endl;
					cout<<"Representante Legal:"  <<" "<<repre<<endl;
					cout<<"Contacto:"            <<" "<<contac<<endl;
					cout<<"                 "<<endl;
					encontrado =true;
				} 
				Lec>>nom;
			}
			break; 
		   
		case 2: //Busqueda por dpi 
			cout<<"INGRESE EL DPI: ";cin>>dpiaux;
			cout<<"                "<<endl;
			   
			system("cls");
			gotoxy(30,10);	cout<<"BUSCANDO LOS DATOS"; 					 		
			gotoxy(20,12);	
			printf("\033[0;40;32m");
			
			for(int i=0; i<41; i++){ //largo linea carga
				cout<<char(219);
				Sleep(50);
			}
			
			printf("\033[0m");
			Encabezado();	
			   
			Lec>>nom;
			while(!Lec.eof() && !encontrado){
				Lec>>dire;
				Lec>>muni;
				Lec>>depa;
				Lec>>telef;
				Lec>>nit;
				Lec>>dpi;
				Lec>>tel_ofi;
				Lec>>pro_v;
				Lec>>paten;
				Lec>>repre;
				Lec>>contac;
				
				if(dpi==dpiaux){
					cout<<"          "<<endl;
					cout<<"NOMBRE:"           <<" "<<nom<<endl;
					cout<<"Direccion:"       <<" "<<dire<<endl;
					cout<<"Municipio:"       <<" "<<muni<<endl;
					cout<<"Departamento:"    <<" "<<depa<<endl;
					cout<<"Telefono:"       <<" "<<telef<<endl;
					cout<<"NIT:"              <<" "<<nit<<endl;
					cout<<"DPI:"              <<" "<<dpi<<endl;
					cout<<"Telefono de oficina:"<<" "<<tel_ofi<<endl;
					cout<<"Producto que vende:"   <<" "<<pro_v<<endl;
					cout<<"Patente de comercio:"  <<" "<<paten<<endl;
					cout<<"Representante Legal:"  <<" "<<repre<<endl;
					cout<<"Contacto:"      <<" "<<contac<<endl;
					cout<<"                 "<<endl;
					encontrado =true;
				} 
				Lec>>nom;
			}
			break;
			
		case 3: //Busqueda por telefono
			cout<<"INGRESE Telefono: ";cin>>telefaux;
			cout<<"                "<<endl;
				
			system("cls");
			gotoxy(30,10);	cout<<"BUSCANDO LOS DATOS"; 					 		
			gotoxy(20,12);	
			printf("\033[0;40;32m");
			
			for(int i=0; i<41; i++){ //largo linea carga
				cout<<char(219);
				Sleep(50);
			}
			
			printf("\033[0m");
			Encabezado();		
				
			Lec>>nom;
			while(!Lec.eof() && !encontrado){  
				Lec>>dire;
				Lec>>muni;
				Lec>>depa;
				Lec>>telef;
				Lec>>nit;
				Lec>>dpi;
				Lec>>tel_ofi;
				Lec>>pro_v;
				Lec>>paten;
				Lec>>repre;
				Lec>>contac; 	
				
				if(telef==telefaux){
					cout<<"          "<<endl;
					cout<<"NOMBRE:"          <<" "<<nom<<endl;
					cout<<"Direccion:"      <<" "<<dire<<endl;
					cout<<"Municipio:"      <<" "<<muni<<endl;
					cout<<"Departamento:"   <<" "<<depa<<endl;
					cout<<"Telefono:"      <<" "<<telef<<endl;
					cout<<"NIT:"             <<" "<<nit<<endl;
					cout<<"DPI:"             <<" "<<dpi<<endl;
					cout<<"Telefono de oficina:"<<" "<<tel_ofi<<endl;
					cout<<"Producto que vende:"   <<" "<<pro_v<<endl;
					cout<<"Patente de comercio:"  <<" "<<paten<<endl;
					cout<<"Representante Legal:"  <<" "<<repre<<endl;
					cout<<"Contacto:"            <<" "<<contac<<endl;
							
					encontrado =true;
				} 
				Lec>>nom;	
			}
			break;
			
		case 4: //Buscar por produccto
			cout<<"INGRESE EL Producto del Cliente: ";cin>>pro_vaux;
			cout<<"                "<<endl;
			
			system("cls");
			gotoxy(30,10);	cout<<"BUSCANDO LOS DATOS"; 					 		
			gotoxy(20,12);	
			printf("\033[0;40;32m");
			
			for(int i=0; i<41; i++){ //largo linea carga
				cout<<char(219);
				Sleep(50);
			}
			
			printf("\033[0m");
			Encabezado();
			
			Lec>>nom;
			while(!Lec.eof() && !encontrado){  
				Lec>>dire;
				Lec>>muni;
				Lec>>depa;
				Lec>>telef;
				Lec>>nit;
				Lec>>dpi;
				Lec>>tel_ofi;
				Lec>>pro_v;
				Lec>>paten;
				Lec>>repre;
				Lec>>contac; 	
				
				if(pro_v==pro_vaux){
					cout<<"          "<<endl;
					cout<<"NOMBRE:"           <<" "<<nom<<endl;
					cout<<"Direccion:"       <<" "<<dire<<endl;
					cout<<"Municipio:"       <<" "<<muni<<endl;
					cout<<"Departamento:"    <<" "<<depa<<endl;
					cout<<"Telefono:"       <<" "<<telef<<endl;
					cout<<"NIT:"              <<" "<<nit<<endl;
					cout<<"DPI:"              <<" "<<dpi<<endl;
					cout<<"Telefono de oficina:"<<" "<<tel_ofi<<endl;
					cout<<"Producto que vende:"   <<" "<<pro_v<<endl;
					cout<<"Patente de comercio:"  <<" "<<paten<<endl;
					cout<<"Representante Legal:"  <<" "<<repre<<endl;
					cout<<"Contacto:"            <<" "<<contac<<endl;
							
					encontrado =true; 
				} 
				Lec>>nom;					 		
			} 									
	}
	Lec.close(); 
	   
	if (!encontrado)
	cout<<"Dato no encontrado, asegure de ingresar correctamento lo solicitado"<<endl;
	
	cout<<"\n<Presione una tecla para volver al menu>";	getch();
	Menu();
}

void vizumod(ifstream &vi){
	Encabezado();
	string Nom;
	string cam; 
	string f_mod;
	vi.open("fecha_mod.txt", ios::in);
	
	if(vi.is_open()){
		system("cls");
		gotoxy(26,10);	cout<<"CARGANDO CLIENTES MODIFICADOS"; 					 		
		gotoxy(16,12);	
		printf("\033[0;40;32m");
					
		for(int i=0; i<45; i++){ //largo linea carga
			cout<<char(219);
			Sleep(50);
		}
					
		printf("\033[0m");
		Encabezado();	    
		cout<<"Registro de Clientes Modificados"<<endl;    
		vi>>Nom; 
		
		while(!vi.eof()){
			vi>>cam; 
			vi>>f_mod; 
				 
			cout<<"Nombre del cliente que fue modificado"<<" "<<Nom<<endl; 
			cout<<"Modificacion realizada"<<" "<<cam<<endl; 
			cout<<"Fecha en la que fue modificado"<<" "<<f_mod<<endl; 
			cout<<"                         "<<endl; 
			vi>>Nom; 
		}
		vi.close();	 
	}	else{
			cout<<"Se ha producido un error"<<endl; 	
		}
	
	cout<<"\n<Presione una tecla para volver al menu>";	getch();
	Menu();	
}

//Modificar registro clientes
void modificarRe(ifstream &Lec){ 
	Encabezado();
	string Nom; 
	string Dire;
	string Muni;
	string Depa;
	string Telef;
	string Nit;
	string Dpi;
	string Tel_ofi;
	string Pro_v;
	string Paten;
	string Repre; 
	string Contac; 
	string dpiaux;
	string nomaux;
	string direaux; 
	string telefaux;
	string pro_vaux; 
	int opcion;
	Lec.open("prueba.txt",ios::in);
	ofstream aux("auxiliar.txt",ios::out);
	
	if(Lec.is_open()){
		cout<<"Ingrese el codigo (DPI): ";  
		cin>>dpiaux; 
		Lec>>Nom; 
				
		cout<<" Registros disponibles ha modificar"<<endl<<endl;  
		cout<<"1.Modificar Nombre"<<endl;
		cout<<"2.Modificar Direccion"<<endl;
		cout<<"3.Modificar Telefono"<<endl;
		cout<<"4.Modificar Producto"<<endl;
				
		cout<<"INGRESE LA OPCION: ";cin>>opcion;
		cout<<"                   "<<endl;
				 
		if(opcion==1){//modificar nombre 
			while(!Lec.eof()){  
				Lec>>Dire;
				Lec>>Muni;
				Lec>>Depa;
				Lec>>Telef;
				Lec>>Nit;
				Lec>>Dpi;
				Lec>>Tel_ofi;
				Lec>>Pro_v;
				Lec>>Paten;
				Lec>>Repre;
				Lec>>Contac;  
				
				if(Dpi==dpiaux){
					cout<<"Ingrese el nombre ha modificar: ";
					cin>>nomaux; 
					
					system("cls");
					gotoxy(26,10);	cout<<"REALIZANDO LOS CAMBIOS"; 					 		
					gotoxy(16,12);	
					printf("\033[0;40;32m");
								
					for(int i=0; i<45; i++){ //largo linea carga
						cout<<char(219);
						Sleep(50);
					}
								
					printf("\033[0m");
					Encabezado();	
					
					aux<<nomaux<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";
					 
				}	else{
						system("pause");
						aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";		
					}
				Lec>>Nom;	
			}
		}
		
		if(opcion==2){ //Modificar direccion 
			while(!Lec.eof()){
				Lec>>Dire;
				Lec>>Muni;
				Lec>>Depa;
				Lec>>Telef;
				Lec>>Nit;
				Lec>>Dpi;
				Lec>>Tel_ofi;
				Lec>>Pro_v;
				Lec>>Paten;
				Lec>>Repre;
				Lec>>Contac;

				if(Dpi==dpiaux){
					cout<<"Ingrese la Direccion ha modificar: "; 
					cin>>direaux;
				
					system("cls");
					gotoxy(26,10);	cout<<"REALIZANDO LOS CAMBIOS"; 					 		
					gotoxy(16,12);	
					printf("\033[0;40;32m");
								
					for(int i=0; i<45; i++){ //largo linea carga
						cout<<char(219);
						Sleep(50);
					}
								
					printf("\033[0m");
					Encabezado();				
							
					aux<<Nom<<" "<<direaux<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";
				}	else{
						system("pause");
						aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";	
					}
				Lec>>Nom;
			}
		} 
		
		if(opcion==3){//Modificar telefono
			while(!Lec.eof()){
				Lec>>Dire;
				Lec>>Muni;
				Lec>>Depa;
				Lec>>Telef;
				Lec>>Nit;
				Lec>>Dpi;
				Lec>>Tel_ofi;
				Lec>>Pro_v;
				Lec>>Paten;
				Lec>>Repre;
				Lec>>Contac;
						
				if(Dpi==dpiaux){
					cout<<"Ingrese el telefono a modificar: ";
					cin>>telefaux;
							
					system("cls");
					gotoxy(26,10);	cout<<"REALIZANDO LOS CAMBIOS"; 					 		
					gotoxy(16,12);	
					printf("\033[0;40;32m");
								
					for(int i=0; i<45; i++){ //largo linea carga
						cout<<char(219);
						Sleep(50);
					}
								
					printf("\033[0m");
					Encabezado();		
								
					aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<telefaux<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";
				}	else{
						system("pause");
						aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";
					}
				Lec>>Nom;
			}
		}
		
		if(opcion==4){//Modificar producto
			while(!Lec.eof()){
				Lec>>Dire;
				Lec>>Muni;
				Lec>>Depa;
			    Lec>>Telef;
			    Lec>>Nit;
				Lec>>Dpi;
				Lec>>Tel_ofi;
				Lec>>Pro_v;
				Lec>>Paten;
				Lec>>Repre;
				Lec>>Contac;	
					
				if(Dpi==dpiaux){
					cout<<"Ingrese el producto a modificar: ";
					cin>>pro_vaux;
							
					system("cls");
					gotoxy(26,10);	cout<<"REALIZANDO LOS CAMBIOS"; 					 		
					gotoxy(16,12);	
					printf("\033[0;40;32m");
								
					for(int i=0; i<45; i++){ //largo linea carga
						cout<<char(219);
						Sleep(50);
					}
								
					printf("\033[0m");
					Encabezado();		
					
					aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<pro_vaux<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";
				}	else{
						system("pause");
						aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<"\n";	
					}
				Lec>>Nom;
			}
		}
		Lec.close();
		aux.close();
	}	else{
			cout<<"VAYA PARECE QUE OCURRIO UN ERROR"<<endl;
		}
	remove("prueba.txt");
	rename("auxiliar.txt","prueba.txt");
}
 
//registrar fecha de modificarcion
void fechamod(ofstream &mo){
	Encabezado();
	string Nom;
	string cam;
	string f_mod;
	mo.open("fecha_mod.txt", ios::out | ios::app);
	
	cout<<"Ingrese el nombre del Cliente Modificado"<<endl;
	cin>>Nom;
	cout<<"Ingrese la modificacion realizada"<<endl;
	cin>>cam;
	cout<<"Ingrese la fecha de modificacion"<<endl; 
	cin>>f_mod; 
	
	mo<<Nom<<" "<<cam<<" "<<f_mod <<endl;
	mo.close(); 
	
	cout<<"\n<Presione una tecla para volver al menu>";	getch();
	Menu();
}  

//ver bajas clientes 
void Verbajas(ifstream &ve){
	Encabezado();
	string Nom;
	string Pro_v; 
	string fecha_baja;
	ve.open("bajas.txt", ios::in);
	
	if(ve.is_open()){		
		system("cls");
		gotoxy(30,10);	cout<<"CARGANDO INFORMACION"; 					 		
		gotoxy(20,12);	
		printf("\033[0;40;32m");
							
		for(int i=0; i<45; i++){ //largo linea carga
			cout<<char(219);
			Sleep(50);
		}
							
		printf("\033[0m");
		Encabezado();	  	    
			 
		cout<<"REGISTROS DE CLIENTES DADOS DE BAJA"<<endl; 
		ve>>Nom; 
		
		while(!ve.eof()){
			ve>>Pro_v;
			ve>>fecha_baja;
				
			cout<<"Nombre del cleinte"<<" "<<Nom<<endl; 
			cout<<"Producto que vendio"<<" "<<Pro_v<<endl; 
			cout<<"Fecha que fue dado de baja"<<" "<<fecha_baja<<endl; 
			cout<<"                         "<<endl; 
			ve>>Nom; 
		}
		ve.close();	 	
	}	else{
			cout<<"Se ha producido un error"<<endl; 		
		}
	
	cout<<"\n<Presione una tecla para volver al menu>";	getch();
	Menu();	
}

//Dar de baja un registro 
void Fecha_baja(ofstream &ba){
	Encabezado();
	string Nom;
	string Pro_v;
	string fecha_baja;
	ba.open("bajas.txt", ios::out | ios::app);
	
	cout<<"Ingrese el nombre (Para tener referencia)"<<endl;
	cin>>Nom;
	cout<<"Ingrese el producto que vendio"<<endl;
	cin>>Pro_v;
	cout<<"Ingrese la fecha de baja"<<endl; 
	cin>>fecha_baja; 
	ba<<Nom<<" "<<Pro_v<<" "<<fecha_baja <<endl;
	ba.close(); 
	
	cout<<"\n<Presione una tecla para volver al menu>";	getch();
	Menu();
}  

void baja(ifstream &Lec){ 
	Encabezado();
	string Nom;
	string Dire;
	string Muni; 
	string Depa;
	string Telef;
	string Nit;
	string Dpi;
	string Tel_ofi;
	string Pro_v;
	string Paten;
	string Repre; 
	string Contac;
	string dpiaux; 

	Lec.open("prueba.txt",ios::in);
	ofstream aux("auxiliar.txt",ios::out); 
	if(Lec.is_open()){
		cout<<"Ingrese el Codigo (DPI)"<<endl; 
		cin>>dpiaux; 
	
		Lec>>Nom; 
		while(!Lec.eof()){ 
			Lec>>Dire;
			Lec>>Muni;
			Lec>>Depa;
			Lec>>Telef;
			Lec>>Nit;
			Lec>>Dpi;
			Lec>>Tel_ofi;
			Lec>>Pro_v;
			Lec>>Paten;
			Lec>>Repre;
			Lec>>Contac;
			
		    if(Dpi==dpiaux){
				system("cls");
				gotoxy(30,10);	cout<<"BORRANDO LOS DATOS"; 					 		
				gotoxy(20,12);	
				printf("\033[0;40;32m");
									
				for(int i=0; i<45; i++){ //largo linea carga
					cout<<char(219);
					Sleep(50);
				}
									
				printf("\033[0m");
				Encabezado();	 	
		
			}	else{
      		 		aux<<Nom<<" "<<Dire<<" "<<Muni<<" "<<Depa<<" "<<Telef<<" "<<Nit<<" "<<Dpi<<" "<<Tel_ofi<<" "<<Pro_v<<" "<<Paten<<" "<<Repre<<" "<<Contac<<endl; 	
				}
			Lec>>Nom;
		}
		Lec.close();
		aux.close();		
	}	else{
			cout<<"Se presento un error"<<endl;	
		}	 
	remove("prueba.txt");
	rename("auxiliar.txt","prueba.txt"); 
}
   
void factura(){
	Encabezado();
	srand(time(NULL)); 
	int cod = rand() % (1000 + 1 ); 
	int c=1; 
	string f_fac; 
	string nom_c; 
	string pro; 
	float pre; 
	float can; 
	float tol; 
	float total; 
	float iva;
	char opc='S';  
		
	while(c!=0){ 
		cout<<"Codigo de Factura"<<" "<<cod<<endl;	
		cout<<"Numero de factura"<<" "<<c<<endl;
		cout<<"Ingrese la fecha de emision de factura"<<endl; 
		cin>>f_fac; 
		cout<<"Ingrese el nombre del cliente"<<endl; 
		cin>>nom_c; 
		cout<<"Ingrese el producto solicitado"<<endl; 
		cin>>pro; 
		cout<<"Ingrese el precio del producto"<<endl; 
		cin>>pre; 
		cout<<"Ingrese la cantidad"<<endl;
		cin>>can;  
		tol=pre*can;  
		iva=tol*.12;
		total=tol+iva; 
		 
		system("cls");
		gotoxy(30,10);	cout<<"GENERANDO FACTURA"; 					 		
		gotoxy(20,12);	
		printf("\033[0;40;32m");
			
		for(int i=0; i<41; i++){ //largo linea carga
			cout<<char(219);
			Sleep(50);
		}
			  
		printf("\033[0m");
		Encabezado();
		gotoxy(10,9);cout<< " ____________________________________________________________________________ "<<endl;
		gotoxy(10,10);cout<<"|Fecha de emision:"<<" "<<f_fac<<endl;
		gotoxy(39,10);cout<<"|Nombre Cliente:|"<<nom_c<<endl;
		gotoxy(65,10);cout<<"|Producto:|"<<pro<<endl;
		gotoxy(10,11);cout<<"|Precio:"<<" "<<"Q"<<pre<<endl;
		gotoxy(10,12);cout<<"|Cantidad:"<<" "<<can<<endl;
		gotoxy(10,13);cout<<"|Monto total de producto"<<" "<<"Q"<<tol<<endl; 
		gotoxy(10,14);cout<<"|IVA incluido"<<" "<<"Q"<<iva<<endl;
		gotoxy(10,15);cout<<"|                                                                           | "<<endl;
		gotoxy(42,15);cout<<" Monto total de la factura"<<" "<<"Q"<<total<<endl;
		gotoxy(10,16);cout<<"|___________________________________________________________________________| "<<endl;
		gotoxy(86,10);cout<<"|"<<endl;
		gotoxy(86,11);cout<<"|"<<endl;
		gotoxy(86,12);cout<<"|"<<endl;
		gotoxy(86,13);cout<<"|"<<endl;
		gotoxy(86,14);cout<<"|"<<endl;
		gotoxy(86,10);cout<<"|"<<endl;
		cout<<" "<<endl;
		gotoxy(10,18);cout<<"Desea Generar otra factura (S/N)  "<<endl; 
		cin>>opc; 
		    
		if(opc=='S'||opc=='s'){ 
			cout<<"Codigo de Factura"<<" "<<cod++<<endl;	
			system("cls");
			c++;	
		}	else{
				c=0;
		
				system("cls");
				gotoxy(30,10);	cout<<"VOLVIENDO AL MENU"; 					 		
				gotoxy(20,12);	
				printf("\033[0;40;32m");
					
				for(int i=0; i<41; i++){ //largo linea carga
					cout<<char(219);
					Sleep(50);
				}
					
				printf("\033[0m");
				Menu();  
			}
	}
}

void Menu(){
	ofstream Esa;
	ofstream ba;
	ofstream mo;
	ifstream Lec;
	ifstream ve;
	ifstream vi;
	bool Sesion=true;
	int x=26, y=10;
	char tecla;
	
	Encabezado();
	
	gotoxy(x,8);	cout<<"Bienvenido al sistema de Facturacion";
	gotoxy(x,10);	cout<<"Altas de Clientes";
	gotoxy(x,11);	cout<<"Bajas de Clientes";
	gotoxy(x,12);	cout<<"Cambios a Clientes";
	gotoxy(x,13);	cout<<"Buscar Registros";
	gotoxy(x,14);	cout<<"Ver Registros";
	gotoxy(x,15);	cout<<"Ver Clientes Modificados";
	gotoxy(x,16);	cout<<"Ver Clientes Dados de Baja";
	gotoxy(x,17);	cout<<"Crear Factura a Cliente";
	gotoxy(x,18);	cout<<"Crear Usuario Nuevo";
	gotoxy(x,19);	cout<<"Cerrar Sesi"<<char(162)<<"n";
	gotoxy(x,20);	cout<<"Salir del Programa";
	
	do{	
		!ENT;
		gotoxy(22, y);	cout<<"==>";
		fflush(stdin);	tecla=getch();
		
		if(ABJ || ARR){
			gotoxy(22, y);	cout<<"   ";
			if(ABJ){
				y+=1;
				if(y>20){y=10;}
			}
			if(ARR){
				y-=1;
				if(y<10){y=20;}
			}
			tecla=getch();
		}	
		if(tecla==ENT){
			switch(y){
				case 10:	//altas
					if(Activo.Altas==1){
						agregar(Esa);
					}	else{
							printf("\033[0;40;31m");
							gotoxy(65,y);	cout<<"Usuario no Autorizado";
							printf("\033[0m");	
							Sleep(1200);
							Menu();
						}
					break;
					
				case 11:	//bajas
					if(Activo.Bajas==1){
						baja(Lec);
						Fecha_baja(ba);						
					}	else{
							printf("\033[0;40;31m");
							gotoxy(65,y);	cout<<"Usuario no Autorizado";
							printf("\033[0m");	
							Sleep(1200);
							Menu();
						}
					break;
					
				case 12:	//cambios
					if(Activo.Cambios==1){
						modificarRe(Lec); 
						fechamod(mo);
					}	else{
							printf("\033[0;40;31m");
							gotoxy(65,y);	cout<<"Usuario no Autorizado";
							printf("\033[0m");	
							Sleep(1200);
							Menu();
						}
					break;
					
				case 13:	//buscar
					buscarcli(Lec);						
					break;
					
				case 14:	//ver registros
					Verdatos(Lec);
					break;
					
				case 15:	//Ver Clientes Modificados
					vizumod(vi);
					break;
					
				case 16:	//Ver Clientes Dados de Baja
					Verbajas(ve);
					break;
					
				case 17:	//factura
					if(Activo.Factura==1){
						factura();
					}	else{
							printf("\033[0;40;31m");
							gotoxy(65,y);	cout<<"Usuario no Autorizado";
							printf("\033[0m");	
							Sleep(1200);
							Menu();
						}
					break;
					
				case 18:	//crear usuario
					if(Activo.Super==1){
						NewUser(0);
					}	else{
							printf("\033[0;40;31m");
							gotoxy(65,y);	cout<<"Usuario no Autorizado";
							printf("\033[0m");	
							Sleep(1200);
							Menu();
						}
					break;
					
				case 19:	//cerrar sesion
					Sesion=false;
					Login();
					
				case 20:	//salir					
					exit(1);																					
			}
		}
	}while(Sesion);
}
