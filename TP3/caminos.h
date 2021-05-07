#ifndef __CAMINOS_H__
#define __CAMINOS_H__

#include <stdbool.h>

#define MAX_NOMBRE_COMANDO 60

typedef struct camino{
	int nivel;

	coordenada_t camino_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1;
	
	coordenada_t camino_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2;

}camino_t;	

/*
*pre: Recibe camino por referenica, con todas sus estructuras validas, y la ruta del archivo de caminos.
*post: Si se pudo abrir el archivo, crea los caminos y devuelve True.
* Si no se puede abrir, devuelve False.
*/

bool inicializar_creacion_camino(char ruta_archivo[MAX_NOMBRE_COMANDO], camino_t* camino);

#endif	