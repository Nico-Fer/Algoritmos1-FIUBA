#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "juego.h"
#include "grabacion.h"
#include "ranking.h"


#define MAX_NOMBRE_RUTA 50

#define PRIMER_NIVEL  1
#define SEGUNDO_NIVEL  2
#define TERCER_NIVEL 3
#define CUARTO_NIVEL  4

#define CRITICO_REGULAR 10
#define CRITICO_BUENO 25
#define CRITICO_MALO 0

#define FALLO_LEGOLAS_MALO (VELOCIDAD_VIENTO_MINIMA/2)
#define FALLO_LEGOLAS_REGULAR (VELOCIDAD_VIENTO_MEDIA/2)
#define FALLO_LEGOLAS_BUENO (VELOCIDAD_VIENTO_MAXIMA/2)
#define FALLO_GIMLI_MALO (HUMEDAD_NOCHE/2)
#define FALLO_GIMLI_REGULAR (HUMEDAD_TARDE/2)
#define FALLO_GIMLI_BUENO (HUMEDAD_MANIANA/2)

static const int TOPE_DEFENSORES_NIVEL1 = 5;
static const int TOPE_DEFENSORES_NIVEL2 = 5;
static const int TOPE_ENANOS_NIVEL3 = 3;
static const int TOPE_ELFOS_NIVEL3 = 3;
static const int TOPE_ENANOS_NIVEL4 = 4;
static const int TOPE_ELFOS_NIVEL4 = 4;

static const int POSICION_INVALIDA = -1;

static const int MAX_ENEMIGOS_PRIMER_NIVEL =  100;
static const int MAX_ENEMIGOS_SEGUNDO_NIVEL =  150;
static const int MAX_ENEMIGOS_TERCER_NIVEL  = 400;
static const int MAX_ENEMIGOS_CUARTO_NIVEL =  500;

static const int TOPE_TERRENO_NIVEL_3_Y_4 = 20;
static const int TOPE_TERRENO_NIVEL_1_Y_2 = 15;

static const char ENTRADA='E';
static const char TORRE='T';
static const char CAMINO = ' ';
static const char ENANO='G';
static const char ELFO ='L';

static const int ORCO_MUERTO = 0;

const int RESTAR_VIDA_DEFENSOR_EXTRA = 50;

const int DIVISOR = 2;

/*
pre: Tiene que recibir un caracter.
post: Devuelve True si el caracter es valido, sino devuelve false.
*/

bool es_seleccion_valida(char seleccion){
	return((seleccion=='S')||(seleccion=='N'));
}	

/*
pre: Tiene que recibir un caracter.
post: Devuelve true si es el tipo correcto, sino devuelve false.
*/

bool es_tipo_valida(char tipo){
	return((tipo==ENANO)||(tipo==ELFO));
}	

/*
pre: Recibe a juego con todas sus estructuras validas, y el tipo de defensor.
post: Le resta vida a la torre, segun el tipo de defensor.
*/

void penalizacion_defensor_extra(juego_t* juego, char tipo){
	if(tipo==ENANO){
			(*juego).torres.resistencia_torre_1-=RESTAR_VIDA_DEFENSOR_EXTRA;
			(*juego).torres.enanos_extra-=1;
	}
	else{	
		(*juego).torres.resistencia_torre_2-=RESTAR_VIDA_DEFENSOR_EXTRA;
		(*juego).torres.elfos_extra-=1;
	}
}	

/*
pre: Recibe el tipo de defensor por parametro.
post: Asigna y valida el tipo de defensor.
*/

void seleccion_defensor_extra(char* tipo){
	printf("Selecione la clase del defensor ELFO(L) o ENANO(G). Al seleccionar elfos se le restara vida a la torre 2, mientras que el enano le resta vida a la torre1");
	scanf(" %c", tipo);
	while(!(es_tipo_valida(*tipo))){
		printf("Los unicos valientes que combaten para defender las torres son ELFOS y ENANOS");
		scanf(" %c", tipo);
	}
}	

/*
pre: Recibe a coordenada con todas sus estructuras validas y el nivel actual.
post: Valida si la posicion elegida no esta fuera del mapa.
*/
bool es_posicion_valida(coordenada_t posicion, int nivel_actual){
	if(nivel_actual==PRIMER_NIVEL || nivel_actual==SEGUNDO_NIVEL){
		return((posicion.col>=0)&&(posicion.fil>=0)&&(posicion.col<TOPE_TERRENO_NIVEL_1_Y_2)&&(posicion.fil<TOPE_TERRENO_NIVEL_1_Y_2));
	}
	else{
		return((posicion.col>=0)&&(posicion.fil>=0)&&(posicion.col<TOPE_TERRENO_NIVEL_3_Y_4)&&(posicion.fil<TOPE_TERRENO_NIVEL_3_Y_4));
	}
}



void seleccion_posicion_defensor(juego_t* juego, coordenada_t* posicion, char tipo){
	printf("Seleccione la fila donde quiere agregar su defensor: ");
	scanf(" %i", &((*posicion).fil));
	printf("Seleccione la columna donde quiere agregar su defensor: ");
	scanf(" %i", &((*posicion).col));
	while(!(es_posicion_valida(*posicion, (*juego).nivel_actual))){
			printf("Para poder pelear contra los orcos, los defensores deben de estar dentro del campo de batalla. Vuelva a introducir la fila y la columna.\n");
			scanf(" %i", &((*posicion).fil));
			scanf(" %i", &((*posicion).col));
		}
	while(agregar_defensor(&((*juego).nivel), *posicion, tipo)==POSICION_INVALIDA){
		printf("Por motivos sanitarios, los defensores no pueden estar en la misma casilla que otro defensor, ni en el camino por el que pasan los orcos. Vuelva a introducir la fila y la columna.\n");
		scanf(" %i", &((*posicion).fil));
		scanf(" %i", &((*posicion).col));
	}
}	



void agregar_defensor_extra(juego_t* juego, coordenada_t posicion){
	char tipo;
	char seleccion;
	printf("¿Desea agregar un defensor extra S/N (SI/NO)? Se le restara vida a la tore.\n");
	scanf(" %c", &seleccion);
	while(!(es_seleccion_valida(seleccion))){
		printf("Las unicas opciones validas son S/N (SI Y NO)\n");
		scanf(" %c", &seleccion);
	}	
	if(seleccion=='S'){
		seleccion_defensor_extra(&tipo);
		seleccion_posicion_defensor(juego, &posicion, tipo);
		penalizacion_defensor_extra(juego, tipo);	
	}	
}
	

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel1(juego_t* juego, coordenada_t posicion, int* enanos_ranking){
	for(int i=0; i<TOPE_DEFENSORES_NIVEL1; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
	calcular_defensas_ranking(enanos_ranking, TOPE_DEFENSORES_NIVEL1);
}

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel2(juego_t* juego, coordenada_t posicion, int* elfos_ranking){
	for(int i=0; i<TOPE_DEFENSORES_NIVEL2; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}
	calcular_defensas_ranking(elfos_ranking, TOPE_DEFENSORES_NIVEL2);	
}	

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel3(juego_t* juego, coordenada_t posicion, int* enanos_ranking, int* elfos_ranking){
	for(int i=0; i<TOPE_ENANOS_NIVEL3; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
	for(int i=0; i<TOPE_ELFOS_NIVEL3; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}
	calcular_defensas_ranking(enanos_ranking, TOPE_ENANOS_NIVEL3);
	calcular_defensas_ranking(elfos_ranking, TOPE_ELFOS_NIVEL3);
}

/*
pre: Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel4(juego_t* juego, coordenada_t posicion, int* enanos_ranking, int* elfos_ranking){
	for(int i=0; i<TOPE_ENANOS_NIVEL4; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
	for(int i=0; i<TOPE_ELFOS_NIVEL4; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}
	calcular_defensas_ranking(enanos_ranking, TOPE_ENANOS_NIVEL4);
	calcular_defensas_ranking(elfos_ranking, TOPE_ELFOS_NIVEL4);
}



void asignar_defensas_default(juego_t* juego, coordenada_t posicion, int* enanos_ranking, int* elfos_ranking){
	if((*juego).nivel_actual==PRIMER_NIVEL){
		establecer_defensa_nivel1(juego, posicion, enanos_ranking);
	}
	else if((*juego).nivel_actual==SEGUNDO_NIVEL){
		establecer_defensa_nivel2(juego, posicion, elfos_ranking);
	}
	else if((*juego).nivel_actual==TERCER_NIVEL){
		establecer_defensa_nivel3(juego, posicion, enanos_ranking, elfos_ranking);
	}
	else{
		establecer_defensa_nivel4(juego, posicion, enanos_ranking, elfos_ranking);
	}	
}	



void inicializar_torre(juego_t nivel, coordenada_t torre[MAX_CANT_TORRES]){
	switch(nivel.nivel_actual){
		case PRIMER_NIVEL:
			(torre[0]).col=COL_TORRE_OESTE;
			(torre[0]).fil=FILA_TORRE_OESTE;
		break;	
		case SEGUNDO_NIVEL:
			(torre[0]).col=COL_TORRE_ESTE;
			(torre[0]).fil=FILA_TORRE_ESTE;
		break;
		case TERCER_NIVEL:
			(torre[0]).col=COL_TORRE1_SUR;
			(torre[0]).fil=FILA_TORRE1_SUR;
			(torre[1]).col=COL_TORRE2_SUR;
			(torre[1]).fil=FILA_TORRE2_SUR;
		break;
		default:
			(torre[0]).col=COL_TORRE1_NORTE;
			(torre[0]).fil=FILA_TORRE1_NORTE;
			(torre[1]).col=COL_TORRE2_NORTE;
			(torre[1]).fil=FILA_TORRE2_NORTE;
		break;	
	}	
}	



void inicializar_entrada(juego_t nivel, coordenada_t entrada[MAX_CANT_ENTRADAS]){
	switch(nivel.nivel_actual){
		case PRIMER_NIVEL:
			(entrada[0]).col=COL_ENTRADA_ESTE;
			(entrada[0]).fil=FILA_ENTRADA_ESTE;
		break;	
		case SEGUNDO_NIVEL:
			(entrada[0]).col=COL_ENTRADA_OESTE;
			(entrada[0]).fil=FILA_ENTRADA_OESTE;
		break;
		case TERCER_NIVEL:
			(entrada[0]).col=COL_ENTRADA1_NORTE;
			(entrada[0]).fil=FILA_ENTRADA1_NORTE;
			(entrada[1]).col=COL_ENTRADA2_NORTE;
			(entrada[1]).fil=FILA_ENTRADA2_NORTE;
		break;
		default:
			(entrada[0]).col=COL_ENTRADA1_SUR;
			(entrada[0]).fil=FILA_ENTRADA1_SUR;
			(entrada[1]).col=COL_ENTRADA2_SUR;
			(entrada[1]).fil=FILA_ENTRADA2_SUR;
		break;	
	}
}	




void inicializar_max_enemigos(juego_t* juego){
	if((*juego).nivel_actual==PRIMER_NIVEL){
		(*juego).nivel.max_enemigos_nivel=MAX_ENEMIGOS_PRIMER_NIVEL;
	}
	else if((*juego).nivel_actual==SEGUNDO_NIVEL){
		(*juego).nivel.max_enemigos_nivel=MAX_ENEMIGOS_SEGUNDO_NIVEL;
	}
	else if((*juego).nivel_actual==TERCER_NIVEL){
		(*juego).nivel.max_enemigos_nivel=MAX_ENEMIGOS_TERCER_NIVEL;
	}
	else{
		(*juego).nivel.max_enemigos_nivel=MAX_ENEMIGOS_CUARTO_NIVEL;
	}	
}	



void obtener_caminos(coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t torre[MAX_CANT_TORRES], juego_t* nivel){
	if((*nivel).nivel_actual==PRIMER_NIVEL || (*nivel).nivel_actual==SEGUNDO_NIVEL){
		obtener_camino((*nivel).nivel.camino_1, &((*nivel).nivel.tope_camino_1), entrada[0], torre[0]);
	}
	else{
		obtener_camino((*nivel).nivel.camino_1, &((*nivel).nivel.tope_camino_1), entrada[0], torre[0]);
		obtener_camino((*nivel).nivel.camino_2, &((*nivel).nivel.tope_camino_2), entrada[1], torre[1]);
	}	
}



void inicializar_nivel_default(juego_t* juego, coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t torre[MAX_CANT_TORRES]){
	(*juego).nivel.tope_defensores=0;
	(*juego).nivel.tope_camino_1=0;
	(*juego).nivel.tope_camino_2=0;
	(*juego).nivel.tope_enemigos=0;
	inicializar_torre(*juego, torre);
	inicializar_entrada(*juego, entrada);
	obtener_caminos(entrada, torre, juego);
	inicializar_max_enemigos(juego);
}


void presentacion_nivel_ganado(){
	printf("===================================================================================\n");
	printf("                  Felicidades, pasaste el nivel, pero no el juego.                 \n");
	printf("Hay orcos en camino decididos a destruir esas torres, defendiendelas con tu vida!!!\n");
	printf("===================================================================================\n");
}	



void contar_orcos_muertos(int* orcos_muertos, enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos){
	for(int i=0; i<tope_enemigos; i++){
		if(enemigos[i].vida==ORCO_MUERTO){
			(*orcos_muertos)++;
		}	
	}	
}	



int jugar(juego_t* juego, coordenada_t torre[MAX_CANT_TORRES], coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t posicion, int* contador, int* orcos_muertos, char ruta_archivo_repe[MAX_NOMBRE_RUTA], int* enanos_ranking, int* elfos_ranking){
	FILE * archivo_grabacion;
	if(strcmp(ruta_archivo_repe, "vacio")!=0){
		archivo_grabacion=fopen(ruta_archivo_repe, "w");
		if(!archivo_grabacion)
			return -1;
	}	
	do{
		inicializar_nivel_default(juego, entrada, torre);
		mostrar_juego(*juego);
		detener_el_tiempo(1);
		asignar_defensas_default(juego, posicion, enanos_ranking, elfos_ranking);
		do{
			if(((*juego).nivel_actual==PRIMER_NIVEL) && ((((*juego).nivel.tope_enemigos)%25)==0) && ((*contador)<=(*juego).nivel.max_enemigos_nivel)){
				agregar_defensor_extra(juego, posicion);
			}
			else if((((*juego).nivel.tope_enemigos)%50)==0 && ((*contador)<=(*juego).nivel.max_enemigos_nivel)){
				agregar_defensor_extra(juego, posicion);
			}
			if(strcmp(ruta_archivo_repe, "vacio")!=0){
				escribir_grabacion(*juego, archivo_grabacion);
			}
			jugar_turno(juego);
			mostrar_juego(*juego);
			*contador = *contador + 1;
			detener_el_tiempo(0.5);
			system("clear");
		}while(estado_nivel((*juego).nivel)==JUGANDO && estado_juego(*juego)==JUGANDO);	
		*contador = 0;
		if(estado_nivel((*juego).nivel)==GANADO && (*juego).nivel_actual!=CUARTO_NIVEL){
			presentacion_nivel_ganado();
		}	
		contar_orcos_muertos(orcos_muertos, (*juego).nivel.enemigos, (*juego).nivel.tope_enemigos);
		(*juego).nivel_actual++;
	}while(estado_juego(*juego)==JUGANDO);
	if(strcmp(ruta_archivo_repe, "vacio")!=0){
		fclose(archivo_grabacion);
	}
	return 1;
}	




void presentacion_juego_perdido(){
	printf("=========================================================================\n");
	printf("                             Has perdido :(                              \n");
	printf("                 Los orcos festejaban al grito de A CASA.                \n");
	printf("               Pero no importa, puedes volver a intentarlo :)            \n");
	printf("=========================================================================\n");
}




void presentacion_juego_ganado(){
	printf("=========================================================================\n");
	printf("*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *\n");
	printf("                      Felicidades, has ganado :)                         \n");
	printf("  *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *  \n");
	printf("=========================================================================\n");
}



void determinar_fallo_legolas(int viento, int* fallo ){
	*fallo = viento/DIVISOR;
}



void determinar_fallo_gimli(int humedad, int* fallo ){
	*fallo = humedad/DIVISOR;
}
	


void determinar_critico(char animo, int* critico){
	if (animo==ANIMO_MALO){
		*critico=CRITICO_MALO;
	}
	else if (animo==ANIMO_REGULAR){
		*critico=CRITICO_REGULAR;
	}
	else{
		*critico=CRITICO_BUENO;
	}		
}	

void jugar_juego_default(int* orcos_muertos, char ruta_archivo_repe[MAX_NOMBRE_COMANDOS], int* enanos_ranking, int* elfos_ranking, int* vida_torre_1_ranking, int* vida_torre_2_ranking, juego_t* juego){
	srand((unsigned)time(NULL));
	int contador = 0;
	int viento=0;
	int humedad=0;
	char animo_legolas;
	char animo_gimli;
	(*juego).nivel_actual=PRIMER_NIVEL;
	animos(&viento, &humedad, &animo_legolas, &animo_gimli);
	detener_el_tiempo(5);
	system("clear");
	inicializar_juego_default(juego, viento, humedad, animo_legolas, animo_gimli);
	calcular_vida_torres(vida_torre_1_ranking, vida_torre_2_ranking, (*juego).torres.resistencia_torre_1, (*juego).torres.resistencia_torre_2);
	coordenada_t torre[MAX_CANT_TORRES];
	coordenada_t entrada[MAX_CANT_ENTRADAS];
	coordenada_t posicion;
	jugar(juego, torre, entrada, posicion, &contador, orcos_muertos, ruta_archivo_repe, enanos_ranking, elfos_ranking);
	if(estado_nivel((*juego).nivel)==GANADO){
		presentacion_juego_ganado();
	}
	else{
		presentacion_juego_perdido();
	}
}	


void mostrar_terreno(int tope_terreno, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
for(int i=0; i<(tope_terreno);i++){
		printf("%2i|", i);
		for(int j=0; j<(tope_terreno);j++){	
			printf(" %c ", terreno[i][j]);
		}
		printf("\n");
	}
}	



void presentacion_columnas(int nivel_actual){
	if(nivel_actual==PRIMER_NIVEL||nivel_actual==SEGUNDO_NIVEL){
	printf("===============================================\n");
	printf("------------DEFENDIENDO LAS TORRES-------------\n");
	printf("                                  1  1  1  1  1\n");
	printf("    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4\n");
	printf("===============================================\n");
	}	
	else{
	printf("==============================================================\n");
	printf("--------------------DEFENDIENDO LAS TORRES--------------------\n");
	printf("                                  1  1  1  1  1  1  1  1  1  1\n");
	printf("    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9\n");
	printf("==============================================================\n");
	}	
}	




void inicializar_terreno(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], int tope_terreno){
	for(int i=0; i<(tope_terreno);i++){
		for(int j=0; j<(tope_terreno);j++){
			terreno[i][j]='X';
		}
	}
}
	

	

void determinar_tope_terreno(int nivel_actual, int* tope_terreno){
	if(nivel_actual==PRIMER_NIVEL || nivel_actual==SEGUNDO_NIVEL){
		*tope_terreno = TOPE_TERRENO_NIVEL_1_Y_2;
	}
	else{
		*tope_terreno = TOPE_TERRENO_NIVEL_3_Y_4;
	}
}



void asignar_entradas(juego_t juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	terreno[juego.nivel.camino_1[0].fil][juego.nivel.camino_1[0].col]= ENTRADA;
	if(juego.nivel_actual==TERCER_NIVEL||juego.nivel_actual==CUARTO_NIVEL){
		terreno[juego.nivel.camino_2[0].fil][juego.nivel.camino_2[0].col]= ENTRADA;
	}
}



void asignar_caminos(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2){
	for(int i=0; i<(tope_camino_1);i++){
		terreno[camino_1[i].fil][camino_1[i].col]=CAMINO;
	}
	if(tope_camino_2>0){
		for(int i=0; i<(tope_camino_2);i++){
			terreno[camino_2[i].fil][camino_2[i].col]=CAMINO;
		}
	}
}	



void asignar_torres(juego_t juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	terreno[juego.nivel.camino_1[(juego.nivel.tope_camino_1) - 1].fil][juego.nivel.camino_1[(juego.nivel.tope_camino_1) - 1].col]= TORRE;
	if(juego.nivel.tope_camino_2>0){
		terreno[juego.nivel.camino_2[(juego.nivel.tope_camino_2) - 1].fil][juego.nivel.camino_2[(juego.nivel.tope_camino_2) - 1].col]= TORRE;
	}
}