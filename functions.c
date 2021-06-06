#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct{
   int id; /* id */
   int coordenadas[2]; /* [0] -> x - [1] -> y */
   double distancia_punto;
}Entrega;

typedef struct{
   List* recorridas;
   List* faltantes;
   double distancia_recorrida;
   char nombre[20];
}Ruta;

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

void leer_archivo(List* entregas){

    char archivo[30];
    printf("Por favor ingrese el archivo que se desea leer: ");
    getchar();
    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivo_entrada = fopen(archivo, "r");
    if (archivo_entrada == NULL){
        printf("El archivo no se pudo abrir en modo lectura.\n");
        return;
    }

    int nombre = 1;
    char linea[20];
    while (fgets(linea, 20, archivo_entrada)){
        Entrega* entrega = (Entrega *)calloc(1,sizeof(Entrega));
        char* coordenada;
        linea[strlen(linea) - 1] = '\0';
        coordenada = strtok(linea," ");
        entrega->id = nombre;
        entrega->coordenadas[0] = atoi(coordenada);
        coordenada = strtok(NULL," ");
        entrega->coordenadas[1] = atoi(coordenada);
        nombre++;
        pushBack(entregas,entrega);
    }

    if (fclose(archivo_entrada) == EOF){
        printf("El archivo no se pudo cerrar correctamente.");
    }
}

double distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y){
    return (double) sqrt((entrega1X-entrega2X)*(entrega1X-entrega2X) + (entrega1Y-entrega2Y)*(entrega1Y-entrega2Y));
}

void copiar_Ciudad(Entrega* original, List* list){
    Entrega* entrega = (Entrega *)calloc(1,sizeof(Entrega));
    int coordenada;
    coordenada = original->coordenadas[0];
    entrega->coordenadas[0] = coordenada;
    coordenada = original->coordenadas[1];
    entrega->coordenadas[1] = coordenada;
    coordenada = original->id;
    entrega->id = coordenada;
    pushBack(list,entrega);
}

Ruta *ruta_aleatoria(List* entregas, HashMap* rutas){

    char coord[50], *token;
    int punto_x, punto_y;
    printf("Ingrese la coordenada inicial (x,y): ");
    scanf("%s", coord);
    getchar();

    token = strtok(coord, ",");
    punto_x = atoi(token);
    token = strtok(NULL, ",");
    punto_y = atoi(token);

    Ruta* ruta = (Ruta *)calloc(1,sizeof(Ruta));
    ruta->faltantes = createList();
    ruta->recorridas = createList();
    ruta->faltantes = entregas;
    Entrega* total = lastList(entregas);

    //srand(getpid());
    int cantidad = rand() % total->id + 1;
    Entrega* buscada = firstList(entregas);
    while(buscada->id!=cantidad) buscada = nextList(entregas);
    ruta->distancia_recorrida = distancia_dos_entregas(buscada->coordenadas[0], buscada->coordenadas[1], punto_x, punto_y);

    do{
        copiar_Ciudad(buscada,ruta->recorridas);
        Entrega* ciudadesRecorrer = (Entrega*)calloc(1,sizeof(Entrega));
        ciudadesRecorrer = nextList(entregas);
        ruta->distancia_recorrida = distancia_dos_entregas(buscada->coordenadas[0], buscada->coordenadas[1], ciudadesRecorrer->coordenadas[0], ciudadesRecorrer->coordenadas[1])+ruta->distancia_recorrida;
        buscada = ciudadesRecorrer;
    }while(cantidad!=buscada->id);

    char nombreRecorrido[20];
    printf("\nRuta creada con exito!\n");
    printf("\nIngrese el nombre de la ruta: ");
    //getchar();
    fgets(nombreRecorrido, 20, stdin);
    strcpy(ruta->nombre,nombreRecorrido);

    while(searchMap(rutas,ruta->nombre)){
        printf("El nombre ya esta ocupado, intente ingresando otro nombre!: ");
        fgets(nombreRecorrido, 20, stdin);
    }
    insertMap(rutas,ruta->nombre,ruta);

    Entrega* aux = firstList(ruta->recorridas);
    printf("\nLa secuencia generada de entregas es: ");
    printf("%d ",aux->id);
    Entrega* aux2 = nextList(ruta->recorridas);
    while(aux!=aux2){
        printf("%d ",aux2->id);
        aux2 = nextList(ruta->recorridas);
    }

    printf("\nLa distancia total recorrida es: %.2lf\n",ruta->distancia_recorrida);
    return ruta;

}

void mostrar_rutas(HashMap *rutas){

    Ruta *iterador = firstMap(rutas);
    printf("- Rutas -\n\n");
    while(iterador){
        printf("Nombre ruta: %s", iterador->nombre);
        Entrega* aux = firstList(iterador->recorridas);
        printf("La secuencia de la ruta es: ");
        printf("%d ",aux->id);
        Entrega* aux2 = nextList(iterador->recorridas);
        while(aux!=aux2){
            printf("%d ",aux2->id);
            aux2 = nextList(iterador->recorridas);
        }
        printf("\nLa distancia total recorrida es: %.2lf\n\n",iterador->distancia_recorrida);
        iterador = nextMap(rutas);
    }

}

double lower_than_double(void* key1, void* key2){
    double k1 = *((double*) (key1));
    double k2 = *((double*) (key2));
    return k1<k2;
}

/* - ARREGLAR - */
/* Se implementa un mapa ordenado con el fin de guardar las distancias ordenadas de menor a mayor, con su respectiva id */
void entregas_cercadas(List* entregas, int x, int y){

    TreeMap *distancias = createTreeMap(lower_than_double);

    Entrega *aux_iterador = lastList(entregas);
    int cantidad = aux_iterador->id;
    Entrega *iterador = firstList(entregas);
    for(int i = 0 ; i < cantidad ; i++){
        iterador->distancia_punto = distancia_dos_entregas(iterador->coordenadas[0], iterador->coordenadas[1], x, y);
        printf("%d %.2lf\n", iterador->id, iterador->distancia_punto);
        insertTreeMap(distancias, &iterador->distancia_punto, iterador);
        iterador = nextList(entregas);
    }
    printf("\n");

    /* Para imprimir las tres primeras entregas ordendas por distancia */
    Entrega *aux = firstTreeMap(distancias);
    if (aux == NULL) printf("No hay entregas disponibles.\n");
    while (aux){
        printf("%d %.2lf\n", aux->id, aux->distancia_punto);
        aux = nextTreeMap(distancias);
    }
    printf("fin\n");
    
}