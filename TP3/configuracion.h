#ifndef __CONFIGURACION_H__
#define __CONFIGURACION_H__

#include <stdbool.h>

#define MAX_NIVELES 4
#define MAX_NOMBRE_RUTA 60
#define MAX_NOMBRE_COMANDO 60
#define MAX_NOMBRE 50

#define ENANOS "Enanos"
#define ELFOS "Elfos"


static const int TORRE_1=1;
static const int TORRE_2=2;

static const int MAX_ENANOS_EXTRA = 5;
static const int MAX_ELFOS_EXTRA = 5;

typedef struct configuracion{
	int resistencia_torre_1;
	int resistencia_torre_2;

	int cant_enanos[MAX_NIVELES];
	int cant_elfos[MAX_NIVELES];
	int cant_enanos_extra;
	int cant_elfos_extra;

	int critico_enanos;
	int critico_elfos;
	int fallo_enanos;
	int fallo_elfos;

	float velocidad_juego;

	char ruta_camino[MAX_NOMBRE_RUTA];

}configuracion_t;

/*
*pre: Recibe configuracion, con todas sus etructuras validas, pasado por parametro, y la ruta del archivo de configuracion.
*post: Si el archivo se pudo abrir, valida y asigna los valores al struct configuracion. Luego escribe el archivo, y devuelve true.
*Si no se pudo abrir el archivo devuelve false.
*/

bool inicializar_creacion_config(char ruta_archivo[MAX_NOMBRE_COMANDO], configuracion_t* configuracion);

/*
*pre: Recibe configuracion, con todas sus estructuras validas, pasada por parametro, y le ruta del archivo camino.
*post: Si el archivo se pudo abrir, lee el arhivo y le asigna los valoras a cada campo de configuracion, y devuelve true.
*Si el archivo no se pudo abrir, devuelve false.
*/

bool leer_configuracion(char ruta_archivo[MAX_NOMBRE_COMANDO], configuracion_t* configuracion);

#endif