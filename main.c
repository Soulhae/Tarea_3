#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "functions.h"
#include "treemap.h"

typedef struct Entrega Entrega;

typedef struct Ruta Ruta;

double lower_than_double(void* key1, void* key2){
    double k1 = *((double*) (key1));
    double k2 = *((double*) (key2));
    return k1<k2;
}

int main(){

    List* entregas = createList();
    TreeMap* rutas = createTreeMap(lower_than_double);

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
                break;
            case 2:; /* Distancia entre dos entregas */
                obtener_distancia(entregas);
                break;
            case 3:; /* Mostrar las tres entregas mas cercanas de acuerdo a las coordenadas ingresadas */
                char coord[50];
                int x, y;
                printf("Ingrese las coordenadas (x,y): ");
                scanf("%s", coord);
                getchar();

                token = strtok(coord, ",");
                x = atoi(token);
                token = strtok(NULL, ",");
                y = atoi(token);

                TreeMap *distancias_cercanas = createTreeMap(lower_than_double);
                entregas_cercanas(entregas, distancias_cercanas, x, y);
                break;
            case 4:; /* Generar ruta */
                printf("Ingrese las coordenadas (x,y): ");
                scanf("%s", coord);
                getchar();

                token = strtok(coord, ",");
                x = atoi(token);
                token = strtok(NULL, ",");
                y = atoi(token);

                TreeMap *distancias = createTreeMap(lower_than_double);
                crear_ruta(entregas, rutas, x, y);
                break;
            case 5:; /* Generar ruta aleatoria */
                ruta_aleatoria(entregas, rutas);
                break;
            case 6:; /* Mejorar una ruta */
                mejorar_ruta(rutas, entregas);
                break;
            case 7: /* Mostrar todas las rutas */
                mostrar_rutas(rutas);
                break;
            case 8:; /* Generar mejor ruta */
                printf("Ingrese las coordenadas (x,y): ");
                scanf("%s", coord);
                getchar();

                token = strtok(coord, ",");
                x = atoi(token);
                token = strtok(NULL, ",");
                y = atoi(token);
                
                mejor_ruta(entregas, rutas, x, y);
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

    return 0;
}