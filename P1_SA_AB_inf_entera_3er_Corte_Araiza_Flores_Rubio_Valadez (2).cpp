#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <regex>

/* Creadores Jose de Jesus Araiza Rodriguez, Bryan Josue Flores Gonzales,
    Julio Leonel Rubio Ramirez, Carlos Ernesto Valadez Berisatin*/
using namespace std;

regex vedad("[0-9]+");  //Validaciones con regex


struct Nodo
{
	int dato;
	Nodo *der;		
	Nodo *izq;
};


char menu(void);
char menure(void);

Nodo *crearNodo(int);

void insertar(Nodo *&, int);
void mostrar(Nodo *,int);
void PreOrden(Nodo *);			//funciones 
void InOrden(Nodo *);
void PostOrden(Nodo *);
void nivel(Nodo *arbol);
bool busqueda(Nodo *, int);
void recorridos();

void gotoxy(int x,int y)  //Función de gotoxy 
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}


Nodo *arbol=NULL;

main()
{
//	int dato;
	char opc;
	int V=2;
	setlocale(LC_CTYPE,"");             //funcion para usar español


	do
	{
	     int contador=0;
	     int dato;
	     char data[10];
		opc=menu();                          //menu utilizando rangos con codigo ascci
	
	
		switch(opc)
		{
			
			char o;
			
			case 59:	do
						{
							memset(data,0,sizeof(data)); 
							gotoxy(16,11);
							cout<<"\nIngrese un numero: ";				          
							fflush(stdin);
							gotoxy(20,12);gets(data);
							fflush(stdin);
							if(!regex_match(data,vedad))
							{
								Beep(500,500);
								gotoxy(20,12);printf("                                                      ");
								gotoxy(20,12);printf("ERROR");
								Sleep(500);
								gotoxy(20,12);printf("                                                      ");
							}
						}while(!regex_match(data,vedad));
						dato=atoi(data);
						V=5;
						insertar(arbol,dato);
						cout<<"\n";
						system("pause");
									
					break;
					
			case 60: 
					if(V	==5)
					{
						cout<<"Mostrando el Arbol completo: \n\n";
						cout<<"El arbol esta en Horizontal \n\n";
				    	mostrar(arbol,contador);
				    	cout<<"\n";
					}
			    	else
			    	cout<<"INGRESE DATOS \n\n";
			    	
			    	system("pause");
					break;
					
			case 61:
					if(V==5)
					{
						recorridos();
					}
			    	else
			    	cout<<"INGRESE DATOS \n\n";
		
					system("pause");
					break;	

			case 62: 
					if(V==5)
					{
						cout<<"\nRecorrido en Nivel: ";
						nivel(arbol);
					}
			    	else
			    	cout<<"INGRESE DATOS \n\n";
		
					system("pause");
				    break;  	
					
			case 63:
					if(V==5)
					{
						cout<<"\nNumero a Buscar: ";
						cin>>dato;
						if(busqueda(arbol,dato) == true){
						cout<<"Elemento '"<<dato<<"' SI fue encontrado.";
					}else{
						cout<<"Elemento '"<<dato<<"' NO fue encontrado.";
					}
					}
					else
			    	cout<<"INGRESE DATOS \n\n";
			    	system("pause");
					
					         
					
					
			case 27: 
				   printf("\nFin del programa\n");
						                             
					system("pause");			
			
			default:
				if(opc !=27)
				{
					
				}
					break;

	}
		
		
		}while(opc!=27);	
	return 0;
	
	
	
	getch();
	return 0;
}

char menu()
{
	char opc1='\0';
	system("cls");
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),9);
	printf("Menu\n");
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
	printf("[F1] Insertar Nuevo Nodo\n");
	printf("[F2] Mostrar arbol\n");	
	printf("[F3] Mostrar Recorridos\n");	
	printf("[F4] Mostrar en Nivel\n");
	printf("[F5] Buscar nodo\n");
	printf("ESC. Salir\n");
	printf("Seleccione una opcion: ");

	opc1=getch();                          //validacion del ESC
	
	if(opc1==0)
	{
		opc1 = getch();
	}
	else if(opc1!=27)
	{
		opc1=-1;
	}
	return opc1;
	
}

Nodo *crearNodo(int n) //crear nuevo nodo 
{
	
	Nodo *nuevo_nodo = new Nodo();
	
	nuevo_nodo->dato = n;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	
	return nuevo_nodo;
}

void insertar(Nodo *&arbol, int n)
{
	
	if(arbol == NULL)
	{
		Nodo *nuevo_nodo= crearNodo(n);
		arbol = nuevo_nodo;
	}
	else 
	{
		int valorRaiz = arbol->dato;
		if(n < valorRaiz)
		{
			insertar(arbol->izq,n);
		}
		else
		{
			insertar(arbol->der,n);
		}
	}
	
}

void mostrar (Nodo *arbol, int cont)
{
	
	if (arbol == NULL)
	{
		return;
	}
	else 
	{
		mostrar(arbol->der,cont+1);
		for(int i=0; i<cont; i++)
		{
			cout<<"   ";
			cout<<"   ";
		}
		cout<<arbol->dato<<endl;
		mostrar(arbol->izq,cont+1);
	}
}

void PreOrden(Nodo *arbol){
	if(arbol == NULL){
		return ;
	}else{
		cout<<arbol->dato<<" - ";
		PreOrden(arbol->izq);
		PreOrden(arbol->der);
	}
}

void InOrden(Nodo *arbol){
	if(arbol == NULL){
		return ;
	}else{
		InOrden(arbol->izq);
		cout<<arbol->dato<<" - ";
		InOrden(arbol->der);
	}
}

void PostOrden(Nodo *arbol){
	if(arbol == NULL){
		return ;
	}else{
		PostOrden(arbol->izq);
		PostOrden(arbol->der);
		cout<<arbol->dato<<" - ";
	}
}

bool busqueda(Nodo *arbol, int n){
	if(arbol == NULL){
		return false;
	}else if(n == arbol->dato){
		return true;
	}else if( n < arbol->dato){
		busqueda(arbol->izq,n);
	}else{
		busqueda(arbol->der,n);
	}
}

void nivel(Nodo *arbol){
	
	if(arbol == NULL){
		return ;
	}else{
		cout<<arbol->dato<<" - ";
		nivel(arbol->izq);
		nivel(arbol->izq);
		
	}
	system("pause");	
}

void recorridos()
{
	//	int dato;
	char opc;
	int V=2;



	do
	{
	     int contador=0;
	     int dato;
	     char data[10];
		opc=menure();                          //menu utilizando rangos con codigo ascci
	
	
		switch(opc)
		{
			
			char o;
			
			case 59:PreOrden(arbol);
					system("pause");				//funciones 			
					break;
					
			case 60: InOrden(arbol);
					system("pause");	
					break;
					
			case 61:PostOrden(arbol);
					system("pause");	
					break;	
 	
					
					         
					
					
			case 27: 
				   printf("\nFin de Recorridos\n");						                           			
			
			default:
				if(opc !=27)
				{
					
				}
					break;

	}
		
		
		}while(opc!=27);			
}

char menure()
{
	char opc1='\0';
	system("cls");
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),9);
	printf("Menu\n");
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),15);
	printf("[F1] mostrar recorrido PreOrden\n");
	printf("[F2] mostrar recorrido InOrden\n");
	printf("[F3] mostrar recorrido PostOrden\n");
	printf("ESC. Salir\n");
	printf("Seleccione una opcion: ");

	opc1=getch();                          //validacion del ESC
	
	if(opc1==0)
	{
		opc1 = getch();
	}
	else if(opc1!=27)
	{
		opc1=-1;
	}
	return opc1;
	
}
	

