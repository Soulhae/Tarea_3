#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ruta.h"

typedef struct Coordenadas Coordenadas;

struct Coordenadas{
    int num_entrega;
    int coord_x;
    int coord_y;
};

void bienvenida(){
    printf("\nAplicacion miau\n");
    printf("1.- Importar archivo de coordenadas.\n");
    printf("2.- Distancia entre dos entregas.\n");
    printf("3.- Mostrar las tres entregas mas cercanas.\n");
    printf("4.- Crear ruta.\n");
    printf("5.- Generar una ruta aleatoria.\n");
    printf("6.- Mejorar una ruta.\n");
    printf("7.- Mostrar todas las rutas.\n");
    printf("8.- Generar una ruta optima.\n");
    printf("9.- Salir.\n");
}

void leer_archivo(){

    char archivo[30];
    printf("\nPor favor ingrese el archivo que se desea leer: ");
    getchar();
    
    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivoEntrada = fopen(archivo, "r");
    if (archivoEntrada == NULL){
        printf("\nEl archivo no se pudo abrir, o no existe\n");
        return;
    }

    int num_coord;
    printf("Ingrese la cantidad de coordenadas: ");
    scanf("%d", &num_coord);

    char linea[1024];
    char *token;
    int num_entrega = 0;
    int coord_x;
    int coord_y;

    while (fscanf(archivoEntrada, "%[^\n]s", linea) != EOF){
        fgetc(archivoEntrada);

        num_entrega ++;
        token = strtok(linea, " ");
        coord_x = atoi(token);
        token = strtok(NULL, " ");
        coord_y = atoi(token);

        guardar_coord(num_entrega, coord_x, coord_y);

        if (num_entrega == num_coord) break;
    }

    if (fclose(archivoEntrada) == EOF){
        printf("\nEl archivo no se pudo cerrar correctamente.\n");
    }else{
        printf("\nEl archivo se leyo correctamente.\n");
    }

}

void guardar_coord(int num_entrega, int coord_x, int coord_y){

    Coordenadas *coordenadas = (Coordenadas *) malloc (sizeof(Coordenadas));
    coordenadas->num_entrega = num_entrega;
    coordenadas->coord_x = coord_x;
    coordenadas->coord_y = coord_y;
    printf("%d - %d\n", coordenadas->coord_x, coordenadas->coord_y);

}