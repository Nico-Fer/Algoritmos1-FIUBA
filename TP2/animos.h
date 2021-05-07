#ifndef __ANIMOS_H__
#define  __ANIMOS_H__

static const char ANIMO_MALO = 'M';
static const char ANIMO_REGULAR = 'R';
static const char ANIMO_BUENO = 'B';
static const int VELOCIDAD_VIENTO_MAXIMA = 75;
static const int VELOCIDAD_VIENTO_MEDIA = 50;
static const int VELOCIDAD_VIENTO_MINIMA = 25;
static const int HUMEDAD_MANIANA = 75;
static const int HUMEDAD_NOCHE = 50;
static const int HUMEDAD_TARDE = 25;

void animos(int* viento, int* humedad, char* animo_legolas, char* animo_gimli);

#endif