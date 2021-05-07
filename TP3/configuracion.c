#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "juego.h"
#include "configuracion.h"

#define PRIMER_NIVEL   1
#define SEGUNDO_NIVEL   2
#define TERCER_NIVEL  3
#define CUARTO_NIVEL   4

const int OPCION_DEFAULT = -1;

	
/*
*pre:Recibe un entero, representando la resistencia de la torre elegida.
*post:Devuelve True si el valor ingresado es valido, sino devuelve False.
*/

bool es_resistencia_valida(int resistencia_torre){
	return((resistencia_torre>0)||(resistencia_torre==OPCION_DEFAULT));
}	

/*
*pre: Recibe la torre elegida y la resistencia de la torre por parametro.
*post: Asigna la resistencia a la torre elegida, ya validada.
*/

void pedir_resistencia_torre(int* resistencia_torre, int numero_torre){
	printf("Seleccione la resistencia de la Torre %i: ", numero_torre);
	scanf("%i", resistencia_torre);
	while(!es_resistencia_valida(*resistencia_torre)){
		printf("Para poder jugar la resistencia de la Torre debe ser mayor a cero.\n");
		scanf("%i", resistencia_torre);
	}
}	

/*
*pre: Recibe un entero, representado la cantidad de tropas extra ingresada por el usuario.
*post: Devuelve True si la cantidad ingresada es valida, sino devuelve false.
*/

bool es_tropas_extra_valido(int tropas_extra){
	return((tropas_extra>=0)||(tropas_extra==OPCION_DEFAULT));
}	

/*
*pre: Recibe el tipo de defensor y las tropas extra por parametro.
*post: Asigna la cantidad de tropas extra, ya validada.
*/

void pedir_tropas_extra(int* tropas_extra, char tipo[MAX_NOMBRE]){
	printf("Ingrese la cantidad de %s extra: ", tipo);
	scanf("%i", tropas_extra);
	while(!es_tropas_extra_valido(*tropas_extra)){
		printf("La cantidad ingresada debe ser mayor o igual a cero.\n");
		scanf("%i", tropas_extra);
	}	
}	

/*
*pre:Recibe un entero, representado la cantidad de tropas ingresada por el usuario.
*post: Devuelve True si la cantidad ingresada es valida, sino devuelve false.
*/

bool es_tropas_valido(int tropas){
	return((tropas>0)||(tropas==OPCION_DEFAULT));
}

/*
*pre: Recibe el nivel, tipo de defensor y las tropas, siendo esta pasada por parametro.
*post: Asigna la cantiad de tropas, ya validada.
*/

void pedir_tropas(int* tropas, char tipo[MAX_NOMBRE], int nivel){
	printf("Ingrese la cantidad de %s que quiere en el nivel %i: ", tipo, nivel);
	scanf("%i", tropas);
	while(!es_tropas_valido(*tropas)){
		printf("La cantidad ingresada debe ser mayor a cero.\n");
		scanf("%i", tropas);
	}	
}		

/*
*pre:Recibe un entero, representado el porcentaje de fallo ingresado por el usuario.
*post: Devuelve True si la cantidad ingresada es valida, sino devuelve false.
*/

bool es_fallo_valido(int fallo){
	return((fallo>=0)||(fallo==OPCION_DEFAULT));
}	

/*
*pre: Recibe el tipo de defensor y el fallo, pasado por parametro.
*post: Asigna el porcentaje de fallo, ya validado.
*/

void pedir_fallo(int* fallo, char tipo[MAX_NOMBRE]){
	printf("Ingrese el porcentaje de fallo para los %s: ", tipo);
	scanf("%i", fallo);
	while(!es_fallo_valido(*fallo)){
		printf("El valir ingresado debe ser mayor o igual a cero.\n");
		scanf("%i", fallo);
	}	
}	

/*
*pre: Recibe un entero, representado el porcentaje de fallo ingresado por el usuario.
*post: Devuelve True si la cantidad ingresada es valida, sino devuelve false.
*/

bool es_critico_valido(int critico){
	return((critico>=0)||(critico==OPCION_DEFAULT));
}	

/*
*pre: Recibe el tipo de defensor y el porcentaje de critico, pasado por parametro.
*post: Asigna el porcentaje de fallo, ya validado.
*/

void pedir_critico(int* critico, char tipo[MAX_NOMBRE]){
	printf("Ingrese el porcentaje de critico para los %s: ", tipo);
	scanf("%i", critico);
	while(!es_critico_valido(*critico)){
		printf("El valor ingresado debe ser mayor o igual a cero.\n");
		scanf("%i", critico);
	}	
}

/*
*pre:Recibe un float, representado la velocidad del juego ingresada por el usuario.
*post: Devuelve True si la cantidad ingresada es valida, sino devuelve false.
*/

bool es_velocidad_valida(float velocidad_juego){
	return((velocidad_juego>0)||(velocidad_juego==OPCION_DEFAULT));
}

/*
*pre: Recibe la velocidad del juego, pasado por parametro.
*post: Asigna la velocidad del juego, ya validada.
*/

void pedir_velocidad_juego(float* velocidad_juego){
	printf("Ingrese la velocidad del juego: ");
	scanf("%f", velocidad_juego);
	while(!es_velocidad_valida(*velocidad_juego)){
		printf("El valor ingresado debe ser mayor a cero.\n");
		scanf("%f", velocidad_juego);
	}	
}	


/*
*pre: Recibe un string, donde se guardara la ruta del archivo de caminos.
*post: Asigna la ruta del archivo de caminos, ingresado por el usuario.
*/

void pedir_camino(char ruta_camino[MAX_NOMBRE_RUTA]){
	printf("Elija la ruta del archivo del camino con extension.\n");
	scanf(" %s", ruta_camino);	
}	

/*
*pre: Recibe configuracion con todas sus etructuras validas, la cantidad de viento, humedad, animo de gimli y legolas. Todas pasadas por parametro.
*post: Asigna todos los campos del struct configuracion.
*/

void pedir_configuracion(configuracion_t* configuracion){
	printf("Bienvenido a la configuracion del juego. Aca vas a poder configurar varias cosas a tu gusto. Y si no la quieres modificar, solo tenes que ingresar -1.\n");
	pedir_resistencia_torre(&((*configuracion).resistencia_torre_1), TORRE_1);
	pedir_resistencia_torre(&((*configuracion).resistencia_torre_2), TORRE_2);
	for(int i=0; i<CUARTO_NIVEL; i++){
		pedir_tropas(&((*configuracion).cant_enanos[i]), ENANOS, i+1);
		pedir_tropas(&((*configuracion).cant_elfos[i]), ELFOS, i+1);
	}	
	pedir_tropas_extra(&((*configuracion).cant_enanos_extra), ENANOS);
	pedir_tropas_extra(&((*configuracion).cant_elfos_extra), ELFOS);
	pedir_fallo(&((*configuracion).fallo_enanos), ENANOS);
	pedir_fallo(&((*configuracion).fallo_elfos), ELFOS);
	pedir_critico(&((*configuracion).critico_enanos), ENANOS);
	pedir_critico(&((*configuracion).critico_elfos), ELFOS);
	pedir_velocidad_juego(&((*configuracion).velocidad_juego));
	pedir_camino((*configuracion).ruta_camino);
}	

/*
*pre: Recibe configuracion, con todas sus estructuras validas, y el archivo configuracion, abierto en modo escritura.
*post: Escribe el archivo con los datos de configuracion.
*/
void escribir_configuracion(FILE * archivo_configuracion, configuracion_t configuracion){
	fprintf(archivo_configuracion, "RESISTENCIA_TORRES=%i,%i\n", configuracion.resistencia_torre_1, configuracion.resistencia_torre_2);
	fprintf(archivo_configuracion, "ENANOS_INICIO=%i,%i,%i,%i\n", configuracion.cant_enanos[0], configuracion.cant_enanos[1], configuracion.cant_enanos[2], configuracion.cant_enanos[3]);
	fprintf(archivo_configuracion, "ELFOS_INICIO=%i,%i,%i,%i\n", configuracion.cant_elfos[0], configuracion.cant_elfos[1], configuracion.cant_elfos[2], configuracion.cant_elfos[3]);
	fprintf(archivo_configuracion, "ENANOS_EXTRA=%i\n", configuracion.cant_enanos_extra);
	fprintf(archivo_configuracion, "ELFOS_EXTRA=%i\n", configuracion.cant_elfos_extra);
	fprintf(archivo_configuracion, "ENANOS_ANIMOS=%i,%i\n", configuracion.fallo_enanos, configuracion.critico_enanos);
	fprintf(archivo_configuracion, "ELFOS_ANIMOS=%i,%i\n", configuracion.fallo_elfos, configuracion.critico_elfos);
	fprintf(archivo_configuracion, "VELOCIDAD=%.2f\n", configuracion.velocidad_juego);
	fprintf(archivo_configuracion, "CAMINOS=%s\n", configuracion.ruta_camino);
}	



bool inicializar_creacion_config(char ruta_archivo[MAX_NOMBRE_COMANDO], configuracion_t* configuracion){
	FILE * archivo_configuracion=fopen(ruta_archivo, "w");
	if(!archivo_configuracion){
		printf("Error al abrir el archivo %s\n", ruta_archivo);
		return false;
	}	
	pedir_configuracion(configuracion);
	escribir_configuracion(archivo_configuracion, *configuracion);
	fclose(archivo_configuracion);
	return true;
}



bool leer_configuracion(char ruta_archivo[MAX_NOMBRE_COMANDO], configuracion_t* configuracion){
	FILE * archivo_configuracion = fopen(ruta_archivo, "r");
	if(!archivo_configuracion){
		printf("Error al abrir el archivo %s", ruta_archivo);
		return false;
	}	
	fscanf(archivo_configuracion, "RESISTENCIA_TORRES=%i,%i\n", &((*configuracion).resistencia_torre_1), &((*configuracion).resistencia_torre_2));
	fscanf(archivo_configuracion, "ENANOS_INICIO=%i,%i,%i,%i\n", &((*configuracion).cant_enanos[0]), &((*configuracion).cant_enanos[1]), &((*configuracion).cant_enanos[2]), &((*configuracion).cant_enanos[3]));
	fscanf(archivo_configuracion, "ELFOS_INICIO=%i,%i,%i,%i\n", &((*configuracion).cant_elfos[0]), &((*configuracion).cant_elfos[1]), &((*configuracion).cant_elfos[2]), &((*configuracion).cant_elfos[3]));
	fscanf(archivo_configuracion, "ENANOS_EXTRA=%i\n", &((*configuracion).cant_enanos_extra));
	fscanf(archivo_configuracion, "ELFOS_EXTRA=%i\n", &((*configuracion).cant_elfos_extra));
	fscanf(archivo_configuracion, "ENANOS_ANIMOS=%i,%i\n", &((*configuracion).fallo_enanos), &((*configuracion).critico_enanos));
	fscanf(archivo_configuracion, "ELFOS_ANIMOS=%i,%i\n", &((*configuracion).fallo_elfos), &((*configuracion).critico_elfos));
	fscanf(archivo_configuracion, "VELOCIDAD=%f\n", &((*configuracion).velocidad_juego));
	fscanf(archivo_configuracion, "CAMINOS=%s\n", (*configuracion).ruta_camino);
	fclose(archivo_configuracion);
	return true;
}	