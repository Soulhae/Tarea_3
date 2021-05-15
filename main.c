#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ruta.h"

int main(){

    int opcion;
    do{
        bienvenida();
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);

        switch(opcion){

            case 1: /* Leer archivo */
                leer_archivo();
                break;
            case 2: /* Obtener distancia entre dos entregar */
                break;
            case 3: /* Mostrar tres entregas mas cercanas */
                break;
            case 4: /* Crear ruta */
                break;
            case 5: /* Generar una ruta aleatoria */
                break;
            case 6: /* Mejorar una ruta */
                break;
            case 7: /* Mostrar todas las rutas guardadas */
                break;
            case 8: /* Generar una ruta optima */
                break;
            case 9: /* Salir */
                break;
            default:
				printf("Intentelo nuevamente.\n");
				getchar();
				break;
        }

    }while(opcion != 9);

    return 0;
}
