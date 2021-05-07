#ifndef __RANKING_H__
#define __RANKING_H__

#define MAX_NOMBRE_JUGADOR 60
#define MAX_JUGADORES 100
#define MAX_NOMBRE_ARCHIVO 100

static const int LISTAR_DEFAULT=-1;

typedef struct ranking{
	char jugador[MAX_NOMBRE_JUGADOR];
	int puntaje;
}ranking_t;	

/*
*pre: Recibe los struct jugador nuevo y jugador en ranking, con todas sus estructuras validas.
*post: Si los archivos se pudieron abrir, le pide el nombre al usuario y lo escribe en el archivo.
	   Sino, devuelve -1.	
*/

int inicializar_escritura_ranking(ranking_t jugador_nuevo, char ruta_archivo[MAX_NOMBRE_ARCHIVO]);

/*
*pre: Recibe la vida inicial de las torres, la cantidad de enanos usados en el juego, la cantidad de defensores extra elegidos por el usuario,
	  y el puntaje pasado por parametro.
*post: Determina el valor del puntaje.
*/

void determinar_puntaje(int* puntaje, int orcos_muertos, int vida_torre_1, int vida_torre_2, int enanos, int elfos, int enanos_extra, int elfos_extra);

/*
*pre: Recibe la cantidad de defensores en el nivel actual, y la cantidad de defensores total, pasada por parametro.
*post: Determina la cantidad de defesnores utilizada en el juego, para poder calcular el puntaje.
*/

void calcular_defensas_ranking(int* defensas_ranking, int defensores);

/*
*pre: Recibe la resistencia inicial de las torres, y la vidas de las torres pasadas por parametro.
*post: Determina la vida de las torres, para poder calcular el puntaje.
*/

void calcular_vida_torres(int* vida_torre_1, int* vida_torre_2, int resistencia_torre_1, int resistencia_torre_2);

/*
*pre: Recibe el nombre del archivo y la cantidad de jugadores a mostrar.
*post: Si se pudo abrir el archivo, lo lee y lo muestra por pantalla.
	   Sino. devuelve -1;
*/

int inicializar_lectura_ranking(char ruta_archivo[MAX_NOMBRE_ARCHIVO], int listar);

#endif