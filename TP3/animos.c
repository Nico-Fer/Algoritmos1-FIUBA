#include <stdio.h>
#include <stdbool.h>
#include "animos.h"


const char HORARIO_TARDE='T';
const char HORARIO_MANIANA='M';
const char HORARIO_NOCHE='N';
const char ENSALADA = 'E';
const char HAMBURGUESA = 'H';
const char PIZZA = 'P';
const char GUISO = 'G';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char LEGOLAS = 'L';
const char GIMLI = 'G';
const int DIA_MINIMO =1;
const int DIA_MAXIMO =30;
const int CANT_HORAS_MINIMA = 0;
const int CANT_HORAS_MAXIMA = 12;
const int DIA_DECIMO =10;
const int DIA_POST_DECIMO =11;
const int DIA_DUODECIMO =20;
const int DIA_POST_DUODECIMO =21;
const int PUNTOS_PIE_IZQUIERDO = 0;
const int PUNTOS_PIE_DERECHO = 10 ;
const int PUNTOS_PIZZA = 10 ;
const int PUNTOS_HAMBURGUESA = 15 ;
const int PUNTOS_GUISO = 5 ;
const int PUNTOS_ENSALADA = 20 ;
const int HORAS_SUENIO_MALAS_MIN = 0 ;
const int HORAS_SUENIO_MALAS_MAX = 4 ;
const int HORAS_SUENIO_BUENAS_MIN = 5 ;
const int HORAS_SUENIO_BUENAS_MAX = 8 ;
const int PUNTOS_SUENIO_MIN = 0 ;
const int PUNTOS_SUENIO_MEDIO = 10 ;
const int PUNTOS_SUENIO_MAX = 20 ;
const int PUNTOS_ANIMO_MALO_MIN = 5;
const int PUNTOS_ANIMO_MALO_MAX = 20;
const int PUNTOS_ANIMO_BUENO_MIN = 36;
const int PUNTOS_ANIMO_BUENO_MAX = 50;
const int PUNTOS_ANIMO_REGULAR_MIN = 21;
const int PUNTOS_ANIMO_REGULAR_MAX = 35;

#define MAX_RESISTENCIA_TORRE 600
#define MAX_TROPAS_EXTRA 10
#define CRITICO_MALO 0
#define CRITICO_REGULAR 10
#define CRITICO_BUENO 25
#define FALLO_LEGOLAS_MALO (VELOCIDAD_VIENTO_MINIMA/2)
#define FALLO_LEGOLAS_REGULAR (VELOCIDAD_VIENTO_MEDIA/2)
#define FALLO_LEGOLAS_BUENO (VELOCIDAD_VIENTO_MAXIMA/2)
#define FALLO_GIMLI_MALO (HUMEDAD_NOCHE/2)
#define FALLO_GIMLI_REGULAR (HUMEDAD_TARDE/2)
#define FALLO_GIMLI_BUENO (HUMEDAD_MANIANA/2)
#define  ENANO 'G'
#define  ELFO 'L'
#define PRIMER_NIVEL   1
#define SEGUNDO_NIVEL   2
#define TERCER_NIVEL   3
#define CUARTO_NIVEL   4
#define TOPE_DEFENSORES_NIVEL1  5
#define TOPE_DEFENSORES_NIVEL2  5
#define TOPE_ENANOS_NIVEL3  3
#define TOPE_ELFOS_NIVEL3  3
#define TOPE_ENANOS_NIVEL4  4
#define TOPE_ELFOS_NIVEL4  4
#define TOPE_TERRENO_NIVEL4  20
#define TOPE_TERRENO_NIVEL3  20
#define TOPE_TERRENO_NIVEL2  15
#define TOPE_TERRENO_NIVEL1  15
#define MAX_CANT_TORRES   2
#define MAX_CANT_ENTRADAS   2
#define GANADO   1
#define JUGANDO   0
#define PERDIDO   -1
#define POSICION_INVALIDA  -1
#define POSICION_VALIDA  1
#define FUERZA_ENANO   60
#define FUERZA_ELFO   30
#define FILA_TORRE1_SUR 19 
#define COL_TORRE1_SUR  8
#define FILA_TORRE2_SUR  19
#define COL_TORRE2_SUR  11
#define FILA_TORRE1_NORTE  0
#define COL_TORRE1_NORTE  5
#define FILA_TORRE2_NORTE  0
#define COL_TORRE2_NORTE  11
#define FILA_TORRE_ESTE  10
#define COL_TORRE_ESTE  14
#define FILA_TORRE_OESTE  6
#define COL_TORRE_OESTE  0
#define FILA_ENTRADA1_SUR  19
#define COL_ENTRADA1_SUR  2
#define FILA_ENTRADA2_SUR  19
#define COL_ENTRADA2_SUR  14
#define FILA_ENTRADA1_NORTE  0
#define COL_ENTRADA1_NORTE  3
#define FILA_ENTRADA2_NORTE  0
#define COL_ENTRADA2_NORTE  16
#define FILA_ENTRADA_ESTE  2
#define COL_ENTRADA_ESTE  14
#define FILA_ENTRADA_OESTE  3
#define COL_ENTRADA_OESTE  0
#define MAX_ENEMIGOS_PRIMER_NIVEL   100
#define MAX_ENEMIGOS_SEGUNDO_NIVEL   150
#define MAX_ENEMIGOS_TERCER_NIVEL   400
#define MAX_ENEMIGOS_CUARTO_NIVEL   500


void presentacion(){
	printf("----------------------------------DEFENDIENDO LAS TORRES----------------------------------\n");
	printf("Tanto el animo de Legolas(L) como el de Gimli(g) podra ser Bueno(B), Regular(R) o Malo(M), y como buenos lideres que son, esto afectara a los elfos(en el caso de Legolas) o a los enanos(si se trata del animo de Gimli).\n");
}






/*
*pre: El valor de pie tiene que ser D o I.
*post:Devuelve el valor falso, si no se cumplen las condiciones, o el valor verdadero, si se cumplen.
*/

bool es_pie_valido(char pie){
		return ((pie==PIE_DERECHO)||(pie==PIE_IZQUIERDO));
}

/*
*pre: El valor de cena tiene que ser H, E, P o G.
*post: Devuelve el valor falso, si no se cumplen las condiciones, o el valor verdadero, si se cumplen.
*/

bool es_cena_valida(char cena){
		return ((cena==HAMBURGUESA)||(cena==ENSALADA)||(cena==PIZZA)||(cena==GUISO));
}

/*
*pre: Las horas dormidas tienen que estar entre o y 12.
*post: Devuelve el valor falso, si no se cumplen las condiciones, o el valor verdadero, si se cumplen.  
*/

bool validacion_horas_dormidas(int horas_dormidas){
	if ((horas_dormidas<=CANT_HORAS_MAXIMA)&&(horas_dormidas>=CANT_HORAS_MINIMA))
		return true;
	else
		return false;
}

/*
*pre: pie_elejido debe ser uno de los caracteres indicados.
*/

void preguntar_pie(char personaje, char* pie_elejido){
	printf("¿Con que pie se levanto %c (Derecho(D) o Izquierdo(I))?\n", personaje);
	scanf(" %c", pie_elejido);
	while(!(es_pie_valido(*pie_elejido))){
		printf("Elfos, humanos y enanos solo tienen dos pies(izquierdo y derecho, o eso creo).\n");
		scanf(" %c", pie_elejido);
	}
}

/*
*pre: Cena debe ser uno de los caracteres indicados.
*/

void cena_elejida(char personaje, char* cena){
	printf("¿Que ceno %c la noche anterior?(Hamburguesa(H), Guiso(G), Pizza(P), Ensalada(E)).\n", personaje);
	scanf(" %c", cena);
	while(!(es_cena_valida(*cena))){
		printf("Las unicas comidas que hay en la tierra media son las hamburguesas, ensaladas, pizzas y guisos (aunque no lo creas).\n");
		scanf(" %c", cena);
	}
}	

/*
*pre: horas_dormidas debe estar entre los valores pedidos.
*/

void horas_de_suenio(char personaje, int* horas_dormidas){
	printf("¿Cuantas horas durmio %c (entre 0 y 12 horas)?\n", personaje);
	scanf("%i", horas_dormidas);	
	while(validacion_horas_dormidas(*horas_dormidas)==false){
		printf("Segun wikipedia los elfos y enanos duermen entre ohs y 12hs\n");
		scanf(" %i", horas_dormidas);
	}
}	


void inicializar_animo(char personaje, char *pie_elejido, char *cena, int *horas_dormidas){
	preguntar_pie(personaje, pie_elejido);
	cena_elejida(personaje, cena);
	horas_de_suenio(personaje, horas_dormidas);
	printf("%c durmio %ihs, ceno %c, y se levanto con el pie %c.\n", personaje, *horas_dormidas, *cena, *pie_elejido);
}

/*
*pre: el valor de dia tiene que ser un numero entero, entre 0 y 30.
*post:Devuelve el valor falso, si no se cumplen las condiciones, o el valor verdader, si se cumplen.
*/

bool es_dia_valido(int dia){
		return ((dia>=DIA_MINIMO) & (dia<=DIA_MAXIMO));	
}


/*
*pre: dia tiene que estar entre los valores pedidos.
*/

void eleccion_dia(int* dia){
	printf("¿Que dia del mes es(en numero)?\n");
	scanf("%i", dia);
	while (!(es_dia_valido(*dia))){
		printf("La cantidad de dias es igual en todos lados (entre 1 y 30)\n");
		scanf("%i", dia);
	}
	printf("El dia es %i \n", *dia);
}


/*
*post: Devuelve la velocidad del viento.
*/

int determinacion_viento(int dia, int* viento){

	if ((dia<=DIA_DECIMO)&&(dia>=DIA_MINIMO)){
		*viento=VELOCIDAD_VIENTO_MAXIMA;
	}
	else if ((dia<=DIA_DUODECIMO)&&(dia>=DIA_POST_DECIMO)){
		*viento= VELOCIDAD_VIENTO_MEDIA;
	}
	else {
		*viento=VELOCIDAD_VIENTO_MINIMA;
	}
	return *viento;
}


/*
*post: Devuelve el porcentaje de humedad.
*/

int determinacion_humedad(char horario, int* humedad){
	if(horario==HORARIO_MANIANA)
		*humedad=HUMEDAD_MANIANA;
	else if (horario==HORARIO_TARDE)
		*humedad=HUMEDAD_TARDE;
	else {
		*humedad=HUMEDAD_NOCHE;
		}
	return *humedad;	
}

/*
*pre: horario es un caracter elegido por el usuario.
*post:Devuelve el valor falso, si no se cumplen las condiciones, o el valor verdadero, si se cumplen.
*/

bool es_horario_valido(char horario){
		return ((horario==HORARIO_NOCHE)||(horario==HORARIO_MANIANA)||(horario==HORARIO_TARDE));
}

/*
*pre: horario debe ser uno de los caracteres indicados.
*/

void eleccion_horario(char *horario){
	printf("¿Que horario es (Mañana(M), Tarde(T), Noche(N))?\n");
	scanf(" %c", horario);
	while (!(es_horario_valido(*horario))){
		printf("En el dia no hay muchos horarios (Mañana(M), Tarde(T), Noche(N))\n");
		scanf(" %c", horario);
	}
	printf("El horario es a la %c \n", *horario);
}

/*
*post:Devuelve un entero, siendo este, las suma de puntos.
*/

void puntos_horas_dormidas(int *contador, int horas_dormidas){
	if ((horas_dormidas>=HORAS_SUENIO_MALAS_MIN)&&(horas_dormidas<=HORAS_SUENIO_MALAS_MAX)){
		*contador=PUNTOS_SUENIO_MIN;
	}
	else if ((horas_dormidas>=HORAS_SUENIO_BUENAS_MIN)&&(horas_dormidas<=HORAS_SUENIO_BUENAS_MAX)){
		*contador=PUNTOS_SUENIO_MEDIO;
	}
	else {
		*contador=PUNTOS_SUENIO_MAX;
	}
}

/*
*post: Devuelve un entero, siendo este, las suma de puntos.
*/

void puntos_cena(int* contador, char cena){
	if (cena == PIZZA){
		*contador= *contador + PUNTOS_PIZZA;
	}
	else if (cena == ENSALADA){
		*contador= *contador + PUNTOS_ENSALADA;
	}
	else if (cena == HAMBURGUESA){
		*contador= *contador + PUNTOS_HAMBURGUESA;
	}
	else {
		*contador= *contador + PUNTOS_GUISO;
	}	
}	

/*
*post: Devuelve un entero, siendo este, las suma de puntos.
*/

void puntos_pie(int* contador, char pie_elejido){
	if (pie_elejido == PIE_IZQUIERDO){
		*contador = *contador + PUNTOS_PIE_IZQUIERDO;
	}
	else {
		*contador = *contador + PUNTOS_PIE_DERECHO;
	}
}

/*
*post: Devuelve un caracter, siendo este, el animo de los personajes.
*/

char determinacion_animo(char personaje, int* contador, char pie_elejido, char cena, int horas_dormidas, char *animo){
	puntos_horas_dormidas(contador, horas_dormidas);
	puntos_cena(contador, cena);
	puntos_pie(contador, pie_elejido);
	if ((*contador>=PUNTOS_ANIMO_MALO_MIN)&&(*contador<=PUNTOS_ANIMO_MALO_MAX)){
		*animo= ANIMO_MALO;
	}
	else if ((*contador>=PUNTOS_ANIMO_REGULAR_MIN)&&(*contador<=PUNTOS_ANIMO_REGULAR_MAX)){
		*animo= ANIMO_REGULAR;
	}	
	else {
		*animo= ANIMO_BUENO;
	}
	return *animo;	
}



void animos(int* viento, int* humedad, char* animo_legolas, char* animo_gimli){
	int dia;
	int horas_dormidas_L;
	int horas_dormidas_g;
	int contador_puntos_L =0;
	int contador_puntos_g =0;
	char horario;
	char pie_elejido_L;
	char pie_elejido_g;
	char cena_L;
	char cena_g;
	presentacion();
	eleccion_dia(&dia);
	determinacion_viento(dia, viento);
	eleccion_horario(&horario);
	determinacion_humedad(horario, humedad);
	inicializar_animo(LEGOLAS, &pie_elejido_L, &cena_L, &horas_dormidas_L);
	inicializar_animo(GIMLI, &pie_elejido_g, &cena_g, &horas_dormidas_g);
	determinacion_animo(LEGOLAS, &contador_puntos_L, pie_elejido_L, cena_L, horas_dormidas_L, animo_legolas);
	determinacion_animo(GIMLI, &contador_puntos_g, pie_elejido_g, cena_g, horas_dormidas_g, animo_gimli);
	printf("Resumen: %i %i %c %c .\n", *viento, *humedad, *animo_legolas, *animo_gimli);
	}