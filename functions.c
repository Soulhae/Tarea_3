#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "list.h"
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

double distancia_dos_entregas(int entrega1X, int entrega1Y, int entrega2X, int entrega2Y){ //Esta funcion calcula la distancia en base de las coordenadas.
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

void ruta_aleatoria(List* entregas, TreeMap* rutas){ //Se creara una ruta aleatoria para las entregas

    Entrega *iterador = first(entregas);
    if(!iterador){
        printf("Aun no hay entregas ingresadas!\n");
        return;
    }

    char coord[50], *token;
    int punto_x, punto_y;
    printf("Ingrese la coordenada inicial (x,y): ");//Recibimos las coordenadas del usuario.
    scanf("%s", coord);
    getchar();

    token = strtok(coord, ",");
    punto_x = atoi(token);
    token = strtok(NULL, ",");
    punto_y = atoi(token);

    Ruta* ruta = (Ruta *)calloc(1,sizeof(Ruta)); //Se asigna memoria a ruta.
    ruta->faltantes = createList(); 
    ruta->recorridas = createList();//Se crea lista de las coordenadas faltantes y recorridas.
    ruta->faltantes = entregas; //Se ingresa a la lista de faltantes todas las coordenadas.

    srand(time(NULL));
    int cantidad = rand() % listSize(entregas) + 1; //Se ocupa rand para buscar una ID aleatoriamente.
    Entrega* buscada = first(entregas); //Usamos buscada para buscar la ID
    while(buscada)
    {
        if(buscada->id == cantidad) break;
        buscada = next(entregas); //Ciclo para buscar la ID y actualiza 
    } 

    ruta->distancia_recorrida = distancia_dos_entregas(buscada->coordenadas[0], buscada->coordenadas[1], punto_x, punto_y); //Ocupamos la funcion para calcular las coordenadas de la entrega con el punto del usuario.
    pushBack(ruta->recorridas, buscada);

    Entrega* ciudadesRecorrer = (Entrega*)calloc(1,sizeof(Entrega));
    
    int cont = listSize(entregas);
    for (int i = 0; i < cont-1; i++)
    {
        ciudadesRecorrer = next(entregas);
        if(ciudadesRecorrer == NULL) 
            ciudadesRecorrer = first(entregas);

        ruta->distancia_recorrida = distancia_dos_entregas(buscada->coordenadas[0], buscada->coordenadas[1], ciudadesRecorrer->coordenadas[0], ciudadesRecorrer->coordenadas[1])+ruta->distancia_recorrida;

        buscada = ciudadesRecorrer;
        pushBack(ruta->recorridas, buscada);
        
    }

    char nombreRecorrido[20];
    printf("\nRuta creada con exito!\n");
    printf("\nIngrese el nombre de la ruta: ");
    //getchar();
    fgets(nombreRecorrido, 20, stdin);
    strcpy(ruta->nombre,nombreRecorrido); 

    insertTreeMap(rutas,&ruta->distancia_recorrida,ruta); //Se ingresa la ruta hecha al mapa con su respectivo nombre.

    Entrega* aux = first(ruta->recorridas); 
    printf("\nLa secuencia generada de entregas es: "); //Muestra la ruta hecha por ID y la distancia que hizo esta ruta.
    
    
    while(aux){
        printf("%d ",aux->id);
        aux = next(ruta->recorridas);
    }

    printf("\nLa distancia total recorrida es: %.2lf\n",ruta->distancia_recorrida);

}

void obtener_distancia(List *entregas){

    int id1, id2;
    printf("Ingrese las id's de las entregas (id1 id2): ");
    scanf("%d %d", &id1, &id2);

    Entrega *primero = 0;
    Entrega *segundo = 0;
    

    /* Busca los datos de la primera id */
    Entrega *entrega = first(entregas);
    while(entrega){
        if(entrega->id == id1){
            primero = entrega;
            break;
        }
        entrega = next(entregas);
    }

    /* Busca los datos de la segunda id */
    entrega = first(entregas);
    while(entrega){
        if(entrega->id == id2){
            segundo = entrega;
            break;
        }
        entrega = next(entregas);
    }

    //printf("%d %d\n", primero->id, segundo->id);

    double distancia = distancia_dos_entregas(primero->coordenadas[0], primero->coordenadas[1], segundo->coordenadas[0], segundo->coordenadas[1]);
    printf("\nLa distancia entre las dos entregas es: %.2lf\n", distancia);

}

void mostrar_rutas(TreeMap *rutas){ //Esta funcion muestra las rutas desde la que recorre menos distancia hasta la que tiene mas distancia.

    Ruta *iterador = firstTreeMap(rutas);
    if(!iterador)
    {
        printf("Aun no hay rutas creadas!\n"); //En caso de que no haya una ruta creada retornamos.
        return;
    }
    printf("- Rutas -\n\n");
    while(iterador){
        printf("Nombre ruta: %s", iterador->nombre); 
        printf("La secuencia de la ruta es: ");
        Entrega* aux = first(iterador->recorridas);
        
        while(aux){ //
            printf("%d ",aux->id);
            aux = next(iterador->recorridas);
        }
        printf("\nLa distancia total recorrida es: %.2lf\n\n",iterador->distancia_recorrida); //Muestra en pantalla la distancia que recorre la ruta.
        iterador = nextTreeMap(rutas); //Se actualiza el iterador de rutas
    }

}

/* Se implementa un mapa ordenado con el fin de guardar las distancias ordenadas de menor a mayor, con su respectiva id */
void entregas_cercanas(List* entregas, TreeMap* distancias_cercanas, int x, int y){

    Entrega *iterador = first(entregas);
    if(!iterador)
    {
        printf("Aun no hay entregas ingresadas!\n");
        return;
    }

    while(iterador){
        iterador->distancia_punto = distancia_dos_entregas(iterador->coordenadas[0], iterador->coordenadas[1], x, y); //Ocupamos la funcion para calcular distancias.
        insertTreeMap(distancias_cercanas, &iterador->distancia_punto, iterador); //Insertamos en el mapa las distancias comparadas con el punto inicial.
        iterador = next(entregas); 
    }
    printf("\n");

    /* Para imprimir las tres primeras entregas ordendas por distancia */
    Entrega *aux = firstTreeMap(distancias_cercanas);
    if (aux == NULL) 
    {
        printf("No hay entregas disponibles.\n"); //En caso que el treemap se encuentre vacio se retorna.
        return;
    }

    printf("Las 3 entregas mas cercanas son: \n");
    printf("ID   Distancia\n");
    for (int i = 0 ; i < 3 ; i++){
        printf("%d %.2lf\n", aux->id, aux->distancia_punto); //Muestra por pantalla el ID de la entrega y la distancia a la que se encuentra del punto inicial.
        aux = nextTreeMap(distancias_cercanas);
    }
    
}

double lower_than_double2(void* key1, void* key2){
    double k1 = *((double*) (key1));
    double k2 = *((double*) (key2));
    return k1<k2;
}


List * copiarLista(List * lista) //Funcion para copiar una lista en otra
{
    List * nuevo = createList();

    Entrega * aux = first(lista);

    while(aux)
    {
        pushBack(nuevo, aux);
        aux = next(lista);
    }

    return nuevo;
}

void crear_ruta(List *entregas, TreeMap *rutas, int x, int y){ //Esta funcion calcula las distancias a partir de un punto inicial y el pide al usuario que indique el siguiente lugar de entrega.

    double distancia_total = 0;

    Ruta* ruta = (Ruta *)calloc(1,sizeof(Ruta));
    ruta->faltantes = createList();
    ruta->recorridas = createList();
    
    ruta->faltantes = copiarLista(entregas); //Se guarda en faltantes las entregas.

    while(listSize(ruta->faltantes) != 0){

        TreeMap *distancias = createTreeMap(lower_than_double2);
        Entrega *entrega = first(ruta->faltantes);

        while(entrega){ //Se calcula la distancia de los puntos comparados con el punto inicial.
            entrega->distancia_punto = distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y);
            insertTreeMap(distancias, &entrega->distancia_punto, entrega); //Se inserta en el mapa las distancias.
            entrega = next(ruta->faltantes);
        }

        Entrega *iterador = firstTreeMap(distancias);
        printf("\nID - Distancia\n");
        while(iterador){ //Muestra en pantalla la ID y la distancia de la entrega a partir del punto donde nos encontremos.
            printf("%d %.2lf\n", iterador->id, iterador->distancia_punto);
            iterador = nextTreeMap(distancias);
        }

        printf("\nIngrese la id de una entrega: ");
        int id;
        scanf("%d", &id); //Se le pide al usuario que ingrese la ID del siguiente punto de entrega.

        entrega = first(ruta->faltantes);

        while(entrega){
            if(entrega->id == id){
                distancia_total += distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y); //Suma la distancia del punto actual al punto de entrega.
                printf("Distancia recorrida al momento: %.2lf\n",distancia_total); //Muestra por pantalla cuanto se lleva recorrido.
                copiar_Ciudad(entrega, ruta->recorridas); //Se ingresa la ciudad visitada en ruta recorrida.
                popCurrent(ruta->faltantes); //Se saca de faltantes la entrega ya visitada.
                x = entrega->coordenadas[0];
                y = entrega->coordenadas[1];
                break;
            }
            entrega = next(ruta->faltantes);
        }
    }

    ruta->distancia_recorrida = distancia_total; //La distancia total se pasa a distancia recorrida de la ruta.

    char nombreRecorrido[20];
    printf("\nRuta creada con exito!\n");
    printf("\nIngrese el nombre de la ruta: "); //La ruta se creo con exito y se le pide al usuario que ingrese un nombre de la ruta.
    getchar();
    fgets(nombreRecorrido, 20, stdin);
    strcpy(ruta->nombre,nombreRecorrido);

    insertTreeMap(rutas,&ruta->distancia_recorrida,ruta); //Se ingresa la ruta hecha al mapa de rutas.

    Entrega* aux = first(ruta->recorridas);
    printf("\nLa secuencia generada de entregas es: ");
    
    while(aux){
        printf("%d ",aux->id);
        aux = next(ruta->recorridas);
    }

    printf("\nLa distancia total recorrida es: %.2lf\n",ruta->distancia_recorrida);
}

void mejorar_ruta(TreeMap* rutas, List *entregas){

    Ruta* aux = firstTreeMap(rutas);
    if(aux == NULL){
        printf("Aun no hay rutas generadas!\n");
        return;
    }

    char nombre[20];
    printf("Ingrese el nombre de la ruta buscada: ");
    getchar();
    fgets(nombre, 20, stdin);
    
    while(aux != NULL){
        if(strcmp(nombre, aux->nombre) == 0) break;
        aux = nextTreeMap(rutas);
    }

    if(aux == NULL){
        printf("No se encontro una ruta con ese nombre!\n");
        return;
    }
    
    printf("Ruta encontrada!\n");

    Entrega * ciudad = first(aux->recorridas);
    printf("Ruta: ");
    while(ciudad)
    {
        printf("%i ", ciudad->id);
        ciudad = next(aux->recorridas);
    }
    printf("\nDistancia recorrida: %.2lf", aux->distancia_recorrida);
    printf("\n");

    int opcion = 0;
    while(opcion != 1 && opcion != 2){   
        printf("Desea realizar un cambio manual (1) o automatico (2)? (Ingrese el numero de la opcion): ");
        scanf("%i", &opcion);
    }

    int id1, id2;
    if (opcion == 1){
        printf("Ingrese la ID de los 2 puntos a intercambiar: ");
        scanf("%i %i", &id1, &id2);
    }
    else{
        int cont = listSize(aux->recorridas);
        id1 = rand() % cont + 1 ;
        do{
            id2 = rand() % cont + 1;
        }while (id1 == id2);
    }

    printf("Intercambiar %i con %i. \n", id1, id2);

    Entrega *primero = 0;
    Entrega *segundo = 0;

    /* Busca los datos de la primera id */
    ciudad = first(aux->recorridas);
    while(ciudad){
        if(ciudad->id == id1){
            primero = ciudad;
            break;
        } 
        ciudad = next(aux->recorridas);
    }

    /* Busca los datos de la segunda id */
    ciudad = first(aux->recorridas);
    while(ciudad){
        if(ciudad->id == id2){
            segundo = ciudad;
            break;
        }
        ciudad = next(aux->recorridas);
    }

    Ruta* ruta_modificada = (Ruta *)calloc(1,sizeof(Ruta));
    ruta_modificada->faltantes = createList();
    ruta_modificada->recorridas = createList();
    Entrega *list_recorridas = first(aux->recorridas);
    while(list_recorridas){

        /* Si se encuentra la primera id, se ingresa a la lista por la segunda id o viceversa, sino, sigue el mismo recorrido */
        if (list_recorridas->id == primero->id){
            pushBack(ruta_modificada->recorridas, segundo);
        }else{
            if(list_recorridas->id == segundo->id){
                pushBack(ruta_modificada->recorridas, primero);
            }else{
                pushBack(ruta_modificada->recorridas, list_recorridas);
            }
        }
        list_recorridas = next(aux->recorridas);
    }

    Entrega *aux1 = first(ruta_modificada->recorridas);
    printf("\nLa secuencia generada de entregas es: ");
    while(aux1){
        printf("%d ",aux1->id, aux1->coordenadas[0], aux1->coordenadas[1]);
        aux1 = next(ruta_modificada->recorridas);
    }
    printf("\n");

    double distancia_total = 0;
    ruta_modificada->faltantes = copiarLista(ruta_modificada->recorridas);
    Entrega *entrega = first(ruta_modificada->faltantes);
    int x = entrega->coordenadas[0];
    int y = entrega->coordenadas[1];
    entrega = next(ruta_modificada->faltantes);
    int cont2 = listSize(ruta_modificada->faltantes);
    for(int i = 0 ; i < cont2 - 1 ; i++){
        distancia_total += distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y);
        copiar_Ciudad(entrega, ruta_modificada->recorridas);
        popCurrent(ruta_modificada->faltantes);
        x = entrega->coordenadas[0];
        y = entrega->coordenadas[1];
        entrega = next(ruta_modificada->faltantes);
    }
    ruta_modificada->distancia_recorrida = distancia_total;
    printf("Distancia nueva recorrida: %.2lf\n", ruta_modificada->distancia_recorrida);

    if (ruta_modificada->distancia_recorrida < aux->distancia_recorrida){
        //deleteNode(rutas, &aux->distancia_recorrida); /* Se cae :( */
        //insertTreeMap(rutas, &ruta_modificada->distancia_recorrida, ruta_modificada);
        Ruta *buscado = searchTreeMap(rutas, &aux->distancia_recorrida);

        Entrega *iterador_buscado = first(ruta_modificada->recorridas);
        clean(buscado->recorridas);
        while(iterador_buscado){
            pushBack(buscado->recorridas, iterador_buscado);
            iterador_buscado = next(ruta_modificada->recorridas);
        }
        buscado->distancia_recorrida = ruta_modificada->distancia_recorrida;
        printf("La ruta fue modificada!\n");
    }
    else{
        printf("La ruta no fue modificada!\n");
    }
}

void mejor_ruta(List *entregas, TreeMap *rutas, int x, int y){

    double distancia_total = 0;
    Ruta* ruta = (Ruta *)calloc(1,sizeof(Ruta));
    ruta->faltantes = createList();
    ruta->recorridas = createList();
    
    ruta->faltantes = copiarLista(entregas);

    while(listSize(ruta->faltantes) != 0){

        TreeMap *distancias = createTreeMap(lower_than_double2);
        Entrega *entrega = first(ruta->faltantes);

        while(entrega){
            entrega->distancia_punto = distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y);
            insertTreeMap(distancias, &entrega->distancia_punto, entrega);
            entrega = next(ruta->faltantes);
        }

        int id;
        Entrega *iterador = firstTreeMap(distancias);
        id = iterador->id;

        entrega = first(ruta->faltantes);
        while(entrega){
            if(entrega->id == id){
                distancia_total += distancia_dos_entregas(entrega->coordenadas[0], entrega->coordenadas[1], x, y);
                copiar_Ciudad(entrega, ruta->recorridas);
                popCurrent(ruta->faltantes);
                x = entrega->coordenadas[0];
                y = entrega->coordenadas[1];
                break;
            }
            entrega = next(ruta->faltantes);
        }
    }

    ruta->distancia_recorrida = distancia_total;

    char nombreRecorrido[20];
    strcpy(nombreRecorrido,"ruta optima\n");
    strcpy(ruta->nombre,nombreRecorrido);
    insertTreeMap(rutas,&ruta->distancia_recorrida,ruta);

    Entrega* aux = first(ruta->recorridas);
    printf("\nLa ruta optima es: ");
    while(aux){
        printf("%d ",aux->id);
        aux = next(ruta->recorridas);
    }

    printf("\nLa distancia total recorrida es: %.2lf\n",ruta->distancia_recorrida);

}


Ruta* CopiarRuta(Ruta* ruta){
    Ruta* new = (Ruta*)calloc(1,sizeof(Ruta));
    *new = *ruta;
    return new;
}

void RemoverEntrega(Entrega* entrega, Ruta* ruta){
    Entrega* aux = first(ruta->faltantes);
    while(aux)
    {
        if(aux->id == entrega->id){
            popCurrent(ruta->faltantes);
            break;
        }
        aux = next(ruta->faltantes);
    }
}

List* NodosAdj(Ruta* ruta){
    //List* list = createList();
    Ruta* nueva;
    Entrega* cont = first(ruta->faltantes);
    Entrega* aux2 = first(ruta->faltantes);
    Entrega* aux1 = first(ruta->recorridas);
    
    
    while(aux2)
    {
        nueva = CopiarRuta(ruta);
        Entrega* aux = (Entrega*)calloc(1,sizeof(Entrega));
        *aux = *aux2;
        RemoverEntrega(aux2,nueva);
        push(nueva->recorridas,aux);
        nueva->distancia_recorrida = distancia_dos_entregas(aux2->coordenadas[0],aux2->coordenadas[1],aux1->coordenadas[0],aux1->coordenadas[1])+nueva->distancia_recorrida;
        aux2 = next(ruta->faltantes);
    }
    
    return nueva->recorridas;
}

Ruta* DFS(Ruta* ruta){
    Stack* S = createStack();
    push(S, ruta);
    Ruta* final;
   
    while(listSize(S) != 0){
        Ruta* n= top(S);
        printf("a1\n");
        sleep(1);
        pop(S);
        printf("a2\n");
        sleep(1);

        if(listSize(n->faltantes)==0){
            printf("a5\n");
            sleep(1);
            final = (Ruta*)calloc(1,sizeof(Ruta));
            printf("a6\n");
            sleep(1);
            if(final->distancia_recorrida<n->distancia_recorrida){
                final = n;
            }
        }
        else
        {
            List* l=NodosAdj(n);
            Ruta* adj=first(l);
            
            while(adj)
            {
                push(S,adj);
                adj=next(l);
                //printf("a10\n");
                //sleep(1); 
            }
            printf("stack llenado: %i \n", listSize(S));
            sleep(1);

            free(n);
            
        }
    }
    printf("salio while\n");
    sleep(1);

    

	return final;
}

void Funcion8(TreeMap *rutas, List* entregas){
    printf("ingrese la coordenada x: ");
    int x;
    scanf("%d",&x);
    printf("ingrese la coordenada y: ");
    int y;
    scanf("%d",&y);
    Entrega* inicio = (Entrega*)calloc(1,sizeof(Entrega));
    inicio->coordenadas[0] = x;
    inicio->coordenadas[1] = y;
    Ruta* ruta = (Ruta*)calloc(1,sizeof(Ruta));
    ruta->faltantes = createList();
    ruta->recorridas = createList();
    ruta->faltantes = entregas;
    pushBack(ruta->recorridas,inicio);
    List* lista = createList();
    Entrega* axu = first(entregas);
    while(axu){
      pushBack(lista,axu);
      axu=next(entregas);          
    };

    ruta->faltantes = lista;
    ruta = DFS(ruta);
    printf("a13\n");
    sleep(1);
    printf("La ruta mas optima es la siguiente: \n");
    Entrega* cont = first(ruta->recorridas);
    //Entrega* cont1 = first(ruta->recorridas);
    printf("a14\n");
    sleep(1);
    int cont3 = listSize(ruta->recorridas);
    printf("a15\n");
    sleep(1);
    for(int i=0; i < cont3 ; i++)
    {
      printf("%d\n",cont->id);
      printf("a16\n");
        sleep(1);
      cont=next(ruta->recorridas);   
      printf("a17\n");
        sleep(1);       
    }
    printf("La distancia en esta ruta es de %d\n",ruta->distancia_recorrida);
    strcpy(ruta->nombre, "ruta optima");
    insertTreeMap(rutas,&ruta->distancia_recorrida,ruta);
}
