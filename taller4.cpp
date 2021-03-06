/*  Estructuras de datos 2
    Presentado por: Jhon Anderson Sanchez
    docente: Carlos londo�o
    ingenieria en sistemas
    III Semestre
    Taller 4 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define reservar_memoria (Nodo *)malloc(sizeof(Nodo))
#define tamano 100
#include <math.h>
/*
* Estructuras
*/

struct Nodo{
    float dato;
    Nodo *siguiente;
};

/*
* Prototipo de Funciones
*/
void menu();
void ingresarExpresion(char [tamano]);
void mostrarExpresion(char [tamano]);
bool pilaVacia(Nodo *pila);
void hacerOperacionPostfijo(Nodo *&, char [tamano]);
void mostrarResultadosOperacionPostfijo(Nodo *&, char [tamano]);
float hacerOperacion(float, float, char);
bool esNumero(char);
bool esOperador(char);
bool esEspacio(char);
//bool esFinCadena(char);
void insertarElementoPila(Nodo *&, float);
float eliminarElementoPila(Nodo *&);
void imprimirPila(Nodo *);
float convertirCadenaNumero(char [tamano]);
//Funcion Principal
int main(){
    menu();
    return 0;
}
//funcion para el menu principal
void menu(){
    Nodo *pila = NULL;
    char miArreglo[tamano];
    int opcion;
    float n;
    do{
        printf("\n\t\t---MENU NOTACION POSTFIJA---\n\n");
        printf("\n\t\t----------------------------\n\n");
        printf("\n1- Ingresar Expresion");
        printf("\n2- Mostrar Expresion Ingresada");
        printf("\n3- Hacer Operacion Postfija");
        printf("\n4- Mostrar Resultados Operacion Postfija");
        printf("\n5- Insertar un elemento a la pila");
        printf("\n6- Eliminar un elemento de la pila");
        printf("\n7- mostrar elementos de la pila");
        printf("\n0- Salir");
        printf("\n-----------------------------------");
        printf("\nSeleccione una opcion del menu: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: ingresarExpresion(miArreglo);
                break;
            case 2: mostrarExpresion(miArreglo);
                break;
            case 3: hacerOperacionPostfijo(pila, miArreglo);
                    printf("\nOperacion Realizada Correctamente\n\n");
                break;
            case 4: mostrarResultadosOperacionPostfijo(pila, miArreglo);
                    printf("\n\n");
                break;
            case 5: insertarElementoPila(pila, n);
                break;
            case 6: eliminarElementoPila(pila);
                break;
            case 7: imprimirPila(pila);
                break;
            case 0: exit(0);
                break;
            default: printf("\nNo es una opcion valida, intentelo de nuevo\n");
                break;
        }
        system("pause");
        system("cls");
    }while(opcion != 0);
}

void ingresarExpresion(char miArreglo[tamano]){
    fflush(stdin);
    int longitud;
    printf("\n Ingrese la expresion en postfijo: ");
    fgets(miArreglo, tamano, stdin);
    longitud = strlen(miArreglo);
    printf("\n Estructura almacenada con exito \n");
    printf("\nExpresion ingresada: %s\n", miArreglo);
}
void mostrarExpresion(char miArreglo[tamano]){
    int longitud;
    longitud = strlen(miArreglo);
    printf("\nLongitud de la expresion: %d", longitud);
    printf("\nExpresion ingresada: %s\n", miArreglo);
}
bool pilaVacia(Nodo *pila){
    return (pila == NULL) ? true:false;
}
void hacerOperacionPostfijo(Nodo *&pila, char miArreglo[tamano]){
    int i, longitud, j = 0;
    float numero_insertar,a,b,c;
    char numero[tamano];
    longitud = strlen(miArreglo);
    for(i = 0; i < longitud; i++){
        if(esNumero(miArreglo[i])){
            numero[j] = miArreglo[i];
            j++;
        }
        if(esEspacio(miArreglo[i])){
            numero_insertar = convertirCadenaNumero(numero);
            insertarElementoPila(pila, numero_insertar);
            j=0;
        }
        if(esOperador(miArreglo[i])){
            a=eliminarElementoPila(pila);
            b=eliminarElementoPila(pila);

            c=hacerOperacion(a,b,miArreglo[i]);
            insertarElementoPila(pila,c);

            i++;
        }
    }
}
float hacerOperacion(float a, float b, char operador){
    int ope =operador;
    float c;

     switch(ope)
    {
    case 43:
        c=a+b;
    break;
    case 45:
        c=a-b;
    break;
    case 47:
        c=a/b;
    break;
    case 94:
        c=pow(a,b);
    break;
    case 42:
        c=a*b;
    break;
    }
    return c;
}
bool esNumero(char valor){
    int numero = valor;
    return (numero > 47 && numero < 58) ? true: false;
}
bool esOperador(char valor){
    int numero = valor;
    return (numero == 43 || numero == 45 || numero == 42 || numero == 47 || numero == 94) ? true: false;
}
bool esEspacio(char valor){
    int numero = valor;
    return (numero == 32) ? true: false;
}

void insertarElementoPila(Nodo *&pila, float n){
    Nodo *nuevo=reservar_memoria;
    printf("\ningrese el elemento del nuevo nodo \n");
    scanf("%d",&n);
    nuevo->dato =n;
    nuevo->siguiente=pila;
    pila=nuevo;
}
 float eliminarElementoPila(Nodo *&pila){
    float n;
    Nodo *aux = pila;
    n = aux->dato;
    pila = aux->siguiente;
    free(aux);
    return n;
}
void imprimirPila(Nodo *pila){
   /* while(pilaVacia(pila)!= true);
    {
        printf("%d",pila -> dato);
        pila=pila -> siguiente;*/

        Nodo *actual=reservar_memoria;
        actual=pila;
        if(actual!=NULL){
            while(actual !=NULL){
                printf("\n%d", actual->dato);
                actual=actual->siguiente;
            }
        }else{
            printf("\n La pila se encuentra vacia");
        } //Esta funcion presenta un problema el cual me esta conviertiendo los numeros en 0
}
void mostrarResultadosOperacionPostfijo(Nodo *&pila, char miArreglo[tamano]){
    printf("%s =  %0.1f",miArreglo, pila->dato);
}
float convertirCadenaNumero(char numero[tamano]){
    float num;
    num = atoi(numero);
    return num;
}
