#include <stdio.h>
#include <stdlib.h>
#include "tdalista.h"
#include "tools.h"
#include <time.h>
#include <windows.h>


int main(int argc, char* argv[])
{
  clock_t ciniIt, cfinIt;

	ciniIt=clock();
  FILE* archivo;
  archivo=fopen(argv[1],"r"); //se abre archivo
	int cantidadCanciones;
	fscanf(archivo, "%d", &cantidadCanciones);

	fclose(archivo);
  Lista* lista = leerCanciones(argv[1], cantidadCanciones);

  archivo = fopen(argv[2],"r");
	int cantidadGeneros, genero;
	fscanf(archivo, "%d %d",&cantidadGeneros,&genero);
	fclose(archivo);
  generos* generitos;
	generitos = leerGeneros(argv[2], cantidadGeneros);

  archivo = fopen(argv[3],"r");
	 int cantidadReclamos;
	fscanf(archivo, "%d",&cantidadReclamos);

  char opcion = argv[4][0];

	fclose(archivo);
  reclamos* reclamos;
  reclamos = leerReclamos(argv[3], cantidadReclamos);

    Lista* listaFiltrada = creaPlaylist(lista, genero);
    Lista* listaFinal = eliminaReclamos(listaFiltrada, reclamos, cantidadReclamos);
    creaLineaOutFiltrada(listaFinal,generitos,genero);
    creaLineaOut(listaFiltrada,generitos,genero);



    cfinIt=clock();
  	//printf("clock_t iterativo:  %f\n",(double)(cfinIt-ciniIt)/CLOCKS_PER_SEC);

  }
