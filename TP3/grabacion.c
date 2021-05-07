#include <stdio.h>
#include <string.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "utiles.h"

#define MAX_RUTA_ARCHIVO 50



void escribir_grabacion(juego_t juego, FILE * archivo_grabacion){
	fwrite(&juego, sizeof(juego_t), 1, archivo_grabacion);	
}	

/*
*pre: Recibe el archivo grabacion, la velocidad del juego y el juego con todas sus estructuras validas, pasado por parametro.
*post: Lee el archivo y muestra por pantalla el juego.
*/

void leer_grabacion(juego_t* juego, FILE * archivo_grabacion, float velocidad_juego){
	fread(juego, sizeof(juego_t), 1, archivo_grabacion);
	while(!feof(archivo_grabacion)){
		detener_el_tiempo(velocidad_juego);
		system("clear");
		mostrar_juego(*juego);
		fread(juego, sizeof(juego_t), 1, archivo_grabacion);
	}	
}	



int lectura_grabacion(char ruta_archivo[MAX_RUTA_ARCHIVO], juego_t* juego, float velocidad_juego){
	FILE * archivo_grabacion = fopen( ruta_archivo, "r");
	if(!archivo_grabacion){
		printf("Error, no se pudo abrir el archivo %s", ruta_archivo);
		return -1;
	}
	leer_grabacion(juego, archivo_grabacion, velocidad_juego);
	fclose(archivo_grabacion);
	return 1;	
}	