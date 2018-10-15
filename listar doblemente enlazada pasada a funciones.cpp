//Lista doblemente enlazada
#include <stdio.h>
#include <stdlib.h>


#define ASCENDENTE 1
#define DESCENDENTE 0
//Clase Nodo
struct nodo{
    int dato;
    struct nodo *siguiente;
    struct nodo *anterior;
};

//Prototipo de funciones
void insertarLista(nodo *&, int);
void MostrarLista(nodo *&, int);
void BorrarLista(nodo *&);
void Borrar(nodo *&lista, int);
int valorActual(nodo *&lista);
int primero(nodo *&);
int ultimo(nodo *&);

//funcion principal
int main(){
	//Se crea una variable nodo llamado lista y la igualamos a NULL
    nodo *lista=NULL;
	//insertamos los datos  a la lista
    insertarLista(lista, 30);
    insertarLista(lista, 20);
    insertarLista(lista, 10);
    insertarLista(lista, 11);
	//mostramos lo elementos de la lista
    MostrarLista(lista, ASCENDENTE);
    MostrarLista(lista, DESCENDENTE);
    printf("\n\n");
	//mostrar el primer y ultimo elemento de la lista
    printf("Primero: %d\n", primero(lista));
    printf("Ultimo: %d\n\n", ultimo(lista));
	//Borramos los valores de la lista
    Borrar(lista, 30);
    Borrar(lista, 15);
    Borrar(lista, 10);
    Borrar(lista, 11);
	//mostramos la lista de primero a ultimo y despues de ultimo a primero	
    MostrarLista(lista, ASCENDENTE);
    MostrarLista(lista, DESCENDENTE);
	//borramos todos los elementos de la lista
    BorrarLista(lista);

    return 0;
}

void insertarLista(nodo *&lista, int numero){
    nodo *nuevo, *actual;

   nuevo = new struct nodo();
   nuevo->dato = numero;
   actual = lista;

   if(actual) while(actual->anterior) actual = actual->anterior;
   if(!actual || actual->dato > numero) {
      nuevo->siguiente = actual;
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!lista) lista = nuevo;
   }
   else {
      while(actual->siguiente &&actual->siguiente->dato <= numero)
      actual = actual->siguiente;
      nuevo->siguiente = actual->siguiente;
      actual->siguiente = nuevo;
      nuevo->anterior = actual;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }
}

void MostrarLista(nodo *&lista, int orden) {
   nodo *nodo = lista;

   if(!lista) printf("Lista vacía");

   nodo = lista;

   if(orden == ASCENDENTE) {
      while(nodo->anterior) nodo = nodo->anterior;
      printf("Orden ascendente: ");
      while(nodo) {
         printf("%d -> ", nodo->dato);
         nodo = nodo->siguiente;
      }
   }
   else {
      while(nodo->siguiente) nodo = nodo->siguiente;
      printf("Orden descendente: ");
      while(nodo) {
         printf("%d -> ", nodo->dato);
         nodo = nodo->anterior;
      }
   }

   printf("\n");
}

void BorrarLista(nodo *&lista) {
   nodo *nodo, *actual;
   actual = lista;

   while(actual->anterior) actual = actual->anterior;

   while(actual) {
      nodo = actual;
      actual = actual->siguiente;
      delete (nodo);
   }
   lista = NULL;
   printf("\nSe borro correctamente la lista\n");
}

void Borrar(nodo *&lista, int numero) {
   nodo *nodo;
   nodo = lista;

   while(nodo && nodo->dato < numero) nodo = nodo->siguiente;
   while(nodo && nodo->dato > numero) nodo = nodo->anterior;

   if(!nodo || nodo->dato != numero) return;

   if(nodo->anterior)
      nodo->anterior->siguiente = nodo->siguiente;
   if(nodo->siguiente)
      nodo->siguiente->anterior = nodo->anterior;

    delete nodo;
}

int valorActual(nodo *&lista){
    return lista->dato;
}

int primero(nodo *&lista){
    nodo *plista;
    plista = lista;
    while(plista && plista->anterior) plista = plista->anterior;
    return plista->dato;
}

int ultimo(nodo *&lista){
    nodo *plista;
    plista = lista;
    while(plista&&plista->siguiente) plista = plista->siguiente;
    return plista->dato;
}

