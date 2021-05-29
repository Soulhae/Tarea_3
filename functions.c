#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "hashmap.h"


typedef struct{
   int numero;
   int coordenadas[2];
}Ciudad;

typedef struct{
   List* recorridas;
   List* faltantes;
   int distanciaRecorrida;
   char nombre[20];
}Recorrido;

void menu(){
    printf("\n- Menu -\n");
    printf("1.- Importar archivo.\n");
    printf("2.- Mostrar la distancia entre dos entregas.\n");
    printf("3.- Mostrar las tres entregas mas cercanas.\n");
    printf("4.- Generar ruta.\n");
    printf("5.- Generar ruta aleatoria.\n");
    printf("6.- Mejorar una ruta.\n");
    printf("7.- Mostrar todas las rutas.\n");
    printf("8.- Generar mejor ruta.\n");
    printf("9.- Salir\n");
    printf("\nIngrese opcion: ");
}

void leer_archivo(List* ciudades){

    char archivo[30];
    printf("Por favor ingrese el archivo que se desea leer: ");
    getchar();
    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivoEntrada = fopen(archivo, "r");
    if (archivoEntrada == NULL){
        printf("El archivo no se pudo abrir en modo lectura.\n");
        return;
    }

    int nombre = 1;
    char linea[20];
    while (fgets(linea, 20, archivoEntrada)){
        Ciudad* city = (Ciudad *)calloc(1,sizeof(Ciudad));
        char* coordenada;
        linea[strlen(linea) - 1] = '\0';
        coordenada = strtok(linea," ");
        city->numero = nombre;
        city->coordenadas[0] = atoi(coordenada);
        coordenada = strtok(NULL," ");
        city->coordenadas[1] = atoi(coordenada);
        nombre++;
        pushBack(ciudades,city);
    }

    if (fclose(archivoEntrada) == EOF){
        printf("El archivo no se pudo cerrar correctamente.");
    }
}

int distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y){
    return (int)sqrt((entrega1X-entrega2X)*(entrega1X-entrega2X) + (entrega1Y-entrega2Y)*(entrega1Y-entrega2Y));
}

void copiar_Ciudad(Ciudad* original, List* list){
    Ciudad* city = (Ciudad *)calloc(1,sizeof(Ciudad));
    int coordenada;
    coordenada = original->coordenadas[0];
    city->coordenadas[0] = coordenada;
    coordenada = original->coordenadas[1];
    city->coordenadas[1] = coordenada;
    coordenada = original->numero;
    city->numero = coordenada;
    pushBack(list,city);
}

Recorrido *ruta_aleatoria(List* ciudades, HashMap* recorridos){

    char nombreRecorrido[20];
    int puntoX;
    int puntoY;
    printf("Ingrese la coordenada 'x': ");
    scanf("%d",&puntoX);
    printf("Ingrese la coordenada 'y': ");
    scanf("%d",&puntoY);

    Recorrido* recorrido = (Recorrido *)calloc(1,sizeof(Recorrido));
    recorrido->faltantes = createList();
    recorrido->recorridas = createList();
    recorrido->faltantes = ciudades;
    Ciudad* total = lastList(ciudades);

    srand(getpid());
    int cantidad = rand() % total->numero + 1;
    Ciudad* buscada = firstList(ciudades);
    while(buscada->numero!=cantidad) buscada = nextList(ciudades);
    recorrido->distanciaRecorrida = distancia_dos_entregas(buscada->coordenadas[0], buscada->coordenadas[1], puntoX, puntoY);

    do{
        copiar_Ciudad(buscada,recorrido->recorridas);
        Ciudad* ciudadesRecorrer = (Ciudad*)calloc(1,sizeof(Ciudad));
        ciudadesRecorrer = nextList(ciudades);
        recorrido->distanciaRecorrida = distancia_dos_entregas(buscada->coordenadas[0], buscada->coordenadas[1], ciudadesRecorrer->coordenadas[0], ciudadesRecorrer->coordenadas[1])+recorrido->distanciaRecorrida;
        buscada = ciudadesRecorrer;
    }while(cantidad!=buscada->numero);

    printf("\nRecorrido creado con exito!\n");
    printf("\nIngrese el nombre del recorrido: ");
    getchar();
    fgets(nombreRecorrido, 20, stdin);
    strcpy(recorrido->nombre,nombreRecorrido);

    while(searchMap(recorridos,recorrido->nombre)){
        printf("El nombre ya esta ocupado, intente ingresando otro nombre!: ");
        fgets(nombreRecorrido, 20, stdin);
    }
    insertMap(recorridos,recorrido->nombre,recorrido);

    Ciudad* aux = firstList(recorrido->recorridas);
    printf("\nLa secuencia generada de ciudades es: ");
    printf("%d ",aux->numero);
    Ciudad* aux2 = nextList(recorrido->recorridas);
    while(aux!=aux2){
        printf("%d ",aux2->numero);
        aux2 = nextList(recorrido->recorridas);
    }

    printf("\nLa distancia total recorrida es: %d\n",recorrido->distanciaRecorrida);
    return recorrido;
}