//Lista doblemente enlazada
#include <stdlib.h>
#include <stdio.h>

#define ASCENDENTE 1
#define DESCENDENTE 0

//Clase Nodo
class nodo{
    //Public hace referencia a las acciones del objeto
public:
    nodo(int v, nodo *sig=NULL, nodo *ant=NULL):
        valor(v), siguiente(sig), anterior(ant){}

private:
    //Private hace referencia a las caracteristicas o atributos del objeto
    int valor;
    nodo *siguiente;
    nodo *anterior;

    //La clase nodo es una clase amiga de lista esto le permite acceder a sus atributos privados
    friend class lista;

};

typedef nodo *pnodo;

//Clase lista
class lista{
    //Public hace referencia a las acciones del objeto
public:
    //Constructor nos sirve para inicializar la lista y sus acciones
    lista() : plista(NULL){}
    ~lista();

    void insertar(int v);
    void borrar(int v);
    bool listaVacia() {return plista==NULL;}
    void mostrar(int);
    void siguiente();
    void anterior();
    void primero();
    void ultimo();
    bool actual(){return plista!=NULL;}
    int valorActual() {return plista->valor;}

private:
    //Private hace referencia a las caracteristicas o atributos del objeto
    pnodo plista;
};

lista::~lista(){
    pnodo aux;
    primero();

    while(plista){
        aux=plista;
        plista=plista->siguiente;
        delete aux;
    }
}

//Insertar elementos a la lista
void lista::insertar(int v){
    //variable de clase lista
    pnodo nuevo;

    primero();

    //Si la lista esta vacia o lista en su valor es mayor al valor ingresado entonces 
    if(listaVacia()||plista->valor > v){
        //Crear un nuevo nodo
        nuevo = new nodo(v,plista);
        //Si lista es igual a NULL, lista sera igual al nuevo nodo
        if(!plista) plista=nuevo;
        //Si no lista apuntando a anterior sera igual a nuevo
        else plista->anterior=nuevo;
    }

    else{
        // Avanzamos hasta el último elemento o hasta que el siguiente tenga un valor mayor que v 
        while(plista->siguiente&&plista->siguiente->valor<=v) siguiente();
        //Creamos nuevo nodo
        nuevo = new nodo(v,plista->siguiente,plista);
        //Lista actual apuntando a siguiente sera igual al nuevo nodo
        plista->siguiente=nuevo;
        if(nuevo->siguiente) nuevo->siguiente->anterior=nuevo;
    }
}

void lista::borrar(int v){
    //Nodo de clase lista
    pnodo nodo;
    //Igualamos nodo a lista
    nodo=plista;

    
    while(nodo&&nodo->valor<v) nodo=nodo->siguiente;

    while(nodo&&nodo->valor>v) nodo=nodo->anterior;

    if(!nodo || nodo->valor !=v) return;

    if(nodo->anterior)
        nodo->anterior->siguiente = nodo->siguiente;
    if(nodo->siguiente)
        nodo->siguiente->anterior = nodo->anterior;

    delete nodo;
}

void lista::mostrar(int orden){
    pnodo nodo;

    //Mostrar la lista en orden ascendente
    if(orden==ASCENDENTE){
        primero();
        nodo=plista;
        while(nodo){
            printf("%d -> ", nodo->valor);
            nodo=nodo->siguiente;
        }
    }
    //Mostrar la lista en orden descendente
    else{
        ultimo();
        nodo=plista;
        while(nodo){
            printf("%d -> ", nodo->valor);
            nodo=nodo->anterior;
        }
    }
    printf("\n");
}

void lista::siguiente(){
    if(plista) plista = plista->siguiente;
}

void lista::anterior(){
    if(plista) plista = plista->anterior;
}

void lista::primero(){
    // Primer elemento de la lista 
    while(plista && plista->anterior) plista = plista->anterior;
}

void lista::ultimo(){
    // Ultimo elemento de la lista 
    while(plista && plista->siguiente) plista = plista->siguiente;
}

int main(){
    // Objeto de clase lista 
    lista listaDE;

    // Insertar al objeto 
    listaDE.insertar(30);
    listaDE.insertar(20);
    listaDE.insertar(10);
    listaDE.insertar(60);

    // Mostrar el Objeto 
    listaDE.mostrar(ASCENDENTE);
    listaDE.mostrar(DESCENDENTE);

    //Mostrar primer elemento de la lista
    listaDE.primero();
    printf("Primero: %d\n", listaDE.valorActual());

    //Mostrar ultimo elemento de la lista
    listaDE.ultimo();
    printf("Ultimo: %d\n", listaDE.valorActual());

    //Borrar elemento de la lista
    listaDE.borrar(30);
    listaDE.borrar(20);
    listaDE.borrar(10);
    listaDE.borrar(60);

    //Mostrar nuevamente la lista de forma ascendente y descendente
    listaDE.mostrar(ASCENDENTE);
    listaDE.mostrar(DESCENDENTE);

    system("pause");

    return 0;
}

