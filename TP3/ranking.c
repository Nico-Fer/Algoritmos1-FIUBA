#include "defendiendo_torres.h"
#include "juego.h"
#include "caminos.h"
#include "configuracion.h"
#include "ranking.h"

/*
*pre: Recibe un string.
*post: Le asigna al string el nombre que el usuario eligio.
*/

void pedir_jugador(char jugador[MAX_NOMBRE_JUGADOR]){
	printf("Ingrese su nombre: ");
	scanf(" %s", jugador);
}

/*
*pre: Recibe los archivos ya abiertos, y jugador_en_ranking y jugador nuevos, con todas sus estructuras validas.
*post: Le asigna al archivo nuevo, los valores del archivo_ranking y el puntaje del jugador actual.
*/

void escribir_ranking_nuevo(FILE * archivo_ranking, FILE * ranking_nuevo, ranking_t jugador_en_ranking, ranking_t jugador_nuevo){
	int leidos;
	bool esta_insertado = false;
	leidos=fscanf(archivo_ranking, "%s;%i\n", jugador_en_ranking.jugador, &(jugador_en_ranking.puntaje));
	while(leidos==2 && !esta_insertado){
		if(jugador_nuevo.puntaje<jugador_en_ranking.puntaje){
			fprintf(ranking_nuevo, "%s;%i\n", jugador_en_ranking.jugador, jugador_en_ranking.puntaje);
		}	
		else{
			fprintf(ranking_nuevo, "%s;%i\n", jugador_nuevo.jugador, jugador_nuevo.puntaje);
			esta_insertado=true;
		}	
		leidos=fscanf(archivo_ranking, "%s;%i\n", jugador_en_ranking.jugador, &(jugador_en_ranking.puntaje));
	}	
	while(leidos==2){
		fprintf(ranking_nuevo, "%s;%i\n", jugador_en_ranking.jugador, jugador_en_ranking.puntaje);
		leidos=fscanf(archivo_ranking, "%s;%i\n", jugador_en_ranking.jugador, &(jugador_en_ranking.puntaje));
	}	
}



int inicializar_escritura_ranking(ranking_t jugador_nuevo, char ruta_archivo[MAX_NOMBRE_ARCHIVO]){
	ranking_t jugador_en_ranking;
	FILE * archivo_ranking = fopen(ruta_archivo, "r");
	if(!archivo_ranking){
		printf("Error al abrir al archivo.\n");
		return -1;
	}	
	FILE * ranking_nuevo = fopen("ranking_nuevo.csv", "w");
	if(!ranking_nuevo){
		printf("Error al abrir al archivo.\n");
		fclose(archivo_ranking);
		return -1;
	}
	pedir_jugador(jugador_nuevo.jugador);
	escribir_ranking_nuevo(archivo_ranking, ranking_nuevo, jugador_en_ranking, jugador_nuevo);
	fclose(ranking_nuevo);
	fclose(archivo_ranking);
	rename("ranking_nuevo.csv", ruta_archivo);
	return 1;
}			



void determinar_puntaje(int* puntaje, int orcos_muertos, int vida_torre_1, int vida_torre_2, int enanos, int elfos, int enanos_extra, int elfos_extra){
	*puntaje= (orcos_muertos*1000)/(vida_torre_2+vida_torre_1+enanos_extra+elfos_extra+enanos+elfos);
}	



void calcular_defensas_ranking(int* defensas_ranking, int defensores){
	*defensas_ranking = *defensas_ranking + defensores;
}



void calcular_vida_torres(int* vida_torre_1, int* vida_torre_2, int resistencia_torre_1, int resistencia_torre_2){
	*vida_torre_1=resistencia_torre_1;
	*vida_torre_2=resistencia_torre_2;
}

/*
*pre: Recibe ranking con todas sus estructuras validas, el archivo de ranking y la cantidad de personas a motrar.
*post: Lee el archivo ranking y lo muestra por pantalla.
*/

void leer_rankig(ranking_t ranking, FILE * archivo_ranking, int listar){
	int leidos;
	int contador = 0;
	leidos = fscanf(archivo_ranking, "%s;%i\n", ranking.jugador, &(ranking.puntaje));
	if(listar!= LISTAR_DEFAULT){
		while((contador<listar) && (leidos==2)){
			printf("%s;%i\n", ranking.jugador, ranking.puntaje);
			leidos = fscanf(archivo_ranking, "%s;%i\n", ranking.jugador, &(ranking.puntaje));
			contador++;
		}
	}	
	else{
		while(leidos==2){
			printf("%s;%i\n", ranking.jugador, ranking.puntaje);
			leidos = fscanf(archivo_ranking, "%s;%i\n", ranking.jugador, &(ranking.puntaje));
			contador++;
		}
	}
}



int inicializar_lectura_ranking(char ruta_archivo[MAX_NOMBRE_ARCHIVO], int listar){
	ranking_t ranking;
	FILE * archivo_ranking = fopen(ruta_archivo, "r");
	if(archivo_ranking==NULL){
		printf("Error al abrir el archivo %s", ruta_archivo);
		return -1;
	}	
	leer_rankig(ranking, archivo_ranking, listar);
	fclose(archivo_ranking);
	return 1;	
}	