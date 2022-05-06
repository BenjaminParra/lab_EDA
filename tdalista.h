#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char* palabra;
    struct Song* song;
    struct Node* siguiente;
}Node;

typedef struct Lista
{
    Node* head;
}Lista;

typedef struct Song
{
	char nombreCancion[70];
	int genero; //numero identicador del genero de la canciones
	char duracionString[70]; //duracion de la cancion en formato MM:SS
	char artista[70]; //nombre del artista
	int duracion; //duracion de la cancion en segundos
}Song;


//funcion que se encarga de crear un nodo vacio
// Entrada: niguna
// Salida: ninguna
Node* crearNodo()
{
    Node* nvo = (Node*)malloc(sizeof(Node));
    //nvo->dato = dato;
    nvo->siguiente = NULL;

    return nvo;
}


//funcion que se encarga de realizar crear una cancion
// Entrada: string nombre, int idgenero, string dureacion (HH:MM:SS), string artista, int duracion ens egundos
// Salida: cancion
Song* creaCancion(char *nombreCancion, int genero, char* duracionString, char* artista, int duracion){
  Song* cancion = (Song*)malloc(sizeof(Song));
  strcpy(cancion->nombreCancion, nombreCancion);
  cancion->genero = genero;
  strcpy(cancion->duracionString ,duracionString);
  strcpy(cancion->artista, artista);
  cancion->duracion =  duracion;
  return cancion;

}
//funcion que se encarga de verificar si una lista esta vacia o no
// Entrada: lista
// Salida: entero
int esListaVacia(Lista* lista)
{
  if (lista->head == NULL)
    return 1;
  else
    return 0;
}

//funcion que se encarga de contar el largo de la lista
// Entrada: lista
// Salida: entero
int getLargo(Lista* lista){
  int contador = 0;
  if (!esListaVacia(lista)){
    Node * auxiliar=lista->head;
    while (auxiliar!=NULL){
      contador = contador + 1;
      auxiliar=auxiliar->siguiente;

    }
  }
  return contador;
}

//funcion que se encarga de crear una lista vacia
// Entrada: ninguna
// Salida: ninguna
Lista* crearLista()
{
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->head = NULL;

    return lista;
}

//funcion que se encarga insertar un nodo a la lista
// Entrada: lista, cancion
// Salida: ninguna
void insertarNodo(Lista* lista,  Song* cancion)
{
    if (lista->head == NULL)
    {
        Node* nvo = crearNodo();
        nvo->song = cancion;


        lista->head = nvo;
    }else
    {
        Node* current = lista->head;

        while(current->siguiente != NULL)
        {
            current = current->siguiente;
        }

        Node* nvo = crearNodo();
        nvo->song = cancion;
        current->siguiente = nvo;
    }
}

//funcion que se encarga de ordenar una lista dada una seleccion
// Entrada: lista, caracter
// Salida: ninguna
void ordernarLista(Lista* lista, char operator)
{
    Node* current = lista->head;
    Node* siguiente;

    while (current!=NULL)
    {
        siguiente = current->siguiente;
        while(siguiente != NULL)
        {
          switch (operator) {
            case 'C':
                    if (strcmp(current->song->nombreCancion, siguiente->song->nombreCancion)>0)
                    {
                        Song* cancion = current->song;
                        //int aux = current->dato;
                        current->song = siguiente->song;
                        siguiente->song = cancion;
                    }
                    siguiente = siguiente->siguiente;
                    break;
            case 'A':
                    if (strcmp(current->song->artista, siguiente->song->artista)>0)
                    {
                        Song* cancion = current->song;
                        //int aux = current->dato;
                        current->song = siguiente->song;
                        siguiente->song = cancion;
                    }
                    siguiente = siguiente->siguiente;
                    break;
            case 'D':
                    if (current->song->duracion > siguiente->song->duracion)
                    {
                        Song* cancion = current->song;
                        //int aux = current->dato;
                        current->song = siguiente->song;
                        siguiente->song = cancion;
                    }
                    siguiente = siguiente->siguiente;
                    break;
          }



        }
        current = current->siguiente;
    }
}
