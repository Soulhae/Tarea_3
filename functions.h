#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include "treemap.h"

typedef struct Entrega Entrega;

typedef struct Ruta Ruta;

void menu();

void leer_archivo(List* entregas);

double distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y);

void copiar_Ciudad(Entrega* original, List* list);

Ruta *ruta_aleatoria(List* entregas, TreeMap* rutas);

void entregas_cercanas(List* entregas, TreeMap* distancias_cercanas, int x, int y);

void mostrar_rutas(TreeMap *rutas);

void crear_ruta(List *entregas, TreeMap *rutas, int x, int y);

void mejorar_ruta(TreeMap* rutas);

// void Funcion8(TreeMap *rutas, List* entregas); Intento fallido de DFS

#endif /* FUNCTIONS_H */