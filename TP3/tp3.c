#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "juego.h"
#include "caminos.h"
#include "configuracion.h"
#include "ranking.h"
#include "grabacion.h"
 
#define MAX_RESISTECIA_TORRE 600

#define COMANDO_JUGAR "jugar"
#define COMANDO_PASAME_LA_REPE "poneme_la_repe"
#define COMANDO_RANKING "ranking"
#define COMANDO_CREAR_CAMINO "crear_camino"
#define COMANDO_CREAR_CONFIGURACION "crear_configuracion"
#define COMANDO_CONFIG "config"
#define COMANDO_CAMINO_DEFAULT "-1"
#define COMANDO_GRABACION_NULO "vacio"
#define COMANDO_RANKING_DEFAULT "Ranking.csv"

const int ARGUMENTO_JUGAR = 1;
const int ARGUMENTO_CREAR_MAPA = 1;
const int ARGUMENTO_MOSTRAR_RANKING = 1;
const int ARGUMENTO_CREAR_CONFIGURACION = 1;
const int ARGUMENTO_MOSTRAR_GRABACION = 1;
const int ARGUMENTO_CAMINO = 2;
const int ARGUMENTO_CONFIGURACION = 2;
const int ARGUMENTO_PONEME_LA_REPE = 2;
const int ARGUMENTO_GRABACION = 3;
const int ARGUMENTO_LISTAR = 3;
const int ARGUMENTO_VELOCIDAD_JUEGO = 3;
const int COMANDO_CONFIGURACION = 7;
const int COMANDO_LISTAR= 7;
const int COMANDO_GRABACION = 10;

static const int OPCION_DEFAULT = -1;
const float VELOCIDAD_JUEGO_DEFAULT = 1;

static const int PRIMER_NIVEL = 1;
static const int SEGUNDO_NIVEL = 2;
static const int TERCER_NIVEL = 3;
static const int CUARTO_NIVEL = 4;

static const int TOPE_ENANOS_NIVEL3 = 3;
static const int TOPE_ELFOS_NIVEL3 = 3;
static const int TOPE_ENANOS_NIVEL4 = 4;
static const int TOPE_ELFOS_NIVEL4 = 4;

static const char ENANO='G';
static const char ELFO ='L';


/*
*pre: Recibe la cantidad de defensores extra determinados por la configuracion, y los defensores extra del juego.
*post: Determina los defensores extra del juego.
*/

void inicializar_defensores_extra(int* enanos_extra, int* elfos_extra, int enanos, int elfos){
	*enanos_extra=enanos;
	*elfos_extra=elfos;
}	

/*
*pre: Recibe la resistencia de las torres determinads por la configuracion, y las resistencias del juego.
*post: Determina las resistencias de las torres del juego.
*/

void inicializar_resistencia_torre(int* resistecia_torre_1, int* resistecia_torre_2, int resistencia_1, int resistencia_2){
	*resistecia_torre_1 = resistencia_1;
	*resistecia_torre_2 = resistencia_2;
}	

/*
*pre: Recibe el critico de los defensores determinados por la configuracion, y los criticos del juego por parametro.
*post: Determina los criticos del juego.
*/

void inicializar_critico(int* critico_gimli, int* critico_legolas, int critico_enanos, int critico_elfos){
	*critico_gimli=critico_enanos;
	*critico_legolas=critico_elfos;
}	

/*
*pre: Recibe el fallo de los defensores determinados por la configuracion, y los fallos del juego por parametro.
*post: Determina los fallos del juego.
*/

void inicializar_fallo(int* fallo_gimli, int* fallo_legolas, int fallo_enanos, int fallo_elfos){
	*fallo_gimli=fallo_enanos;
	*fallo_legolas=fallo_elfos;
}

/*
*pre: Recibe el viento y la humedad.
*post: Si estos no estan inicializados, devuelve True. Sino devuelve False.
*/

bool animos_esta_inicializado(int viento, int humedad){
	return((viento!=0) || (humedad!=0));
}

/*
*pre:Recibe el tipo de defensor, la velocidad del viento, humedad, y animo de legolas y gimli.
*post: Determina el fallo de los defensores segun lo calculado en animos.
*/

void determinar_fallo_default(int* fallo, int* viento, int* humedad, char* animo_gimli, char* animo_legolas, char tipo[MAX_NOMBRE]){
	if(!animos_esta_inicializado(*viento, *humedad)){
		animos(viento, humedad, animo_legolas, animo_gimli);
	}
	if(strcmp(tipo, ENANOS)==0){
		determinar_fallo_gimli(*humedad, fallo);
		printf("El porcentaje de fallo es: %i \n", *fallo);
	}	
	else{
		determinar_fallo_legolas(*viento, fallo);
		printf("El porcentaje de fallo es: %i \n", *fallo);
	}	
}	

/*
*pre: Recibe el tipo de defensor, la velocidad del viento, humedad, y animo de legolas y gimli.
*post: Determina el critico de los defensores segun lo calculado en animos.
*/

void determinar_critico_default(int* critico, int* viento, int* humedad, char* animo_gimli, char* animo_legolas, char tipo[MAX_NOMBRE]){
	if(!animos_esta_inicializado(*viento, *humedad)){
		animos(viento, humedad, animo_legolas, animo_gimli);
	}
	if(strcmp(tipo, ENANOS)==0){
		determinar_critico(*animo_gimli, critico);
		printf("El critico es : %i \n", *critico);
	}
	else{
		determinar_critico(*animo_gimli, critico);
		printf("El critico es : %i \n", *critico);
	}	
}	

/*
*pre: Recibe el tipo de defensor y la cantidade de tropas extra por parametro.
*post: Determina la cantidad de defensores extra con su valor default.
*/

void determinar_tropas_extra_default(int* tropas_extra, char tipo[MAX_NOMBRE]){
	if(strcmp(tipo, ENANOS)==0){
		*tropas_extra = MAX_ENANOS_EXTRA;
	}
	else{
		*tropas_extra = MAX_ELFOS_EXTRA;
	}	
}	

/*
*pre: Recibe la resistencia de la torre por parametro.
*post: Determina la resistencia de la torre con su valor default
*/

void determinar_resistencia_torre_default(int* resistencia_torre){
	*resistencia_torre = MAX_RESISTECIA_TORRE;
}

/*
*pre: Recibe juego por parametro, con todas sus estructuras validas.
*post: Determina todos valores defaults, elegidos por la configuracion del usuario.
*/

void determinar_defaults(juego_t* juego){
	char animo_gimli;
	char animo_legolas;
	int viento=0;
	int humedad=0;
	if((*juego).torres.resistencia_torre_1==OPCION_DEFAULT){
		determinar_resistencia_torre_default(&((*juego).torres.resistencia_torre_1));
	}
	if((*juego).torres.resistencia_torre_2==OPCION_DEFAULT){
		determinar_resistencia_torre_default(&((*juego).torres.resistencia_torre_2));
	}
	if((*juego).fallo_gimli==OPCION_DEFAULT){
		determinar_fallo_default(&((*juego).fallo_gimli), &viento, &humedad, &animo_gimli, &animo_legolas, ENANOS);
	}	
	if((*juego).fallo_legolas==OPCION_DEFAULT){
		determinar_fallo_default(&((*juego).fallo_legolas), &viento, &humedad, &animo_gimli, &animo_legolas, ELFOS);
	}
	if((*juego).critico_gimli==OPCION_DEFAULT){
		determinar_critico_default(&((*juego).critico_gimli), &viento, &humedad, &animo_gimli, &animo_legolas, ENANOS);
	}
	if((*juego).critico_legolas==OPCION_DEFAULT){
		determinar_critico_default(&((*juego).critico_legolas), &viento, &humedad, &animo_gimli, &animo_legolas, ELFOS);
	}
	if((*juego).torres.enanos_extra==OPCION_DEFAULT){
		determinar_tropas_extra_default(&((*juego).torres.enanos_extra), ENANOS);
	}
	if((*juego).torres.elfos_extra==OPCION_DEFAULT){
		determinar_tropas_extra_default(&((*juego).torres.elfos_extra), ELFOS);
	}	
}		

/*
*pre: Recibe juego y configuracion, con todas sus estructuras validas.
*post: Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de Legolas y Gimli.
*/

void inicializar_juego(juego_t* juego, configuracion_t configuracion, int* vida_torre_1, int* vida_torre_2){
	(*juego).nivel_actual=PRIMER_NIVEL;
	inicializar_resistencia_torre(&((*juego).torres.resistencia_torre_1), &((*juego).torres.resistencia_torre_2), configuracion.resistencia_torre_1, configuracion.resistencia_torre_2);
	inicializar_defensores_extra(&((*juego).torres.enanos_extra), &((*juego).torres.elfos_extra), configuracion.cant_enanos_extra, configuracion.cant_elfos_extra);
	inicializar_critico(&((*juego).critico_gimli), &((*juego).critico_legolas), configuracion.critico_enanos, configuracion.critico_elfos);
	inicializar_fallo(&((*juego).fallo_gimli), &((*juego).fallo_legolas), configuracion.fallo_enanos, configuracion.fallo_elfos);
	determinar_defaults(juego);
	calcular_vida_torres(vida_torre_1, vida_torre_2, (*juego).torres.resistencia_torre_1, (*juego).torres.resistencia_torre_2);
}	

/*
*pre: Recibe el juego por parametro, con todas sus estructuras validas.
*post: Determina el camino de forma default.
*/

void obtener_camino_default(juego_t* juego){
	coordenada_t torre[MAX_CANT_TORRES];
	coordenada_t entrada[MAX_CANT_ENTRADAS];
	inicializar_torre(*juego, torre);
	inicializar_entrada(*juego, entrada);
	obtener_caminos(entrada, torre, juego);
}	

/*
*pre: Recibe el juego pasado por parametro, con todas sus estructuras validas, y el archivo de caminos.
*post: Inicializara el nivel correspondiente, asignandole la posicion a las torres y entradas, obteniendo el camino,
*     inicializando los topes en 0, inicializando al maximo de enemigos y leyendo los caminos del nivel correspondiente.
*/

void inicializar_nivel(juego_t* juego, FILE * archivo_camino){	
	(*juego).nivel.tope_defensores=0;
	(*juego).nivel.tope_camino_1=0;
	(*juego).nivel.tope_camino_2=0;
	(*juego).nivel.tope_enemigos=0;
	inicializar_max_enemigos(juego);
	leer_camino(juego, archivo_camino);
}		

/*
*pre: Recibe juego y posicion, con todas sus estrcucturas validas, y la cantidad de enanos.
*post: Asigna la cantidad de eananos para usar en el nivel actual, dependiendo de la configuracion elegida por el usuario.
*/

void establecer_enanos(juego_t* juego, int cant_enanos, coordenada_t posicion, int* enanos_ranking){
	if(((*juego).nivel_actual==TERCER_NIVEL)&&(cant_enanos==OPCION_DEFAULT)){
		cant_enanos = TOPE_ENANOS_NIVEL3;
	}	
	if(((*juego).nivel_actual==CUARTO_NIVEL)&&(cant_enanos==OPCION_DEFAULT)){
		cant_enanos = TOPE_ENANOS_NIVEL4;
	}
	for(int i=0; i<cant_enanos; i++){
		seleccion_posicion_defensor(juego, &posicion, ENANO);
	}	
	calcular_defensas_ranking(enanos_ranking, cant_enanos);
}	

/*
*pre: Recibe juego y posicion, con todas sus estrcucturas validas, y la cantidad de elfos.
*post: Asigna la cantidad de elfos para usar en el nivel actual, dependiendo de la configuracion elegida por el usuario.
*/

void establecer_elfos(juego_t* juego, int cant_elfos, coordenada_t posicion, int* elfos_ranking){
	if(((*juego).nivel_actual==TERCER_NIVEL)&&(cant_elfos==OPCION_DEFAULT)){
		cant_elfos = TOPE_ELFOS_NIVEL3;
	}	
	if(((*juego).nivel_actual==CUARTO_NIVEL)&&(cant_elfos==OPCION_DEFAULT)){
		cant_elfos = TOPE_ELFOS_NIVEL4;
	}
	for(int i=0; i<cant_elfos; i++){
		seleccion_posicion_defensor(juego, &posicion, ELFO);
	}	
	calcular_defensas_ranking(elfos_ranking, cant_elfos);
}

/*
*pre: Recibe juego, configuracion y posicion, con todas sus etructuras validas, y el nivel actual.
*post: Asigna las defensas del nivel dependiendo de la configuracion elegida por el usuario.
*/

void establecer_defensas(juego_t* juego, configuracion_t configuracion, int nivel_actual, coordenada_t posicion, int* enanos_ranking, int* elfos_ranking){
	if((nivel_actual==PRIMER_NIVEL)||(nivel_actual=SEGUNDO_NIVEL)){
		if(((configuracion.cant_enanos[nivel_actual-1])==OPCION_DEFAULT) || ((configuracion.cant_elfos[nivel_actual-1])==OPCION_DEFAULT)){
			asignar_defensas_default(juego, posicion, enanos_ranking, elfos_ranking);
		}
		else{	
			establecer_enanos(juego, configuracion.cant_enanos[nivel_actual-1], posicion, enanos_ranking);
			establecer_elfos(juego, configuracion.cant_elfos[nivel_actual-1], posicion, elfos_ranking);
		}
	}	
}	

/*
*pre: Recibe juego y posicion con todas sus etructuras validas, la velocidad del juego y el contador, pasado por referencia.
*post: Realiza todas las acciones a ejecutar de un nivel.
*/

void ejecutar_turno(juego_t* juego, int* contador, float velocidad_juego, coordenada_t posicion){
	if(((*juego).nivel_actual==PRIMER_NIVEL) && ((((*juego).nivel.tope_enemigos)%25)==0) && ((*contador)<=(*juego).nivel.max_enemigos_nivel)){
		agregar_defensor_extra(juego, posicion);
	}
	else if((((*juego).nivel.tope_enemigos)%50)==0 && ((*contador)<=(*juego).nivel.max_enemigos_nivel)){
		agregar_defensor_extra(juego, posicion);
	}
	jugar_turno(juego);
	mostrar_juego(*juego);
	*contador = *contador + 1;
	detener_el_tiempo(velocidad_juego);
	system("clear");
}		

/*
*pre: Recibe juego, posicion y configuracion con todas sus estructuras validas, el archivo de caminos , y el contador y la cantidad de orcos muertos, por parametro.
*post: Juega al juego con los caminos creados por el usuario.
*/

int jugar_juego_comandos(juego_t* juego, FILE * archivo_camino, configuracion_t configuracion, coordenada_t posicion, int* contador, int* orcos_muertos, char ruta_archivo_repe[MAX_NOMBRE_COMANDO], int* cant_enanos, int* cant_elfos){
	FILE * archivo_grabacion;
	if(strcmp(ruta_archivo_repe, COMANDO_GRABACION_NULO)!=0){
		archivo_grabacion=fopen(ruta_archivo_repe, "w");
		if(!archivo_grabacion)
			return -1;
	}	
	do{
		if(strcmp(configuracion.ruta_camino, COMANDO_CAMINO_DEFAULT)==0){
			coordenada_t torre[MAX_CANT_TORRES];
			coordenada_t entrada[MAX_CANT_ENTRADAS];
			inicializar_nivel_default(juego, entrada, torre);
		}else{
			inicializar_nivel(juego, archivo_camino);
		}	
		mostrar_juego(*juego);
		establecer_defensas(juego, configuracion, (*juego).nivel_actual, posicion, cant_enanos, cant_elfos);
		detener_el_tiempo(1);
		do{
			if(strcmp(ruta_archivo_repe, COMANDO_GRABACION_NULO)!=0){
				escribir_grabacion(*juego, archivo_grabacion);
			}	
			ejecutar_turno(juego, contador, configuracion.velocidad_juego, posicion);
		}while(estado_nivel((*juego).nivel)==JUGANDO && estado_juego(*juego)==JUGANDO);	
		contador = 0;
		if(estado_nivel((*juego).nivel)==GANADO && (*juego).nivel_actual!=CUARTO_NIVEL){
			presentacion_nivel_ganado();
		}	
		contar_orcos_muertos(orcos_muertos, (*juego).nivel.enemigos, (*juego).nivel.tope_enemigos);
		(*juego).nivel_actual++;
	}while(estado_juego(*juego)==JUGANDO);
	if(strcmp(ruta_archivo_repe, COMANDO_GRABACION_NULO)!=0){
		fclose(archivo_grabacion);
	}
	return 1;
}	

/*
*pre: Recibe la velocidad del juego por parametro.
*post: Determina la velocidad del juego.
*/

void determinar_velocidad_juego(float* velocidad_juego){
	if(*velocidad_juego==OPCION_DEFAULT){
		*velocidad_juego= VELOCIDAD_JUEGO_DEFAULT;
	}	
}	

/*
*pre: Recibe juego por parametro, con todas sus estructuras validas, la ruta del archivo y la cantidad de orcos muertos.
*post: Si se pudieron abrir los archivos, se juega el juego y devuelve 1.
* Si no se puede abrir alguno de los archivos devuelve -1.
*/

int jugar_juego(juego_t* juego, char ruta_archivo_config[MAX_NOMBRE_COMANDO], int* orcos_muertos, char ruta_archivo_repe[MAX_NOMBRE_COMANDO], int* vida_torre_1, int* vida_torre_2, int* cant_enanos, int* cant_elfos){
	srand((unsigned)time(NULL));
	configuracion_t configuracion;
	coordenada_t posicion;
	int contador;
	bool se_pudo_leer;
	FILE * archivo_camino;
	se_pudo_leer=leer_configuracion(ruta_archivo_config, &configuracion);
	if(!se_pudo_leer){
		return -1;
	}	
	if(strcmp(configuracion.ruta_camino, COMANDO_CAMINO_DEFAULT)!=0){
		archivo_camino = fopen(configuracion.ruta_camino, "r");
		if(!archivo_camino){
			printf("Error al abrir el archivo %s", configuracion.ruta_camino);
			return -1;
		}	
	}	
	inicializar_juego(juego, configuracion, vida_torre_1, vida_torre_2);
	determinar_velocidad_juego(&(configuracion.velocidad_juego));
	jugar_juego_comandos(juego, archivo_camino, configuracion, posicion, &contador, orcos_muertos, ruta_archivo_repe, cant_enanos, cant_elfos);
	fclose(archivo_camino);
	return 1;
}	

/*
*pre: Recibe el comando de velocidad ingresado por el usuario.
*post: Transforma la cadena ingresada por el usuario a un numero.
*/

float obtener_velocidad_juego(char comando_velocidad[MAX_NOMBRE_COMANDO]){
	char *comando;
	comando = strtok(comando_velocidad, "=");
	comando = strtok(NULL, "\n");
	float velocidad_juego = (float) atof(comando);
	return velocidad_juego;
}	

/*
*pre: Recibe la ruta del archivo de caminos.
*post: Realiza todas las acciones relacionadas con crear los caminos.
*/

void ejecutar_crear_camino(char ruta_archivo[MAX_NOMBRE_COMANDO]){
	camino_t camino;
	camino.nivel = 1;
	inicializar_creacion_camino(ruta_archivo, &camino);
}	

/*
*pre: Recibe la ruta del archivo configuracion.
*post: Realiza todas las acciones relacionadas  con crear la configuracion.
*/

void ejecutar_crear_configuracion(char ruta_archivo[MAX_NOMBRE_COMANDO]){
	strcpy(ruta_archivo, &(ruta_archivo[COMANDO_CONFIGURACION]));
	configuracion_t configuracion;
	inicializar_creacion_config(ruta_archivo, &configuracion);
}	

/*
*pre: Recibe los argumentos ingresados por el usuario y el juego con todas sus estructuras validas, pasado por parametro.
*post: Realiza todas las acciones relacionadas con pasar la repeticion.
*/

void ejecutar_poneme_la_repe(int argc, char* argv[], juego_t* juego){
	char* comando;
	comando = strtok(argv[ARGUMENTO_PONEME_LA_REPE], "=");	
	strcpy(comando, &(comando[COMANDO_GRABACION]));
	if(argc==4){
		float velocidad_juego;
		velocidad_juego= obtener_velocidad_juego(argv[ARGUMENTO_VELOCIDAD_JUEGO]);
		printf("%f", velocidad_juego);
		lectura_grabacion(comando, juego, velocidad_juego);
	}
	else if(argc==3){
		lectura_grabacion(comando, juego, VELOCIDAD_JUEGO_DEFAULT);
	}	
	else{
		printf("Para poder ver la repeticion es obligatorio poner la ruta del archivo.");
	}	
}	

/*
*pre: Recibe los comandos ingresados por el usuario y la cantidad de jugadores a mostrar.
*post: Determina la cantidad de jugadores a mostrar, y la ruta de los archivos.
*/

void determinar_comandos_ranking(char* comando_config, char* comando_listar, int* listar){
	strcpy(comando_config, &(comando_config[COMANDO_CONFIGURACION]));
	comando_config = strtok(comando_config, ".");
	strcat(comando_config, ".csv");
	strcpy(comando_listar, &(comando_listar[COMANDO_LISTAR]));
	*listar = (int) atoi(comando_listar);
}	

/*
*pre: Recibe los argumentos ingresados por el usuario
*post: Realiza todas las acciones realizadas relecionadas con ranking.
*/

void ejecutar_ranking(int argc, char* argv[]){
	if(argc==2){
		inicializar_lectura_ranking(COMANDO_RANKING_DEFAULT, OPCION_DEFAULT);
	}	
	else if(argc==3){	
		char* comando;
		comando = strtok(argv[ARGUMENTO_CONFIGURACION], "=");
		if(strcmp(comando, COMANDO_CONFIG)==0){
			strcpy(comando, &(comando[COMANDO_CONFIGURACION]));
			comando = strtok(comando, ".");
			strcat(comando, ".csv");
			inicializar_lectura_ranking(comando, OPCION_DEFAULT);
		}
		else{	
			strcpy(comando, &(comando[COMANDO_LISTAR]));
			int listar = (int) atoi(comando);
			inicializar_lectura_ranking(COMANDO_RANKING_DEFAULT, listar);
		}	
	}	
	else{
		char* comando_1;
		char* comando_2;
		comando_1 = strtok(argv[ARGUMENTO_CONFIGURACION], "=");
		comando_2 = strtok(argv[ARGUMENTO_LISTAR], "=");
		int listar;
		determinar_comandos_ranking(comando_1, comando_2, &listar);
		inicializar_lectura_ranking(comando_1, listar);	
	}
}	

/*
*pre: Recibe juego con todas sus estructuras validas, la cantidad de defensores en cada nivel, la cantidad de orcos muertos, la vida inicial de las torres
	  y la ruta del archivo de ranking..
*post: Determina el puntaje del jugador y lo escribe en el archivo.
*/

void ejecutar_lectura_ranking(int vida_torre_1, int vida_torre_2, int cant_enanos, int cant_elfos, juego_t juego, int orcos_muertos, char ruta_archivo[MAX_NOMBRE_COMANDO]){
	ranking_t jugador_nuevo;
	determinar_puntaje(&(jugador_nuevo.puntaje), orcos_muertos, vida_torre_1, vida_torre_2, cant_enanos, cant_elfos, juego.torres.enanos_extra, juego.torres.elfos_extra);
	ruta_archivo = strtok(ruta_archivo, ".");
	strcat(ruta_archivo, ".csv");
	inicializar_escritura_ranking(jugador_nuevo, ruta_archivo);
}	

/*
*pre: Recibe los argumentos ingresados por el usuario y el juego con todas sus estructuras validas, pasado por parametro.
*post: Realiza todo lo relacionado con el comando jugar.
*/

void ejecutar_jugar(int argc, char* argv[], juego_t* juego){
	int vida_torre_1;
	int vida_torre_2;
	int cant_enanos;
	int cant_elfos;
	int orcos_muertos;
	if(argc==3){
		char* comando;
		comando = strtok(argv[ARGUMENTO_CONFIGURACION], "=");
		if(strcmp(comando, COMANDO_CONFIG)==0){
			strcpy(comando, &(comando[COMANDO_CONFIGURACION]));
			jugar_juego(juego, comando, &orcos_muertos, COMANDO_GRABACION_NULO, &vida_torre_1, &vida_torre_2, &cant_enanos, &cant_elfos);
			ejecutar_lectura_ranking(vida_torre_1, vida_torre_2, cant_enanos, cant_elfos, *juego, orcos_muertos, comando);
		}
		else{
			strcpy(comando, &(comando[COMANDO_GRABACION]));
			jugar_juego_default(&orcos_muertos, comando, &cant_enanos, &cant_enanos, &vida_torre_1, &vida_torre_2, juego);
			ejecutar_lectura_ranking(vida_torre_1, vida_torre_2, cant_enanos, cant_elfos, *juego, orcos_muertos, COMANDO_RANKING_DEFAULT);
		}	
	}
	else if(argc==4){
		char* comando_1;
		char* comando_2;
		comando_1 = strtok(argv[ARGUMENTO_CONFIGURACION], "=");
		comando_2 = strtok(argv[ARGUMENTO_GRABACION], "=");
		strcpy(comando_1, &(comando_1[COMANDO_CONFIGURACION]));
		strcpy(comando_2, &(comando_2[COMANDO_CONFIGURACION]));
		jugar_juego(juego, comando_1, &orcos_muertos, comando_2, &vida_torre_1, &vida_torre_2, &cant_enanos, &cant_elfos);
		ejecutar_lectura_ranking(vida_torre_1, vida_torre_2, cant_enanos, cant_elfos, *juego, orcos_muertos, comando_1);
	}
	else{	
		jugar_juego_default(&orcos_muertos, COMANDO_GRABACION_NULO, &cant_enanos, &cant_elfos, &vida_torre_1, &vida_torre_2, juego);
		ejecutar_lectura_ranking(vida_torre_1, vida_torre_2, cant_enanos, cant_elfos, *juego, orcos_muertos, COMANDO_RANKING_DEFAULT);
	}
}	



int main(int argc, char* argv[]){
	juego_t juego;
	if(argc>1){
		if((strcmp(argv[ARGUMENTO_CREAR_MAPA], COMANDO_CREAR_CAMINO)==0) && (argc==3)){
			ejecutar_crear_camino(argv[ARGUMENTO_CAMINO]);
		}
		else if((strcmp(argv[ARGUMENTO_CREAR_CONFIGURACION], COMANDO_CREAR_CONFIGURACION)==0) && (argc==3)){	
			ejecutar_crear_configuracion(argv[ARGUMENTO_CONFIGURACION]);
		}
		else if(strcmp(argv[ARGUMENTO_MOSTRAR_GRABACION], COMANDO_PASAME_LA_REPE)==0){
			ejecutar_poneme_la_repe(argc, argv, &juego);	
		}
		else if(strcmp(argv[ARGUMENTO_MOSTRAR_RANKING], COMANDO_RANKING)==0){	
			ejecutar_ranking(argc, argv);	
		}
		else if(strcmp(argv[ARGUMENTO_JUGAR], COMANDO_JUGAR)==0){
			ejecutar_jugar(argc, argv, &juego);	
		}
		else{	
			printf("Ninguno de los comandos es correcto.");
		}	
	}

	return 0;  
}