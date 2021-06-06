#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct Entrega Entrega;

typedef struct Ruta Ruta;

void menu();

void leer_archivo(List* entregas);

double distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y);

void copiar_Ciudad(Entrega* original, List* list);

Ruta *ruta_aleatoria(List* entregas, TreeMap* rutas);

void entregas_cercanas(List* entregas, TreeMap* distancias, int x, int y);

int lower_than_int(void* key1, void* key2);

void mostrar_rutas(TreeMap *rutas);

#endif /* FUNCTIONS_H */