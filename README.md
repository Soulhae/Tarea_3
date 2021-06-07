# Tarea 3 Entregas

## Nota para el usuario

* Importar: El archivo .csv debe estar en la carpeta donde se compila el programa.
* Case sensitive : El programa toma como diferentes, por ejemplo, ruta y Ruta, OJO!!.
* Para compilar y ejecutar : 
```
    gcc main.c list.c functions.c treemap.c stack.c -o Tarea3
    ./Tarea3
```

## Detalles

* Caso 6 (mejorar ruta): En el caso que la distancia de la ruta modificada sea menor
* que la distancia de la ruta original, en un comienzo intentamos eliminar la ruta
* original del mapa ordenado 'rutas' (donde se almacenan todas las rutas) para luego
* insertar la ruta original y estas sean ordenadas nuevamente, de acuerdo a su distancia,
* pero con la funcion de 'eraseMap' el programa se caia (lo dejamos comentado en el
* código - linea 470). Lo que tuvimos que hacer fue reemplazar los datos de la ruta original
* por los datos de la ruta modifcada, pero luego de realizar esto y mostrar todas las rutas
* (opción 7), estas no seran necesariamente mostradas en orden de acuerdo a su distancia.
*
* Caso 8 (encontrar la mejor ruta): Se utilizo un algortimo voraz, ya que no logramos hacer
* funcionar el algoritmo de busqueda a tiempo. Entendemos que no es necesariamente la ruta
* mas corta, pero es la única solución que encontramos.


## Aspectos positivos y a mejorar por el grupo

Ignacio Price-> Aspectos positivos: - Altos conocimientos en estructuras y punteros.
                                    - Buen liderazgo y apoyo.
                Aspectos a mejorar: - Mejorar legibilidad.
                                    - Mayor orden en el código.

Matias Burgos-> Aspectos positivos: - Buenos comentarios aportando al equipo.
                                    - Se esfuerza por ayudar a sus compañeros.
                Aspectos a mejorar: - Es terco con sus decisiones.

Nicolás Barraza-> Aspectos positivos: - Aporta el equipo con comentarios.
                                      - Código fácil de entender.
                  Aspectos a mejorar: - Mayor comunicación.

Benjamín Herrera-> Aspectos positivos: - Alto pensamiento analitico.
                                       - Ayuda al equipo a solucionar errores.
                   Aspectos a mejorar: - Trabajar más para ayudar al equipo.

Eyleen Sánchez-> Aspectos positivos: - Comenta sus funciones para saber que falta.
                                     - Orden en el código.
                 Aspectos a mejorar: - Contar más con el equipo.
 
## Puntos de premio/castigo

Nicolás Barraza-> 0
Benjamín Herrera-> 0
Ignacio Price-> 0
Matias Burgos-> 0
Eyleen Sánchez-> 0