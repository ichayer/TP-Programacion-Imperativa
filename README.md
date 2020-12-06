# Trabajo práctico final de Programación Imperativa 09/12/2020.

El proyecto permite procesar la información de los árboles censados en distintas ciudades del mundo.
Su objetivo principal es la resolución de ciertas consultas (queries) específicas,
En el siguiente archivo, se detallará cómo generar los ejecutables y cómo ejecutarlos. 

# MAKEFILE

      make all 
      make clean 
      
El comando "make all" se encarga de generar los dos ejecutables pedidos:

      arbolesADTBUE y arbolesADTVAN 

El comando "make clean" eliminará todos los archivos generados por el makefile.

Para el trabajo práctico analizaremos la ciudad de Vancouver y de Buenos Aires. Si se quisiera generar un ejecutable de una ciudad en particular, ejecutar alguno de los siguientes comandos:

      make arbolesADTBUE 
      make arbolesADTVEN 

# Compilación
Se debe reemplazar en CSV.h las columnas de interés para procesar los datos de Vancouver y de Buenos Aires de manera correcta.

      NEIGH_FILE : archivo de los barrios (leer sección de Ejecución).
      TREE_FILE  : archivo de los arboles (leer seccion de Ejecución).
      NEIGH_NAME : columna de los barrios del archivo CSV de los barrios.
      NEIGH_POP  : columna de la cantidad de habitantes del archivo CSV de los barrios.
      SPNAME     : columna del nombre cientifico de los árboles del archivo CSV de los árboles
      NEIGH_TREE : columna del barrio donde se ubican los distintos árboles del archivo CSV de los árboles.

Supongamos que quisieramos procesar los datos de otra ciudad, por ejemplo, la ciudad de París. Entonces en el makefile se deben agregar las siguientes líneas:
      
      OUTPUT_FILE_PAR=arbolesADTPAR

      arbolesADTPAR:
            $(COMPILER) $(CFLAGS) -o $(OUTPUT_FILE_PAR) $(FILES) -D PAR

Además, se deben definir en el CSV.h las columnas donde se encuentra la información que desea procesarse.

# Ejecución
Si se desea procesar los archivos CSV de Buenos Aires y se llaman arboles.csv y barrios.csv y están en el mismo directorio que el ejecutable arbolesADTBUE, el programa se puede invocar como: 

      $> ./arbolesADTBUE barrios.csv arboles.csv

Si se define NEIGH_FILE 1  TREE_FILE 2 en el archivo CSV.h.
 
Si se mantienen las mismas constantes y ambos archivos CSV se llaman arb.csv y bar.csv y además están en el directorio superior al ejecutable arbolesADTBUE, se invocará como 
 
      $> ./arbolesADTBUE ../bar.csv ../arb.csv
      
Analógamente para los archivos CSV de la ciudad de Vancouver.

      Nota: 
      Por cada ejecución del programa ambos archivos .csv correspondientes a las queries se sobreescribirán si existían previamente.
      Si se deseara pasar primero el archivo de los arboles se debe definir TREE_FILE 1 y luego NEIGH_FILE 2.

# Resultado final
Se crearán dos archivos en el directorio donde haya sido ejecutado el programa que corresponden a los queries de la primer fecha de entrega. A saber:

      query1.csv y query2.csv

## Query 1: Total de árboles por habitante. 

Cada línea separa mediante un “;” el nombre del barrio y el total de árboles por habitante 
El orden de impresión es descendente por el total de árboles por habitante y luego alfabético por nombre de barrio. El total de árboles por habitante se imprime truncado a dos decimales.
Sólo se listan los barrios presentes en el archivo CSV de barrios.

## Query 2: Especie de árbol más popular por barrio. 
Cada línea separa mediante un “;” el nombre del barrio y el nombre de la especie del árbol más popular de ese barrio.
Se listan unicamente los barrios presentes en el archivo CSV de barrios.
El orden de impresión es alfabético por nombre de barrio.

      Nota: 
      El programa no procesa árboles de un barrio que no esta en el archivo de barrios.
      El programa no acepta barrios repetidos en el archivo de barrios. En caso de haberlos, se los ignora. 

# Errores
El programa no abortará. El programa informará mediante la salida de errores los posibles problemas que pudieran surgir. Los códigos de error y sus referencias son: 
>1) Error cantidad de argumentos.
>2) Error en el procesamiento de un archivo.
>3) No hay suficiente memoria al utilizar el heap.




