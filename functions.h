#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "list.h"
#include "hashmap.h"

typedef struct Ciudad Ciudad;

typedef struct Recorrido Recorrido;

void LeerArchivo(List* ciudades);

Recorrido * RutaAleatoria(List* ciudades, HashMap* recorridos);

#endif /* FUNCTIONS_H */