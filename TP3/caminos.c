#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "juego.h"
#include "caminos.h"

#define PRIMER_NIVEL   1
#define SEGUNDO_NIVEL   2
#define TERCER_NIVEL  3
#define CUARTO_NIVEL   4

const int TORRE_1=1;
const int TORRE_2=2;

const char ARRIBA = 'W';
const char ABAJO = 'S';
const char IZQUIERDA = 'A';
const char DERECHA = 'D';
const char TERMINAR = 'T';
const char OTRO='O';
const char CAMINO= ' ';

const int TOPE_TERRENO_MINIMO = 0;

static const int TOPE_CAMINO_MINIMO = 0;

static const char TORRE='T';
static const char ENTRADA='E';



/*
*pre:Recibe un vector de caminos, con todas sus estructuras validas, el nivel en el que se esta jugando, el camino elegido,
*el tope de ese camino, y el archivo de caminos.
*post: Escribe el archivo camino, con los valores ,ya validados y asignados, de camino.
*/

void escribir_camino(coordenada_t camino[MAX_LONGITUD_CAMINO], int nivel, int numero_camino, int tope_camino, FILE * archivo_camino){
	fprintf(archivo_camino, "NIVEL=%i\n", nivel);
	fprintf(archivo_camino, "CAMINO=%i\n", numero_camino);
	for(int i=0; i<tope_camino; i++){
		fprintf(archivo_camino, "%i;%i\n", camino[i].fil, camino[i].col);
	}	
}		


/*
*pre: Recibe los caminos con todas sus estructuras validas, el tope del camino_2 y una matriz que representa el mapa.
*post: Le asigna al terreno la posicion de la entrada.
*/

void asignar_entrada(coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], int tope_camino_1){
	if(tope_camino_1>TOPE_CAMINO_MINIMO){
		terreno[camino_1[0].fil][camino_1[0].col]= ENTRADA;
	}
	if(tope_camino_2>TOPE_CAMINO_MINIMO){
		terreno[camino_2[0].fil][camino_2[0].col]= ENTRADA;
	}
}

/*
*pre:Recibe los caminos con todas sus estructuras validas,sus topes y una matriz que representa el mapa.
*post: Le asigna al trreno la posicion de los caminos.
*/

void asignar_camino(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_1, int tope_camino_2){
	for(int i=1; i<(tope_camino_1);i++){
		terreno[camino_1[i].fil][camino_1[i].col]=CAMINO;
	}
	if(tope_camino_2>TOPE_CAMINO_MINIMO){
		for(int i=0; i<(tope_camino_2);i++){
			terreno[camino_2[i].fil][camino_2[i].col]=CAMINO;
		}
	}
}

/*
*pre:Recibe los caminos con todas sus estructuras validas, sus topes y una matriz que representa el mapa.
*post: Le asigna al terreno la posicion de la torre.
*/

void asignar_torre(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_1, int tope_camino_2){
	if((tope_camino_1 - 2)>= TOPE_TERRENO_MINIMO){
		terreno[camino_1[(tope_camino_1) -1].fil][camino_1[(tope_camino_1) - 1].col]= TORRE;
	}
	if((tope_camino_2 - 2)>= TOPE_TERRENO_MINIMO){
		terreno[camino_2[(tope_camino_2) -1].fil][camino_2[(tope_camino_2) - 1].col]= TORRE;
	}
}

/*
*pre: Recibe los caminos con todas sus estructuras validas, sus topes, una matriz que representa el mapa y el tope del terreno.
*post: Muestra por pantalla el mapa del juego.
*/

void guia_camino(int tope_terreno, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_1, int tope_camino_2, camino_t camino){
	inicializar_terreno(terreno, tope_terreno);
	asignar_camino(terreno, camino_1, camino_2, tope_camino_1, tope_camino_2);
	asignar_entrada(camino_1, camino_2, tope_camino_2, terreno, tope_camino_1);
	asignar_torre(terreno, camino_1, camino_2, tope_camino_1, tope_camino_2);
	presentacion_columnas(camino.nivel);
	mostrar_terreno(tope_terreno, terreno);
}	

/*
*pre: Recibe el tope del terreno y la posicion de la entrada, ingresada por el usuario.
*post: Devuelve True si el valor asignado es valido, sino devuelve False.
*/

bool es_entrada_valida(int posicion, int tope_terreno){
	return((posicion>=0) && (posicion<tope_terreno));	
}	

/*
*pre: Recibe el tope del terreno y la fila de la entrada, pasada por parametro.
*post: Asigna la fila de la entrada, ya validada.
*/

void preguntar_fila_entrada(int* fila, int tope_terreno){
	int contador=0;
 	printf("Seleccione la fila de la entrada \n");
	scanf("%i", fila);
	while(!es_entrada_valida(*fila, tope_terreno)){
		contador++;
		printf("La fila debe estar dentro del terreno \n");
		scanf("%i", fila);
		printf("%i", contador);
	}	
}	

/*
*pre: Recibe el tope del terreno y la posicion de la columna pasada por parametro.
*post: Aigna la columna de la entrada, ya validada.
*/

void preguntar_columna_entrada(int* columna, int tope_terreno){
 	printf("Seleccione la columna de la entrada \n");
	scanf("%i", columna);
	while(!es_entrada_valida(*columna, tope_terreno)){
		printf("La columna debe estar dentro del terreno \n");
		scanf("%i", columna);
	}	
}

/*
*pre: Recibe un vector de coordenadas, con todas sus estructuras validas, el tope del terreno, y el tope del vector camino, pasado por parametro.
*post: Asigna la posicion de la entrada.
*/

void determinar_entrada(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_terreno, int* tope_camino){
	preguntar_fila_entrada(&(camino[*tope_camino].fil), tope_terreno);
	preguntar_columna_entrada(&(camino[*tope_camino].col), tope_terreno);
	(*tope_camino)++;
}	

void mostrar_guia_generar_caminos(){
	printf("Para poder ir generando el camino es necesario saber el funcionamiento de 5 caracteres:\n");
	printf("W: Arriba.\n");
	printf("S: Abajo.\n");
	printf("D: Derecha.\n");
	printf("A: Izquierda.\n");
	printf("T: Finalizar el camino y establecer la torre.\n");
}	

/*
*pre: Recibe el movimiento sellecionado por el usuario.
*post: Devuelve True si el caracter seleccionado es valido, sino devuelve False.
*/

bool es_movimiento_valido(char movimiento){
	return((movimiento==ARRIBA) || (movimiento==ABAJO) || (movimiento==DERECHA) || (movimiento==IZQUIERDA) || (movimiento==TERMINAR));
}	

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas y el tope del camino.
*post: Devuelve True si el movimiento se puede ejecutar, sino devuelve False.
*/

bool es_arriba_valida(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	return( (camino[tope_camino -1].fil -1) >= 0);
}	

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas, el topde del terreno y el tope del camino.
*post: Devuelve True si el movimiento se puede ejecutar, sino devuelve False.
*/

bool es_abajo_valido(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_terreno, int tope_camino){
		return((camino[tope_camino -1].fil +1)<tope_terreno);
}

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas, el tope del terreno y el tope del camino.
*post: Devuelve True si el movimiento se puede ejecutar, sino devuelve False.
*/

bool es_derecha_valida(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_terreno, int tope_camino){
	return((camino[tope_camino -1].col + 1)<tope_terreno);
}

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas y el tope del camino.
*post: Devuelve True si el movimiento se puede ejecutar, sino devuelve False.
*/

bool es_izquierda_valida(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	return( (camino[tope_camino -1].col -1)>=0 );
}	
	

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas y el tope del camino, pasado por parametro.
*post: Asigna un valor al camino, de la cual esta una fila arriba de la posicion anterior.
*/

void moverse_arriba(coordenada_t camino[MAX_LONGITUD_CAMINO], int* tope_camino){
	camino[*tope_camino].fil= camino[*tope_camino - 1].fil -1;
	camino[*tope_camino].col= camino[*tope_camino - 1].col;
	(*tope_camino)++;
}	

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas y el tope del camino, pasado por parametro.
*post: Asigna un valor al camino, de la cual esta una fila abajo de la posicion anterior.
*/

void moverse_abajo(coordenada_t camino[MAX_LONGITUD_CAMINO], int* tope_camino){
	camino[*tope_camino].fil= camino[*tope_camino - 1].fil +1;
	camino[*tope_camino].col= camino[*tope_camino - 1].col;
	(*tope_camino)++;
}

/*
*pre:Recibe un vector de coordenadas con todas sus etructuras validas y el tope del camino, pasado por parametro.
*post: Asigna un valor al camino, de la cual esta una columna a la derecha de la posicion anterior.
*/

void moverse_derecha(coordenada_t camino[MAX_LONGITUD_CAMINO], int* tope_camino){
	camino[*tope_camino].col= camino[*tope_camino - 1].col + 1;
	camino[*tope_camino].fil= camino[*tope_camino - 1].fil;
	(*tope_camino)++;
}

/*
*pre: Recibe un vector de coordenadas con todas sus etructuras validas y el tope del camino, pasado por parametro.
*post: Asigna un valor al camino, de la cual esta una columna a la izquierda de la posicion anterior.
*/

void moverse_izquierda(coordenada_t camino[MAX_LONGITUD_CAMINO], int* tope_camino){
	camino[*tope_camino].col= camino[*tope_camino - 1].col - 1;
	camino[*tope_camino].fil= camino[*tope_camino - 1].fil;
	(*tope_camino)++;
}	


/*
*pre: Recibe un vector de coordenadas con todas sus estructuras validas, el tope del terreno, el tope del camino y el movimiento elegido por el usuario.
*post: Devuelve un booleano, donde su valor depende del movimiento seleccionado.
*/

bool puede_moverse(char movimiento, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_terreno, int tope_camino){
	bool puede_moverse = false;
	if(movimiento==ARRIBA){
		puede_moverse = es_arriba_valida(camino, tope_camino);
	}	
	else if(movimiento==ABAJO){
		puede_moverse = es_abajo_valido(camino, tope_terreno, tope_camino);
	}
	else if(movimiento==DERECHA){
		puede_moverse = es_derecha_valida(camino, tope_terreno, tope_camino);
	}
	else if(movimiento==IZQUIERDA){
		puede_moverse = es_izquierda_valida(camino, tope_camino);
	}
	else{ 
		puede_moverse = true;
	}	
	return puede_moverse;
}	

/*
*pre: Recibe un vector de coordenadas, con todas sus estructuras validas
*post: Realiza el movimiento elegido por el usuario, ya validado.
*/

void moverse(char* movimiento, coordenada_t camino[MAX_LONGITUD_CAMINO], int* tope_camino){
	if(*movimiento==ARRIBA){	
		moverse_arriba(camino, tope_camino);
	}
	else if(*movimiento==ABAJO){	
		moverse_abajo(camino, tope_camino);
	}
	else if(*movimiento==DERECHA){	
		moverse_derecha(camino, tope_camino);
	}
	else if(*movimiento==IZQUIERDA){	
		moverse_izquierda(camino, tope_camino);
	}
	else{
		*movimiento=TERMINAR;
	}
}	

/*
*pre: Recibe un vector de coordenadas con todas sus estructuras validas, el tope del camino y del terreno, y el movimineto pasado por parametro.
*post: Valida el movimiento elegido por el usuario. 
*/

void validar_movimiento(char* movimiento, int tope_terreno, int tope_camino, coordenada_t camino[MAX_LONGITUD_CAMINO]){
	printf("Seleccione el movimiento que quiere hacer");
	scanf(" %c", movimiento);
	while(!es_movimiento_valido(*movimiento)){
		printf("Las unicas teclas validas son W, A, S, D y T.");
		scanf(" %c", movimiento);
	}
	while(!puede_moverse(*movimiento, camino, tope_terreno, tope_camino)){
        printf("El camino debe estar dentro del mapa.");
        scanf(" %c", movimiento);
    } 
}	

/*
*pre: Recibe los caminos con todas sus estructuras validas, el terreno ,su tope, y el tope de los caminos pasados por parametro.
*post: Genera el camino.
*/

void generar_camino(int tope_terreno, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int* tope_camino_1, int* tope_camino_2, camino_t camino){
	char movimiento = OTRO;
	mostrar_guia_generar_caminos();
	while(movimiento!=TERMINAR){
		guia_camino(tope_terreno, terreno, camino_1, camino_2, *tope_camino_1, *tope_camino_2, camino);
		validar_movimiento(&movimiento, tope_terreno, *tope_camino_1, camino_1);
		moverse(&movimiento, camino_1, tope_camino_1);
		system("clear");
	}	
	movimiento = OTRO;
	if(*tope_camino_2>TOPE_CAMINO_MINIMO){
		while(movimiento!=TERMINAR){
			guia_camino(tope_terreno, terreno, camino_1, camino_2, *tope_camino_1, *tope_camino_2, camino);
			validar_movimiento(&movimiento, tope_terreno, *tope_camino_2, camino_2);
			moverse(&movimiento, camino_2, tope_camino_2);
			system("clear");
		}
	}	
}	

/*
*pre: Recibe camino, pasado por referancia, con todas sus estructuras validas, el terreno y su tope, pasado por referencia.
*post: Determina el tope del terreno y la posicion de la entrada.
*/

void inicializar_nivel_camino(camino_t* camino, int* tope_terreno, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	(*camino).tope_camino_1 = 0;
	(*camino).tope_camino_2 = 0;
	determinar_tope_terreno((*camino).nivel, tope_terreno);
	guia_camino(*tope_terreno, terreno, (*camino).camino_1, (*camino).camino_2, (*camino).tope_camino_1, (*camino).tope_camino_2, *camino);
	determinar_entrada((*camino).camino_1, *tope_terreno, &((*camino).tope_camino_1));
	if(((*camino).nivel == TERCER_NIVEL) || ((*camino).nivel == CUARTO_NIVEL)){
		determinar_entrada((*camino).camino_2, *tope_terreno, &((*camino).tope_camino_2));
	}
}	

/*
*pre: Recibe camino por referencia, con todas sus estructuras validas, y el archivo del camino.
*post: Crea los caminos de todos los niveles.
*/

void crear_camino(camino_t* camino, FILE * archivo_camino){
	char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO];
	int tope_terreno;
	for(; (*camino).nivel <= CUARTO_NIVEL; (*camino).nivel++){
		inicializar_nivel_camino(camino, &tope_terreno, terreno);
		generar_camino(tope_terreno, terreno, (*camino).camino_1, (*camino).camino_2, &((*camino).tope_camino_1), &((*camino).tope_camino_2), *camino);
		escribir_camino((*camino).camino_1, (*camino).nivel, 1, (*camino).tope_camino_1, archivo_camino);
		if((*camino).tope_camino_2>TOPE_CAMINO_MINIMO){
			escribir_camino((*camino).camino_2, (*camino).nivel, 2, (*camino).tope_camino_2, archivo_camino);
		}
	}
}


/*
*pre: Recibe camino por referenica, con todas sus estructuras validas, y la ruta del archivo de caminos.
*post: Si se pudo abrir el archivo, crea los caminos y devuelve True.
* Si no se puede abrir, devuelve False.
*/

bool inicializar_creacion_camino(char ruta_archivo[MAX_NOMBRE_COMANDO], camino_t* camino){	
	FILE * archivo_camino = fopen(ruta_archivo, "w");
	if(!archivo_camino){
		printf("Error al abrir el archivo %s.\n", ruta_archivo);
		return false;
	}	
	crear_camino(camino, archivo_camino);
	fclose(archivo_camino);
	return true;
}