#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"
#include "hashmap.h"
#include "treemap.h"

typedef struct Entrega Entrega;

typedef struct Ruta Ruta;

int main(){

    List* entregas = createList();
    HashMap* rutas = createMap(80);

    int opcion;
    do{
        menu();
        scanf("%d", &opcion);
        printf("\n");

        char *token;
        char nombre_ruta[50];

        switch(opcion){

            case 1: /* Importar archivo */
                leer_archivo(entregas);
                printf("El archivo se leyo correctamente.\n");
                break;
            case 2:; /* Distancia entre dos entregas */
                char coord1[50], coord2[50];
                int x1, y1, x2, y2, distancia;
                printf("Ingrese la primera coordenada (x,y): ");
                scanf("%s", coord1);
                getchar();
                printf("Ingrese la segunda coordenada (x,y): ");
                scanf("%s", coord2);

                token = strtok(coord1, ",");
                x1 = atoi(token);
                token = strtok(NULL, ",");
                y1 = atoi(token);
                token = strtok(coord2, ",");
                x2 = atoi(token);
                token = strtok(NULL, ",");
                y2 = atoi(token);

                distancia = distancia_dos_entregas(x1, y1, x2, y2);
                printf("\nLa distancia entre las dos entregas es: %d\n", distancia);

                break;
            case 3:; /* Mostrar las tres entregas mas cercanas de acuerdo a coord. ingresadas */
                break;
            case 4: /* Generar ruta */
                break;
            case 5:; /* Generar ruta aleatoria */
                Ruta* ruta = ruta_aleatoria(entregas, rutas);
                break;
            case 6: /* Mejorar una ruta */
                break;
            case 7: /* Mostrar todas las rutas */
                mostrar_rutas(rutas);
                break;
            case 8: /* Generar mejor ruta */
                break;
            case 9: /* Salir */
                break;
            default:;
				opcion = 11;
				printf("Intentelo nuevamente.\n");
				getchar();
				break;
        }

    }while(opcion != 9);
}