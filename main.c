#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"
#include "hashmap.h"

int main(){
    List* ciudades = createList();
    HashMap* recorridos = createMap(80);
    LeerArchivo(ciudades);
    Recorrido* ruta = RutaAleatoria(ciudades,recorridos);
    int pausa;
    printf("fin");
    scanf("&d",pausa);
}