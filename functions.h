#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include "treemap.h"

typedef struct Entrega Entrega;

typedef struct Ruta Ruta;

void menu();

/* Funcion para leer el archivo que contiene las coordenadas de las entregas del usuario. En esta funcion se le asigna a cada entrega su respectiva id y se almacena en la estructura 'Entrega'. */
void leer_archivo(List* entregas);

/* Funcion para obtener la distancia entre dos puntos previamente señalados. */
double distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y);

/* Funcion para obtener la distancia entre dos entregas indicadas por el usuario. */
void obtener_distancia(List *entregas);

/* Funcion para asignarle memoria y almacenar los datos de una entrega. */
void copiar_Ciudad(Entrega* original, List* list);

/* Funcion que genera una ruta aleatoria. Esta ruta se almacena en un mapa ordenado, en la cual su 'key' será la distancia total recorrida de la ruta. */
void ruta_aleatoria(List* entregas, TreeMap* rutas);

/* Funcion para obtener las tres entregas mas cercanas de acuerdo a un punto inicial dado por el usuario */
void entregas_cercanas(List* entregas, TreeMap* distancias_cercanas, int x, int y);

/* Funcion para mostrar todas las rutas almacenadas, las cuales son mostradas de menor a mayor de acuerdo a la distancia total recorrida de cada ruta. */
void mostrar_rutas(TreeMap *rutas);

/* Funcion para crear una ruta manualmente. El usuario elegira el camino a recorrer (orden de las entregas) de acuerdo a las id's de las entregas. */
void crear_ruta(List *entregas, TreeMap *rutas, int x, int y);

/*
 * Funcion para mejorar una ruta, en la cual se intercambian dos entregas. Estas entregas pueden ser elegidas manualmente o aleatoriamente. Si la distancia de la
 * ruta generada disminuye, se sustituye la ruta original por la ruta generada, en caso contrario, se mantiene la ruta original.
 */
void mejorar_ruta(TreeMap* rutas, List *entregas);

/* Funcion que genera la mejor ruta, la cual optimiza la distancia total recorrida. */
void mejor_ruta(List *entregas, TreeMap *rutas, int x, int y);

/* void Funcion8(TreeMap *rutas, List* entregas); Intento fallido de DFS */

#endif /* FUNCTIONS_H */