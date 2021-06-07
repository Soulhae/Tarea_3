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
        printf("El archivo no se pudo cerrar correctamente.\n");
    }else printf("El archivo se leyo correctamente.\n");
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

Ruta *ruta_aleatoria(List* entregas, TreeMap* rutas){

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

    insertTreeMap(rutas,&ruta->distancia_recorrida,ruta);

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

void mostrar_rutas(TreeMap *rutas){

    Ruta *iterador = firstTreeMap(rutas);
    if(!iterador)
    {
        printf("Aun no hay rutas creadas!\n");
        return;
    }
    printf("- Rutas -\n\n");
    while(iterador){
        printf("Nombre ruta: %s", iterador->nombre);
        printf("La secuencia de la ruta es: ");
        Entrega* aux = firstList(iterador->recorridas);
        printf("%d ",aux->id);
        Entrega* aux2 = nextList(iterador->recorridas);
        while(aux!=aux2){
            printf("%d ",aux2->id);
            aux2 = nextList(iterador->recorridas);
        }
        printf("\nLa distancia total recorrida es: %.2lf\n\n",iterador->distancia_recorrida);
        iterador = nextTreeMap(rutas);
    }

}

/* Se implementa un mapa ordenado con el fin de guardar las distancias ordenadas de menor a mayor, con su respectiva id */
void entregas_cercanas(List* entregas, TreeMap* distancias_cercanas, int x, int y){

    Entrega *iterador = firstList(entregas);
    if(!iterador)
    {
        printf("Aun no hay entregas ingresadas!\n");
        return;
    }

    Entrega *aux_iterador = lastList(entregas);
    int cantidad = aux_iterador->id;

    for(int i = 0 ; i < cantidad ; i++){
        iterador->distancia_punto = distancia_dos_entregas(iterador->coordenadas[0], iterador->coordenadas[1], x, y);
        insertTreeMap(distancias_cercanas, &iterador->distancia_punto, iterador);
        iterador = nextList(entregas);
    }
    printf("\n");

    /* Para imprimir las tres primeras entregas ordendas por distancia */
    Entrega *aux = firstTreeMap(distancias_cercanas);
    if (aux == NULL) 
    {
        printf("No hay entregas disponibles.\n");
        return;
    }

    printf("Las 3 entregas mas cercanas son: \n");
    printf("ID   Distancia\n");
    for (int i = 0 ; i < 3 ; i++){
        printf("%d %.2lf\n", aux->id, aux->distancia_punto);
        aux = nextTreeMap(distancias_cercanas);
    }
    
}

double lower_than_double2(void* key1, void* key2){
    double k1 = *((double*) (key1));
    double k2 = *((double*) (key2));
    return k1<k2;
}


List * copiarLista(List * lista)
{
    List * nuevo = createList();
    int cont = listSize(lista);

    Entrega * aux = firstList(lista);

    for (int i = 0; i < cont; i++)
    {
        pushBack(nuevo, aux);
        aux = nextList(lista);
    }

    return nuevo;
}

void crear_ruta(List *entregas, TreeMap *rutas, int x, int y){

    double distancia_total = 0;

    Ruta* ruta = (Ruta *)calloc(1,sizeof(Ruta));
    ruta->faltantes = createList();
    ruta->recorridas = createList();
    
    ruta->faltantes = copiarLista(entregas);

    while(listSize(ruta->faltantes) != 0){

        TreeMap *distancias = createTreeMap(lower_than_double2);
        Entrega *entrega = firstList(ruta->faltantes);

        int cont = listSize(ruta->faltantes);

        for(int i = 0 ; i < cont ; i++){
            entrega->distancia_punto = distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y);
            insertTreeMap(distancias, &entrega->distancia_punto, entrega);
            entrega = nextList(ruta->faltantes);
        }

        Entrega *iterador = firstTreeMap(distancias);
        printf("\nID - Distancia\n");
        while(iterador){
            printf("%d %.2lf\n", iterador->id, iterador->distancia_punto);
            iterador = nextTreeMap(distancias);
        }

        printf("\nIngrese la id de una entrega: ");
        int id;
        scanf("%d", &id);

        entrega = firstList(ruta->faltantes);

        for(int i = 0 ; i < cont ; i++){
            if(entrega->id == id){
                distancia_total += distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y);
                printf("Distancia recorrida al momento: %.2lf\n",distancia_total);
                copiar_Ciudad(entrega, ruta->recorridas);
                popCurrent(ruta->faltantes);
                x = entrega->coordenadas[0];
                y = entrega->coordenadas[1];
                break;
            }
            entrega = nextList(ruta->faltantes);
        }
    }

    ruta->distancia_recorrida = distancia_total;

    char nombreRecorrido[20];
    printf("\nRuta creada con exito!\n");
    printf("\nIngrese el nombre de la ruta: ");
    getchar();
    fgets(nombreRecorrido, 20, stdin);
    strcpy(ruta->nombre,nombreRecorrido);

    insertTreeMap(rutas,&ruta->distancia_recorrida,ruta);

    Entrega* aux = firstList(ruta->recorridas);
    printf("\nLa secuencia generada de entregas es: ");
    printf("%d ",aux->id);
    Entrega* aux2 = nextList(ruta->recorridas);
    while(aux!=aux2){
        printf("%d ",aux2->id);
        aux2 = nextList(ruta->recorridas);
    }

    printf("\nLa distancia total recorrida es: %.2lf\n",ruta->distancia_recorrida);
}

void mejorar_ruta(TreeMap* rutas)
{
    Ruta* aux = firstTreeMap(rutas);
    if(!aux)
    {
        printf("Aun no hay rutas generadas!\n");
        return;
    }

    char nombre[50];
    printf("Ingrese el nombre de la ruta buscada: \n");
    scanf("%s", &nombre);
    getchar();
    
    while(!aux)
    {
        if(strcmp(nombre, aux->nombre) == 0) break;
        aux = nextTreeMap(rutas);
    }

    if(!aux)
    {
        printf("No se encontro una ruta con ese nombre!\n");
        return;
    }
    
    printf("Ruta encontrada!\n");
    
    Entrega * ciudad = firstList(aux->recorridas);
    int cont = listSize(aux->recorridas);
    printf("Ruta: ");
    for(int i = 0; i < cont; i++)
    {
        printf("%i ", ciudad->id);
        ciudad = nextList(aux->recorridas);
    }
    printf("- Distancia recorrida: %.2lf", aux->distancia_recorrida);
    printf("\n");

    int opcion = 0;
    while(opcion != 1 && opcion != 2)
    {   
        printf("Desea realizar un cambio manual (1) o automatico (2)?: (Ingrese el numero de la opcion)\n");
        scanf("%i", &opcion);
    }

    int id1, id2;
    if (opcion == 1)
    {
        printf("Ingrese la ID de los 2 puntos a intercambiar: ");
        scanf("%i %i", &id1, &id2);
    }
    else
    {
        id1 = rand() % (cont + 1);
        do
        {
            id2 = rand() % (cont + 1);
        } while (id1 == id2);
    }

    printf("Intercambiar %i con %i. \n", id1, id2);

    int primero;

    ciudad = firstList(aux->recorridas);
    printf("Ruta: ");
    for(int i = 0; i < cont; i++)
    {
        if(ciudad->id == id1 || ciudad->id == id2)
        printf("%i ", ciudad->id);
        ciudad = nextList(aux->recorridas);
    }


    


}