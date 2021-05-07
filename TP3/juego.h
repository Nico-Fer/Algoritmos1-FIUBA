#ifndef __JUEGO_H__
#define  __JUEGO_H__

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

static const int MAX_CANT_TORRES =  2;
static const int MAX_CANT_ENTRADAS =  2;

#define MAX_NOMBRE_COMANDOS 50

/*
*pre: Recibe el terreno y su tope.
*post: Muestra por pantalla el terreno del nivel actual.
*/

void mostrar_terreno(int tope_terreno, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]);

/*
pre: Recibe el nivel con todas sus estructuras validas.
post: Muestra por pantalla la cantidad de columnas de la matriz segun el nivel.
*/

void presentacion_columnas(int nivel_actual);

/*
pre: Recibe la matriz terreno y el tope terreno ya validados.
post: Le asigna a cada elemento de la matriz un valor.
*/

void inicializar_terreno(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], int tope_terreno);

/*
pre: Recibe en que nivel esta y el tope del terreno pasado por referencia.
post: Se le asigna un valor al tope del terreno segun el nivel.
*/

void determinar_tope_terreno(int nivel_actual, int* tope_terreno);

/*
pre:Recibe el juego con todas sus estructuras validas.
post:Le asigna un caracter a la matriz donde se encuentran las entradas.
*/

void asignar_entradas(juego_t juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]);

/*
pre: Recibe el terreno ya inicializado.
post:Le asigna un caracter a la matriz donde se encuentra el camino.
*/

void asignar_caminos(char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2);

/*
pre: Recibe el juego con todas sus estructuras validas.
post:Le asigna un caracter a la matriz donde se encuentran las torres.
*/

void asignar_torres(juego_t juego, char terreno[MAX_LONGITUD_CAMINO][MAX_LONGITUD_CAMINO]);

/*
pre: Recibe el animo ya validado y el critico pasado por referencia.
post: Le asigna el porcentaje de critico segun el animo.
*/

void determinar_critico(char animo, int* critico);

/*
pre:Recibe el nivel de viento ya validado, y el fallo recibido como parametro.
post: Le asigna el porcentaje de fallo a los elfos segun el nivel de viento.
*/

void determinar_fallo_legolas(int viento, int* fallo );

/*
pre: Recibe el nivel de humedad ya validado, y el fallo recibido como parametro.
post: Le asigna el porcentaje de fallo a los enanos segun el nivel de humedad.
*/

void determinar_fallo_gimli(int humedad, int* fallo );

/*
pre:Recibe el nivel con todas sus estructuras validas.
post: Le asigna una posicion al defensor, si asi es deseado.
*/

void agregar_defensor_extra(juego_t* juego, coordenada_t posicion);

/*
pre: Recibe nivel con todas sus estructuras validas.
post: Le asigna las coordenadas a las entradas segun el nivel.
*/

void inicializar_entrada(juego_t nivel, coordenada_t entrada[MAX_CANT_ENTRADAS]);

/*
pre: Recibe el nivel con todas sus estructuras validas.
post: Le asigna las coordenadas a las torres segun el nivel.
*/

void inicializar_torre(juego_t nivel, coordenada_t torre[MAX_CANT_TORRES]);

/*
pre: Recibe a juego con todas sus estructuras validas.
post: Le asigna el maximo de enemigos, dependiendo el nivel.
*/

void inicializar_max_enemigos(juego_t* juego);

/*
pre: Recibe a juego con todas sus estructuras validas y los vectores entrada y torre.
post: Inicializara el nivel correspondiente, asignandole la posicion a las torres y entradas, obteniendo el camino,
*     inicializando los topes en 0 e inicializando al maximo de enemigos.
*/

void inicializar_nivel_default(juego_t* juego, coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t torre[MAX_CANT_TORRES]);

/*
pre: Recibe el nivel con todas sus estructuras validas, las coordenadas da la torre y la entrada deben ser validas.
post: Generara un camino desde la entrada hasta la torre.
*/

void obtener_caminos(coordenada_t entrada[MAX_CANT_ENTRADAS], coordenada_t torre[MAX_CANT_TORRES], juego_t* nivel);

/*
pre: Recibe el juego con todas sus estructuras validas.
post: Asigna las defensas segun el nivel.
*/

void asignar_defensas_default(juego_t* juego, coordenada_t posicion, int* enanos_ranking, int* elfos_ranking);

/*
pre: Recibe a juego y posicion con todas sus estructuras validas, y el tipo de defensor.
post: Asigna la posicion al defensor.
*/

void seleccion_posicion_defensor(juego_t* juego, coordenada_t* posicion, char tipo);

void presentacion_nivel_ganado();

void jugar_juego_default(int* orcos_muertos, char ruta_archivo_repe[MAX_NOMBRE_COMANDOS], int* enanos_ranking, int* elfos_ranking, int* vida_torre_1_ranking, int* vida_torre_2_ranking, juego_t* juego);

/*
*pre: Recibe al vector de enemigos, con todas sus estructuras validas, su tope, la cantidad de orcos muertos, pasado por parametro.
*post; determina la cantidad de orcos muertos.
*/

void contar_orcos_muertos(int* orcos_muertos, enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos);

#endif