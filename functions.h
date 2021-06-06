#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include "hashmap.h"

typedef struct Entrega Entrega;

typedef struct Ruta Ruta;

void menu();

void leer_archivo(List* entregas);

int distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y);

void copiar_Ciudad(Entrega* original, List* list);

Ruta *ruta_aleatoria(List* entregas, HashMap* rutas);

void mostrar_rutas(HashMap *rutas);

#endif /* FUNCTIONS_H */