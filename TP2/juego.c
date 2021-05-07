#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"


const int RESTAR_VIDA_DEFENSOR_EXTRA = 50;
static const char ENANO='G';
static const char ELFO ='L';
#define PRIMER_NIVEL   1
#define SEGUNDO_NIVEL   2
#define TERCER_NIVEL  3
#define CUARTO_NIVEL   4
static const int TOPE_DEFENSORES_NIVEL1 = 5;
static const int TOPE_DEFENSORES_NIVEL2 = 5;
static const int TOPE_ENANOS_NIVEL3 = 3;
static const int TOPE_ELFOS_NIVEL3 = 3;
static const int TOPE_ENANOS_NIVEL4 = 4;
static const int TOPE_ELFOS_NIVEL4 = 4;
static const int MAX_CANT_TORRES =  2;
static const int MAX_CANT_ENTRADAS =  2;
static const int GANADO  = 1;
static const int JUGANDO  = 0;
static const int POSICION_INVALIDA = -1;
static const int FILA_TORRE1_SUR =19; 
static const int COL_TORRE1_SUR  =8;
static const int FILA_TORRE2_SUR = 19;
static const int COL_TORRE2_SUR = 11;
static const int FILA_TORRE1_NORTE = 0;
static const int COL_TORRE1_NORTE = 5;
static const int FILA_TORRE2_NORTE = 0;
static const int COL_TORRE2_NORTE = 11;
static const int FILA_TORRE_ESTE = 10;
static const int COL_TORRE_ESTE = 14;
static const int FILA_TORRE_OESTE = 6;
static const int COL_TORRE_OESTE = 0;
static const int FILA_ENTRADA1_SUR = 19;
static const int COL_ENTRADA1_SUR = 2;
static const int FILA_ENTRADA2_SUR = 19;
static const int COL_ENTRADA2_SUR = 14;
static const int FILA_ENTRADA1_NORTE = 0;
static const int COL_ENTRADA1_NORTE  =3;
static const int FILA_ENTRADA2_NORTE = 0;
static const int COL_ENTRADA2_NORTE = 16;
static const int FILA_ENTRADA_ESTE = 2;
static const int COL_ENTRADA_ESTE = 14;
static const int FILA_ENTRADA_OESTE = 3;
static const int COL_ENTRADA_OESTE = 0;
static const int MAX_ENEMIGOS_PRIMER_NIVEL =  100;
static const int MAX_ENEMIGOS_SEGUNDO_NIVEL =  150;
static const int MAX_ENEMIGOS_TERCER_NIVEL  = 400;
static const int MAX_ENEMIGOS_CUARTO_NIVEL =  500;
static const int TOPE_TERRENO_NIVEL_3_Y_4 = 20;
static const int TOPE_TERRENO_NIVEL_1_Y_2 = 15;


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

/*
pre: Recibe a juego y posicion con todas sus estructuras validas, y el tipo de defensor.
post: Asigna la posicion al defensor.
*/

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

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor, si asi es deseado.
*/

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

void establecer_defensa_nivel1(juego_t* juego, coordenada_t posicion){
	for(int i=0; i<TOPE_DEFENSORES_NIVEL1; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
}

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel2(juego_t* juego, coordenada_t posicion){
	for(int i=0; i<TOPE_DEFENSORES_NIVEL2; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}	
}	

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel3(juego_t* juego, coordenada_t posicion){
	for(int i=0; i<TOPE_ENANOS_NIVEL3; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
	for(int i=0; i<TOPE_ELFOS_NIVEL3; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}
}

/*
pre: Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor.
*/

void establecer_defensa_nivel4(juego_t* juego, coordenada_t posicion){
	for(int i=0; i<TOPE_ENANOS_NIVEL4; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
	for(int i=0; i<TOPE_ELFOS_NIVEL4; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}
}

/*
pre: Recibe el juego con todas sus estructuras validas.
post: Asigna las defensas segun el nivel.
*/

void asignar_defensas(juego_t* juego, coordenada_t posicion){
	if((*juego).nivel_actual==PRIMER_NIVEL){
		establecer_defensa_nivel1(juego, posicion);
	}
	else if((*juego).nivel_actual==SEGUNDO_NIVEL){
		establecer_defensa_nivel2(juego, posicion);
	}
	else if((*juego).nivel_actual==TERCER_NIVEL){
		establecer_defensa_nivel3(juego, posicion);
	}
	else{
		establecer_defensa_nivel4(juego, posicion);
	}	
}	

/*
pre: Recibe el nivel con todas sus estructuras validas.
post: Le asigna las coordenadas a las torres segun el nivel.
*/

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

/*
pre: Recibe nivel con todas sus estructuras validas.
post: Le asigna las coordenadas a las entradas segun el nivel.
*/

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


/*
pre: Recibe a juego con todas sus estructuras validas.
post: Le asigna el maximo de enemigos, dependiendo el nivel.
*/

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

/*
pre: Recibe el nivel con todas sus estructuras validas, las coordenadas da la torre y la entrada deben ser validas.
post: Generara un camino desde la entrada hasta la torre.
*/

void obtener_caminos(coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t torre[MAX_CANT_TORRES], juego_t* nivel){
	if((*nivel).nivel_actual==PRIMER_NIVEL || (*nivel).nivel_actual==SEGUNDO_NIVEL){
		obtener_camino((*nivel).nivel.camino_1, &((*nivel).nivel.tope_camino_1), entrada[0], torre[0]);
	}
	else{
		obtener_camino((*nivel).nivel.camino_1, &((*nivel).nivel.tope_camino_1), entrada[0], torre[0]);
		obtener_camino((*nivel).nivel.camino_2, &((*nivel).nivel.tope_camino_2), entrada[1], torre[1]);
	}	
}

/*
pre: Recibe a juego con todas sus estructuras validas y los vectores entrada y torre.
post: Inicializara el nivel correspondiente, asignandole la posicion a las torres y entradas, obteniendo el camino,
*     inicializando los topes en 0 e inicializando al maximo de enemigos.
*/

void inicializar_nivel(juego_t* juego, coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t torre[MAX_CANT_TORRES]){
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


void jugar_juego(juego_t* juego, coordenada_t torre[MAX_CANT_TORRES], coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t posicion, int* contador){
	do{
		inicializar_nivel(juego, entrada, torre);
		mostrar_juego(*juego);
		detener_el_tiempo(1);
		asignar_defensas(juego, posicion);
		do{
			if(((*juego).nivel_actual==PRIMER_NIVEL) && ((((*juego).nivel.tope_enemigos)%25)==0) && ((*contador)<=(*juego).nivel.max_enemigos_nivel)){
				agregar_defensor_extra(juego, posicion);
			}
			else if((((*juego).nivel.tope_enemigos)%50)==0 && ((*contador)<=(*juego).nivel.max_enemigos_nivel)){
				agregar_defensor_extra(juego, posicion);
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
		(*juego).nivel_actual++;
	}while(estado_juego(*juego)==JUGANDO);
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
	



int main(){
	srand((unsigned)time(NULL));
	int contador = 0;
	int viento=0;
	int humedad=0;
	char animo_legolas;
	char animo_gimli;
	juego_t juego;
	juego.nivel_actual=PRIMER_NIVEL;
	animos(&viento, &humedad, &animo_legolas, &animo_gimli);
	detener_el_tiempo(5);
	system("clear");
	inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli);
	coordenada_t torre[MAX_CANT_TORRES];
	coordenada_t entrada[MAX_CANT_ENTRADAS];
	coordenada_t posicion;
	jugar_juego(&juego, torre, entrada, posicion, &contador);
	if(estado_nivel(juego.nivel)==GANADO){
		presentacion_juego_ganado();
	}
	else{
		presentacion_juego_perdido();
	}	
	return 0;  

}
