#ifndef __GRABACION__H__
#define __GRABACION__H__

#define MAX_RUTA_ARCHIVO 50

/*
*pre: Recibe el archivo grabacion y el juego, con todas sus estructuras validas.
*post: Escribe en el archivo, el juego.
*/

void escribir_grabacion(juego_t juego, FILE * archivo_grabacion);

/*
*pre: Recibe la ruta del archivo, la velocidad el juego, y el juego con todas sus estructuras validas, pasado por parametro.
*post: Si el archivo se pudo abrir, lee el archivo grabacion.
	   Sino, devuelve -1.
*/

int lectura_grabacion(char ruta_archivo[MAX_RUTA_ARCHIVO], juego_t* juego, float velocidad_juego);

#endif