#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "utiles.h"
#include "juego.h"
#include "animos.h"


const int TOPE_CAMINO_MINIMO = 0;

const int FALLO=0;
const int ATAQUE_LETAL_GIMLI = 100;
const int ATAQUE_GIMLI=60;
const int ATAQUE_LETAL_LEGOLAS = 70;
const int ATAQUE_LEGOLAS=30;
const int VIDA_MINIMA_ORCO = 200;

const int CAMINO_1=1;
const int CAMINO_2=2;

const int ORCO_MUERTO = 0;

const int MAX_RANGO_ENANO = 1;
const int MAX_RANGO_ELFO = 3;

const char ORCO= 'O';
static const char ENANO='G';
static const char ELFO ='L';

static const int PRIMER_NIVEL  = 1;
static const int SEGUNDO_NIVEL  = 2;
static const int TERCER_NIVEL =  3;
static const int CUARTO_NIVEL  = 4;

static const int POSICION_INVALIDA = -1;
static const int POSICION_VALIDA = 0;

static const int FUERZA_ENANO  = 60;
static const int FUERZA_ELFO  = 30;


#define MAX_TROPAS_EXTRA 10
	


void inicializar_juego_default(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli){
	(*juego).torres.resistencia_torre_1=MAX_RESISTENCIA_TORRE;
	(*juego).torres.resistencia_torre_2=MAX_RESISTENCIA_TORRE;
	(*juego).torres.enanos_extra=MAX_TROPAS_EXTRA;
	(*juego).torres.elfos_extra=MAX_TROPAS_EXTRA;
	determinar_critico(animo_legolas, &((*juego).critico_legolas));
	determinar_critico(animo_gimli, &((*juego).critico_gimli));
	determinar_fallo_legolas(viento,&((*juego).fallo_legolas));
	determinar_fallo_gimli(humedad,&((*juego).fallo_gimli));
	(*juego).nivel_actual=1;
}


/*
pre:Recibe el juego con todas sus estructuras validas.
post: Muestra por pantalla la vida que tienen las torres.
*/

void mostrar_vida_torre(juego_t juego){
	printf("La vida de la Torre1 es: %i \n", juego.torres.resistencia_torre_1);
	if(juego.nivel_actual==TERCER_NIVEL||juego.nivel_actual==CUARTO_NIVEL){
		printf("La vida de la Torre2 es: %i \n", juego.torres.resistencia_torre_2);
	}
}

/*
pre:Recibe el juego con todas sus estructuras validas.
post: Muestra por pantalla el porcentaje de critico de los defensores.
*/

void mostrar_criticos(juego_t juego){
	printf("La probabilidad de critico de los Enanos es: %i\n", juego.critico_gimli);
	printf("La probabilidad de critico de los Elfos es: %i\n", juego.critico_legolas);
}	

/*
pre: Recibe el juego con todas sus estructuras validas.
post: Muestra por pantalla el porcentaje de fallo de los defensores.
*/

void mostrar_fallos(juego_t juego){
	printf("La probabilidad de fallo de los Enanos es: %i\n", juego.fallo_gimli);
	printf("La probabilidad de fallo de los Elfos es: %i\n", juego.fallo_legolas);
}


/*
pre: Recibe a defensores con todas sus estructuras validas.
post: Le asigna un carater a la matriz donde se encuentran los defensores.
*/

void mostrar_defensores(defensor_t defensores[MAX_DEFENSORES], int tope_defensores, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	for(int i=0; i<(tope_defensores); i++){	
		if(defensores[i].tipo == ENANO){
			terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = ENANO;
		}
		else{
			terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = ELFO;
		}	
	}
}

/*
pre: Recibe las coordenadas con todas sus estructuras validas.
post:Le asigna un carater a la matriz donde se encuentran los orcos en camino.
*/

void mostrar_orcos(coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2, enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]){
	for(int i=0; i < tope_enemigos; i++){	
		if((enemigos[i].pos_en_camino>0) && (enemigos[i].vida>0)){
			if(enemigos[i].camino == CAMINO_1){
				terreno[camino_1[enemigos[i].pos_en_camino].fil][camino_1[enemigos[i].pos_en_camino].col] = ORCO;
			}
			else{
				terreno[camino_2[enemigos[i].pos_en_camino].fil][camino_2[enemigos[i].pos_en_camino].col] = ORCO;
			}	
		}	
	}
}


void mostrar_juego(juego_t juego){
	char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO];
	int tope_terreno;
	determinar_tope_terreno(juego.nivel_actual, &tope_terreno);
	inicializar_terreno(terreno, tope_terreno);
	mostrar_vida_torre(juego);
	mostrar_criticos(juego);
	mostrar_fallos(juego);
	asignar_caminos(terreno, juego.nivel.camino_1, juego.nivel.tope_camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_2);
	asignar_torres(juego, terreno);
	asignar_entradas(juego, terreno);
	mostrar_defensores(juego.nivel.defensores, juego.nivel.tope_defensores, terreno);
	mostrar_orcos(juego.nivel.camino_1, juego.nivel.tope_camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_2, juego.nivel.enemigos, juego.nivel.tope_enemigos, terreno);
	presentacion_columnas(juego.nivel_actual);
	mostrar_terreno(tope_terreno, terreno);
}
	

/*
pre: Recibe a defensor y enemigo con todas sus estructuras validas.
post: Devuelve True si esta en el rango del enano, sino, devuelve False.
*/

bool esta_en_rango_enano(coordenada_t defensor, coordenada_t enemigo){
	return((abs(defensor.fil - enemigo.fil)<=MAX_RANGO_ENANO)&&(abs(defensor.col - enemigo.col)<=MAX_RANGO_ENANO));
}	

	

/*
pre:Recibe el juego con todas sus estructuras validas.
post: Devuelve el valor de la fuerza del enano.
*/

int determinar_ataque_enano(juego_t* juego){
	int critico = rand() % 101;
	int fallo = rand() % 101;
	int fuerza;
	if(fallo <= ((*juego).fallo_gimli)){
		fuerza = FALLO;
	}
	else if(critico <= ((*juego).critico_gimli)){
		fuerza = ATAQUE_LETAL_GIMLI;
	}
	else{
		fuerza = ATAQUE_GIMLI;
	}
	return fuerza;
}	

/*
pre: Recibe el juego con todas sus estructuras validas y el auxiliar que representa la posicion del elemento del vector enemigos.
post: Le resta la vida al orco, segun la fuerza del ataque del enano.
*/

void implementar_ataque_enano(juego_t* juego, int aux){
	(*juego).nivel.enemigos[aux].vida=((*juego).nivel.enemigos[aux].vida) - determinar_ataque_enano(juego);
	if ((*juego).nivel.enemigos[aux].vida<=0){
		(*juego).nivel.enemigos[aux].vida=ORCO_MUERTO;
	}
}	


 
/*
pre: Recibe el juego con todas sus estructuras validas y el defensor, que representa la posicion del elemento del vector defensores.
post: Dejara el juego en el estado correspondiete y jugara el turno de un solo enano.
*/

void jugar_turno_enano(juego_t* juego, int defensor){
	int aux=0;
	bool esta_en_rango = false;
	while( (esta_en_rango==false) && (aux<(*juego).nivel.tope_enemigos)){
		if((*juego).nivel.enemigos[aux].camino == CAMINO_1){
			esta_en_rango=esta_en_rango_enano(((*juego).nivel.defensores[defensor].posicion), (*juego).nivel.camino_1[(*juego).nivel.enemigos[aux].pos_en_camino]);
		}	
		else{
			esta_en_rango=esta_en_rango_enano(((*juego).nivel.defensores[defensor].posicion), (*juego).nivel.camino_2[(*juego).nivel.enemigos[aux].pos_en_camino]);
		}	
		if((*juego).nivel.enemigos[aux].vida==ORCO_MUERTO){
			esta_en_rango=false;
		}	
		if(esta_en_rango==true){
			implementar_ataque_enano(juego, aux);
		}
		aux++;
	}		
}	

/*
pre: Recibe a defensor y enemigo con todas sus estructuras validas.
post: Devuelve True si esta en el rango del elfo, sino, devuelve False.
*/

bool esta_en_rango_elfo(coordenada_t defensor, coordenada_t enemigo){
	return(((abs(defensor.fil - enemigo.fil))+(abs(defensor.col - enemigo.col)))<=MAX_RANGO_ELFO);
}

/*
pre: Recibe el juego con todas sus estructuras validas.
post: Devuelve el valor del ataque del elfo.
*/

int determinar_ataque_elfo(juego_t* juego){
	int critico = rand() % 101;
	int fallo = rand() % 101;
	int fuerza;
	if(fallo <= ((*juego).fallo_legolas)){
		fuerza = FALLO;
	}
	else if(critico <= ((*juego).critico_legolas)){
		fuerza = ATAQUE_LETAL_LEGOLAS;
	}
	else{
		fuerza = ATAQUE_LEGOLAS;
	}
	return fuerza;
}	

	

/*
pre: Recibe el juego con todas sus estructuras validas y el auxiliar que representa la posicion del elemento del vector enemigos.
post: Le resta la vida al orco, segun la fuerza del ataque del elfo.
*/

void implementar_ataque_elfo(juego_t* juego, int aux){
	(*juego).nivel.enemigos[aux].vida=((*juego).nivel.enemigos[aux].vida) - determinar_ataque_elfo(juego);
	if ((*juego).nivel.enemigos[aux].vida<=0){
		(*juego).nivel.enemigos[aux].vida=ORCO_MUERTO;
	}
}
	

/*
pre: Recibe el juego con todas sus estructuras validas y el contador defensor que representa el elemento del vector defensores.
post: Jugara el turno de un solo elfo y dejara el juego en el estado correspondiete .
*/

void jugar_turno_elfo(juego_t* juego, int defensor){
	bool esta_en_rango = false;
	int aux=0;
	for(; aux<((*juego).nivel.tope_enemigos); aux++){
		if((*juego).nivel.enemigos[aux].camino == CAMINO_1){
			esta_en_rango=esta_en_rango_elfo(((*juego).nivel.defensores[defensor].posicion), (*juego).nivel.camino_1[(*juego).nivel.enemigos[aux].pos_en_camino]);
		}	
		else{
			esta_en_rango=esta_en_rango_enano(((*juego).nivel.defensores[defensor].posicion), (*juego).nivel.camino_2[(*juego).nivel.enemigos[aux].pos_en_camino]);
		}	
		if((*juego).nivel.enemigos[aux].vida==ORCO_MUERTO){
			esta_en_rango=false;
		}	
		if(esta_en_rango==true){
			implementar_ataque_enano(juego, aux);
		}	
	}	
}

	

/*
pre: Recibe el juego con todas sus estructuras validas, la posicion del elemento del vector enemigos y la torre.
post: Si el orco llega vivo a la torre, le resta vida a la torre correspondiente y el orco muere.
*/

void ataque_orco(juego_t* juego, int orco, int torre){
	if(torre==1){
		(*juego).torres.resistencia_torre_1 = (*juego).torres.resistencia_torre_1 - (*juego).nivel.enemigos[orco].vida;
	}
	else{
		(*juego).torres.resistencia_torre_2 = (*juego).torres.resistencia_torre_2 - (*juego).nivel.enemigos[orco].vida;
	}
	(*juego).nivel.enemigos[orco].vida = ORCO_MUERTO;	
}	

/*
pre: Recibe el juego con todas sus estructuras validas
post: Todos los orcos vivos avanzan un casillero.
*/

void avanzar_orcos(juego_t* juego){
	for(int i=0; i<((*juego).nivel.tope_enemigos); i++){
		if(((*juego).nivel.enemigos[i].vida)>0){
			(*juego).nivel.enemigos[i].pos_en_camino++;
		}
		if((((*juego).nivel.enemigos[i].pos_en_camino)==((*juego).nivel.tope_camino_1 - 1))&&(((*juego).nivel.enemigos[i].camino)==CAMINO_1)){	
			ataque_orco(juego, i, 1);
		}	
		if((((*juego).nivel.enemigos[i].pos_en_camino)==((*juego).nivel.tope_camino_2 - 1))&&(((*juego).nivel.enemigos[i].camino)==CAMINO_2)){	
			ataque_orco(juego, i, 2);
		}
	}	
}		

/*
pre:  Recibe el nivel con todas sus estructuras validas y una cantidad de caminos valida.
post: Se creara un orco y dejara el nivel en el estado correspondiente.
*/

void generar_orco(nivel_t* nivel, int cantidad_caminos){
	(*nivel).enemigos[(*nivel).tope_enemigos].vida= VIDA_MINIMA_ORCO + rand() %101;
	(*nivel).enemigos[(*nivel).tope_enemigos].camino=CAMINO_1;
	(*nivel).enemigos[(*nivel).tope_enemigos].pos_en_camino=0;
	(*nivel).tope_enemigos++;
	if(cantidad_caminos==2){
		(*nivel).enemigos[(*nivel).tope_enemigos].vida= VIDA_MINIMA_ORCO + rand() %101;
		(*nivel).enemigos[(*nivel).tope_enemigos].camino=CAMINO_2;
		(*nivel).enemigos[(*nivel).tope_enemigos].pos_en_camino=0;
		(*nivel).tope_enemigos++;
	}	
}	

/*
pre:  Recibe el juego con todas sus estructuras validas.
post: El orco jugará un turno y dejará el juego en el estado correspondiente.
*/

void turno_orcos(juego_t* juego){
	avanzar_orcos(juego);
	if(((*juego).nivel.tope_enemigos)<(*juego).nivel.max_enemigos_nivel){
		if((*juego).nivel_actual==PRIMER_NIVEL || (*juego).nivel_actual==SEGUNDO_NIVEL){
			generar_orco(&((*juego).nivel), 1);	
		}
		else{
			generar_orco(&((*juego).nivel), 2);	
		}
	}
}	




void jugar_turno(juego_t* juego){
	for(int i=0; i<(*juego).nivel.tope_defensores; i++){
		if((*juego).nivel.defensores[i].tipo==ENANO){
			jugar_turno_enano(juego, i);
		}	
	}
	for(int i=0; i<(*juego).nivel.tope_defensores; i++){
		if((*juego).nivel.defensores[i].tipo==ELFO){
			jugar_turno_elfo(juego, i);
		}	
	}	
	turno_orcos(juego);
}




int estado_nivel(nivel_t nivel){
	bool hay_orco_vivo = false;
	int i = 0;
	while(!(hay_orco_vivo)&&(i<nivel.tope_enemigos)){
		if(nivel.enemigos[i].vida>0){
			hay_orco_vivo = true;
		}	
		i++;
	}	
	if((!(hay_orco_vivo)) && (nivel.max_enemigos_nivel==nivel.tope_enemigos)){
		return GANADO;
	}	
	else{ 
		return JUGANDO;
	}	
}	



int estado_juego(juego_t juego){
	if((juego.nivel_actual==CUARTO_NIVEL)&&(estado_nivel(juego.nivel)==GANADO)){
		return GANADO;
	}
	else if((juego.torres.resistencia_torre_1<=0)||(juego.torres.resistencia_torre_2<=0)){	
		return PERDIDO;
	}
	else{
		return JUGANDO;
	}	
}

/*
pre: Recibe el nivel con todas sus estructuras validas.
post: Devuelve false si la posicion no es valida, o true si es valida
*/

bool posicion_esta_libre(nivel_t* nivel, coordenada_t posicion){
	bool aux=true;
	for(int i=0; i<(*nivel).tope_camino_1; i++){
		if((posicion.fil==(*nivel).camino_1[i].fil)&&(posicion.col==(*nivel).camino_1[i].col)){
			aux=false;
		}
	}
	for(int i=0; i<(*nivel).tope_camino_2; i++){
		if((posicion.fil==(*nivel).camino_2[i].fil)&&(posicion.col==(*nivel).camino_2[i].col)){
			aux=false;
		}
	}
	for(int i=(*nivel).tope_defensores; i>0; i--){
		if((posicion.fil==(*nivel).defensores[i-1].posicion.fil)&&(posicion.col==(*nivel).defensores[i-1].posicion.col)){
			aux=false;
		}	
	}	

	return aux;	
}	

/*
pre: Recibe el tipo de defensor ya validado.
post: Le asigna la fuerza al defensor segun su tipo.
*/

int fuerza_ataque_defensores(char tipo){
	if(tipo==ENANO){
		return FUERZA_ENANO;
	}	
	else
		return FUERZA_ELFO;
}	





int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){
	int estado_posicion= POSICION_VALIDA;
	if((posicion_esta_libre(nivel, posicion))==false){
		estado_posicion=POSICION_INVALIDA;
	}
	else{	
		(*nivel).defensores[(*nivel).tope_defensores].tipo=tipo;
		(*nivel).defensores[(*nivel).tope_defensores].fuerza_ataque=fuerza_ataque_defensores(tipo);
		(*nivel).defensores[(*nivel).tope_defensores].posicion=posicion;
		(*nivel).tope_defensores++;
	}	
	return estado_posicion;
}



/*
*pre: Recibe el archivo de caminos y el juego, pasado por parametro y con todas sus estructuras validas.
*post: Lee el archivo y le asigna el camino al juego.
*/

void leer_camino(juego_t* juego, FILE * archivo_camino){
	int leidos;
	int camino;
	leidos =fscanf(archivo_camino, "NIVEL=%i\n", &((*juego).nivel_actual));
	leidos = fscanf(archivo_camino, "CAMINO=%i\n", &camino);
	leidos= fscanf(archivo_camino, "%i;%i\n", &((*juego).nivel.camino_1[(*juego).nivel.tope_camino_1].fil), &((*juego).nivel.camino_1[(*juego).nivel.tope_camino_1].col));	
	while(leidos==2){
		(*juego).nivel.tope_camino_1++;
		leidos= fscanf(archivo_camino, "%i;%i\n", &((*juego).nivel.camino_1[(*juego).nivel.tope_camino_1].fil), &((*juego).nivel.camino_1[(*juego).nivel.tope_camino_1].col));	
	}
	if(((*juego).nivel_actual==TERCER_NIVEL) || ((*juego).nivel_actual==CUARTO_NIVEL)){	
		leidos =fscanf(archivo_camino, "NIVEL=%i\n", &((*juego).nivel_actual));
		leidos = fscanf(archivo_camino, "CAMINO=%i\n", &camino);
		leidos= fscanf(archivo_camino, "%i;%i\n", &((*juego).nivel.camino_2[(*juego).nivel.tope_camino_2].fil), &((*juego).nivel.camino_2[(*juego).nivel.tope_camino_2].col));
		while(leidos==2){
		(*juego).nivel.tope_camino_2++;
		leidos= fscanf(archivo_camino, "%i;%i\n", &((*juego).nivel.camino_2[(*juego).nivel.tope_camino_2].fil), &((*juego).nivel.camino_2[(*juego).nivel.tope_camino_2].col));	
		}
	}	
}
