#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "tdalista.h"
//Funcion que entrega un entero de la cantidad de caracteres presentes en un arreglo de caracteres
//Entrada: arreglo de caracteres (representado a una palabra o string) y caracter a buscar
//salida: entero con la cantidad de ocurrencias del caracter

struct generos{
	int idGenero; //numero identificador del genero
	char nombreGenero[70]; //el nombre de dicho genero

};typedef struct generos generos;


struct reclamos{
	//int idGenero; //numero identificador del genero
	char cancionesReclamo[70]; //el nombre de dicho genero

};typedef struct reclamos reclamos;


// Funcion se encarga de leer el archivo con las indicaciones de la playlist requerida y almacena los datos en la estructura generos
//Entrada: caderna de caracteres (nombre del archivo), entero con la canctidad de generos existentes
//Salida: arregloe de generos
generos* leerGeneros(char *nombre, int cantidadGenero){
	generos *genero = (generos*)malloc(sizeof(struct generos) * cantidadGenero);
	FILE* archivo;
	int i = 0;
	char buffer[1024];
	if (archivo = fopen(nombre, "r")){
		fgets(buffer, 1024, archivo);
		while (fscanf(archivo, "%d %s", &genero[i].idGenero, &genero[i].nombreGenero) != EOF){
			++i;
		}
		fclose(archivo);
	}
	return genero;
}


//Funcion que entrega un entero de la cantidad de caracteres presentes en un arreglo de caracteres
//Entrada: arreglo de caracteres (representado a una palabra o string) y caracter a buscar
//salida: entero con la cantidad de ocurrencias del caracter
int cuentaCaracteres(char* palabra, char caracter){
	int i,contador = 0;
	for(i=0;palabra[i];i++)
	{
		if(palabra[i]==caracter){
			contador++;
		}
 	}
 	return contador;
  }
	// Funcion que convierte la duracion en el formato HH:MM:SS o MM:SS de las canciones en un int que representa la cantidad de segundos
	//Entrada: arreglo de caracteres que contiene el tiempo en el formato ya escrito
	//Salida: entero con la cantidad de segundos
int duracionEnSegundos(char* duracion){
	int largo_duracion;
	largo_duracion =  cuentaCaracteres(duracion,':');
	char * token = strtok(duracion, ":");
 	int tiempos[largo_duracion];
	int outPut,num1,num2, num3;
	if (largo_duracion == 1)
	{
		tiempos[0] = atoi(token);
   	 	token =   strtok(NULL, ":");
    	tiempos[1] = atoi(token);
     	token =   strtok(NULL, ":");
     	num1 = tiempos[0]*60;
		num2 = tiempos[1];
		outPut = num1+num2;
	}else{
		tiempos[0] = atoi(token);
    	token =   strtok(NULL, ":");
    	tiempos[1] = atoi(token);
	    token =   strtok(NULL, ":");
        tiempos[2] = atoi(token);
        num1 = tiempos[0]*3600;
        num2 = tiempos[1]*60;
        num3 = tiempos[2];
        outPut = num1+num2+num3;

	}
	return  outPut;

}

// Funcion se encarga de leer el archivo con los reclamos y almacena los datos en la estructura reclamos
//Entrada: caderna de caracteres (nombre del archivo), entero con la canctidad de generos existentes
//Salida: arregloe de reclamos
reclamos* leerReclamos(char* nombre, int cantidadReclamos){
  reclamos *reclamo = (reclamos*)malloc(sizeof(struct reclamos) * cantidadReclamos);
	FILE* archivo;
	int i = 0;
	char buffer[1024];
	if (archivo = fopen(nombre, "r")){
		fgets(buffer, 1024, archivo);
		while (fscanf(archivo, "%s", &reclamo[i].cancionesReclamo) != EOF){
			++i;
		}
		fclose(archivo);
	}
	return reclamo;
}





// Funcion lee cada linea de las canciones y la almacena en una estructura de canciones
// Entrada: cadena de caracateres (nombre del archivo de canciones), entero que es la cantidad de canciones existentes en el archivo
// Salida: Un arreglo de canciones
Lista* leerCanciones(char *nombre,int cantidadCanciones){//char *nombre, int numeroPostulantes){
  Lista *TDALista = crearLista();
  Song *songs = NULL;// (canciones*)malloc(sizeof(struct canciones) * cantidadCanciones);
  FILE* archivo;
  char buffer[1024];
  int aux_duracion;
  static char nombreCancion[100];
  int genero;
  static char duracionString[20];
  static char artista[100];
  //printf("este es nombre %s\n",nombre );
  static char duracion_string[20];
  if (archivo = fopen(nombre, "r")){
    fgets(buffer, 1024, archivo);
    while (fscanf(archivo, "%s %d %s %s", &nombreCancion,&genero, &duracionString, &artista) != EOF){
      //printf("nombre %s\n",nombreCancion );
      strcpy(duracion_string,duracionString);
      aux_duracion = duracionEnSegundos(duracion_string);
      //songs[i].duracion = aux_duracion;
      Song* cancion = creaCancion(nombreCancion, genero, duracionString, artista, aux_duracion);
      insertarNodo(TDALista, cancion);

    }
    fclose(archivo);
  }
  return TDALista;
}

//Funcion que se encarga de verificar que una cancion no se encuentre en una lista
//En caso de que el nombre de cancion y artista coincidan entregará un 1, en caso contrario un 0
//Entrada: Una lista, una cancion (verificar estructura al inicio del programa)
//Salida: un valor entero que 1 significa la existencia y 0 en caso de que no se encuentre
int existeEnPlaylist(Lista* lista, Song* song){
	int existe = 0; //cero si es que no existe
	if (!esListaVacia(lista))
  {
    Node* current = lista->head;
    while (current!=NULL)
    {
			if (strcmp(current->song->nombreCancion,song->nombreCancion)== 0 && strcmp(current->song->artista,song->artista)== 0){
				existe = 1;
				current = current->siguiente;
			}else{
				current = current->siguiente;
			}

		}


	}
	return existe;




}
//funcion que se encarga de realizar la seleccion de canciones para la playlist considerando el genero de esta y su duracion, luego
// de crear la playlist se encargará de escribirla en un archivo de salida
// Entrada: una lista, id del genero
// Salida: lista
Lista* creaPlaylist(Lista* lista, int idGenero){
  Lista* sublista = crearLista();
	int existe = 0;
  if (!esListaVacia(lista))
  {
    Node* current = lista->head;
    while (current!=NULL)
    {

			existe = existeEnPlaylist(sublista,current->song);

			if ((current->song->genero == idGenero) && (existe == 0)) {
				Song* cancion = current->song;
				insertarNodo(sublista,cancion);
				current = current->siguiente;

			}else{
				current = current->siguiente;

			}

		}
		return sublista;
	}
}
//Funcion que se encarga de verificar que una cancion no se encuentre en un arreglo de reclamos
//artista coincidan entregará un 1, en caso contrario un 0
//Entrada: Un arreglo de reclamos, nombreArtista, largo actual de los reclamos
//Salida: un valor entero que 1 significa la existencia y 0 en caso de que no se encuentre
int existeEnPlaylistReclamos(reclamos* reclamos, char* artista, int cantidadReclamos){
	int existe = 0; //cero si es que no existe
	for (int i = 0; i < cantidadReclamos; ++i){
		if (strcmp(reclamos[i].cancionesReclamo,artista)== 0){
			existe = 1;

		}
	}
	return existe;


}


//funcion se encarga de eliminar canciones que hayan sido reclamdas
// Entrada: lista, arreglo de reclamos, entero con la cantidad de reclamos
// Salida: lista
Lista* eliminaReclamos(Lista* lista, reclamos* reclamos, int cantidadReclamos){
	Lista* sublista = crearLista();
	int existe;
  if (!esListaVacia(lista))
  {
    Node* current = lista->head;
    while (current!=NULL)
    {
			existe = existeEnPlaylistReclamos(reclamos, current->song->artista, cantidadReclamos);
			if (existe==0) {
				Song* cancion = current->song;
				insertarNodo(sublista,cancion);
				current = current->siguiente;

			}else{
				current = current->siguiente;

			}

		}
		return sublista;
	}

}

//funcion que se encarga contabilizar la duracion final de una playlist (lista)
// Entrada: lista
// Salida: entero
int getTiempo(Lista* lista){
	int tiempoTotal = 0;
  if (!esListaVacia(lista))
  {
    Node* current = lista->head;
    while (current!=NULL)
    {
				tiempoTotal = tiempoTotal + current->song->duracion;
				current = current->siguiente;



			}
			return tiempoTotal;

		}

	}
	//Funcion complementaria tiempoEnString, obtiene el string de las horas contenido en la cantidad de segundos
// entrada: un int que es la cantidad de segundos
// salida: un string con el formato HH:
char* horaEnString(int tiempo){
	static char tiempo_string[20];
	char hora_string[30];
	int hora;
	if(tiempo < 3600){
		strcat(tiempo_string,"00:");
	}else{
		hora = tiempo/3600;
		if(hora<10){
			strcat(tiempo_string,"0");
			sprintf(hora_string,"%d",hora);
			strcat(tiempo_string,hora_string);
			strcat(tiempo_string,":");
			}else{
				sprintf(hora_string,"%d",hora);
				strcat(tiempo_string,":");
			}
	}

	return tiempo_string;
}

	//Funcion que transforma un entero que reseprenta tiempo (en seg) a un string HH:MM:SS
//entrada: un int que contiene la cantidad de tiempo en segundos
//salida: un string que contiene la cantidad de tiempo en el formato HH:MM:SS
char* tiempoEnString(int tiempo){
	static char tiempo_string[20];
	char minutos_string[20];
	char* hora_string;
	hora_string = horaEnString(tiempo);
	int hora, minuto, segundos;
	strcat(tiempo_string,hora_string);
	if(tiempo<3600){
		minuto = tiempo/60;
		segundos = tiempo%60;
		}else{
			minuto = (tiempo%3600)/60;
			segundos = (tiempo%3600)%60;
		}
	if(minuto<10){
		strcat(tiempo_string,"0");
		sprintf(minutos_string,"%d",minuto);
		strcat(tiempo_string,minutos_string);
		strcat(tiempo_string,":");
		}else{
			sprintf(minutos_string,"%d",minuto);
			strcat(tiempo_string,minutos_string);
			strcat(tiempo_string,":");
			}
	if(segundos<10){
		strcat(tiempo_string,"0");
		sprintf(minutos_string,"%d",segundos);
		strcat(tiempo_string,minutos_string);
		}else{
			sprintf(minutos_string,"%d",segundos);
			strcat(tiempo_string,minutos_string);
			}
	return tiempo_string;
}

char* horaEnStringFiltro(int tiempo){
	static char tiempo_string[20];
	char hora_string[30];
	int hora;
	if(tiempo < 3600){
		strcat(tiempo_string,"00:");
	}else{
		hora = tiempo/3600;
		if(hora<10){
			strcat(tiempo_string,"0");
			sprintf(hora_string,"%d",hora);
			strcat(tiempo_string,hora_string);
			strcat(tiempo_string,":");
			}else{
				sprintf(hora_string,"%d",hora);
				strcat(tiempo_string,":");
			}
	}

	return tiempo_string;
}
//Funcion que transforma un entero que reseprenta tiempo (en seg) a un string HH:MM:SS
//entrada: un int que contiene la cantidad de tiempo en segundos
//salida: un string que contiene la cantidad de tiempo en el formato HH:MM:SS
char* tiempoEnStringFiltro(int tiempo){
static char tiempo_string[22];
char minutos_string[20];
char* hora_string;
hora_string = horaEnStringFiltro(tiempo);
int hora, minuto, segundos;
strcat(tiempo_string,hora_string);
if(tiempo<3600){
	minuto = tiempo/60;
	segundos = tiempo%60;
	}else{
		minuto = (tiempo%3600)/60;
		segundos = (tiempo%3600)%60;
	}
if(minuto<10){
	strcat(tiempo_string,"0");
	sprintf(minutos_string,"%d",minuto);
	strcat(tiempo_string,minutos_string);
	strcat(tiempo_string,":");
	}else{
		sprintf(minutos_string,"%d",minuto);
		strcat(tiempo_string,minutos_string);
		strcat(tiempo_string,":");
		}
if(segundos<10){
	strcat(tiempo_string,"0");
	sprintf(minutos_string,"%d",segundos);
	strcat(tiempo_string,minutos_string);
	}else{
		sprintf(minutos_string,"%d",segundos);
		strcat(tiempo_string,minutos_string);
		}
return tiempo_string;
}


//funcion que se encarga de realizar la seleccion de canciones para la playlist considerando el genero de esta
// Entrada: lista, arreglo de generos, entero para id genero
// Salida: ninguna
void creaLineaOut(Lista* lista, generos* generito, int genero){

	FILE* archivo;

	int sumaDuraciones = getTiempo(lista);
	int cantidadCanciones = getLargo(lista);

	//Aqui se realiza la escritura del archivo
	archivo=fopen("playlist.out","w");
  char* duracionFinal_playlist = tiempoEnString(sumaDuraciones);
	fprintf(archivo, "%d %s %s\n",cantidadCanciones, duracionFinal_playlist, generito[genero-1].nombreGenero);

	if (!esListaVacia(lista))
  {
    Node* current = lista->head;
    while (current!=NULL)
    {
				fprintf(archivo,"%s %s %s\n",current->song->nombreCancion, current->song->duracionString, current->song->artista);
				current = current->siguiente;



			}
			fclose(archivo);

		}






}
//funcion que se encarga de realizar la seleccion de canciones para la playlist considerando el genero de esta
// Entrada: lista, arreglo de generos, entero para id genero
// Salida: ninguna
void creaLineaOutFiltrada(Lista* lista, generos* generito, int genero){
	FILE* archivo;
	int sumaDuraciones = getTiempo(lista);
	int cantidadCanciones = getLargo(lista);

	//Aqui se realiza la escritura del archivo
	archivo=fopen("playlistTienda.out","w");
  char* duracionFinal_playlist = tiempoEnStringFiltro(sumaDuraciones);
	fprintf(archivo, "%d %s %s\n",cantidadCanciones, duracionFinal_playlist, generito[genero-1].nombreGenero);

	if (!esListaVacia(lista))
  {
    Node* current = lista->head;
    while (current!=NULL)
    {
				fprintf(archivo,"%s %s %s\n",current->song->nombreCancion, current->song->duracionString, current->song->artista);
				current = current->siguiente;



			}
			fclose(archivo);

		}

		printf("Se han creado los archivos\n");






}
