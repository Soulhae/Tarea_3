#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include "hashmap.h"

typedef struct Ciudad Ciudad;

typedef struct Recorrido Recorrido;

void menu();

void leer_archivo(List* ciudades);

int distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y);

void copiar_Ciudad(Ciudad* original, List* list);

Recorrido *ruta_aleatoria(List* ciudades, HashMap* recorridos);

#endif /* FUNCTIONS_H */