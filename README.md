# Trabajo práctico final de Programación Imperativa primer fecha (09/12/2020).

El proyecto permite procesar la información de los árboles censados en distintas ciudades del mundo.
Su objetivo principal es la creación de ciertas consultas especificas asignadas por la cátedra.
En el siguiente archivo, se detallará cómo generar los ejecutables y de cómo ejecutarlos. 
# MAKEFILE
Para el MAKEFILE deben indicarse las columnas de interés. 

      -D SPNAME=X -D NEIGH=Y -D NEIGH_NAME=Z -D NEIGH_POP=K

SPNAME es la columna de la especie del árbol y NEIGH la columna de los barrios en los archivos arbolesXXX.csv. 
NEIGH_NAME es la columna de los barrios y NEIGH_POP es la columna de los habitantes en los archivos barriosXXX.csv

      make all 
      make clean 
      
El comando "make all" se encarga de generar los dos ejecutables pedidos para este trabajo practico mientras que "make clean" eliminará todos los archivos generados por el makefile.

Para el trabajo práctico analizaremos la ciudad de Vancouver y de Buenos Aires. Si se quisiera generar un ejecutable de una ciudad en particular ejecutar alguno de los siguientes comandos:

      make arbolesADTBUE 
      make arbolesADTVEN 
# Ejecución
Si se desea procesar los archivos CSV de Buenos Aires y se llaman arboles.csv y barrios.csv y están en el mismo directorio que el ejecutable arbolesADTBUE, el programa se debe invocar como: 

      $> ./arbolesADTBUE barrios.csv arboles.csv
 
Si ambos archivos CSV se llaman arb.csv y bar.csv y están en el directorio superior al ejecutable arbolesADTBUE, se invocará como 
 
      $> ./arbolesADTBUE ../bar.csv ../arb.csv
      
Analógamente para los archivos CSV de la ciudad de Vancouver.

# Resultado final
Se crearan dos archivos en el directorio donde haya sido ejecutado el programa que corresponden a los query's de la primer fecha de entrega:

      query1.csv y query2.csv

#Query 1: Total de árboles por habitante. 

Cada línea separa mediante un “;” el nombre del barrio y el total de árboles por habitante 
El orden de impresión es descendente por el total de árboles por habitante y luego alfabético por nombre de barrio. El total de árboles por habitante se imprime truncado a dos decimales.
Sólo se listan los barrios presentes en el archivo CSV de barrios.

#Query 2: Especie de árbol más popular por barrio. 
Cada línea separada mediante yb “;” el nombre del barrio y el nombre de la especie del árbol más popular de ese barrio.
Se listan unicamente los barrios presentes en el archivo CSV de barrios.
El orden de impresión es alfabético por nombre de barrio.

      Nota: 
      Por cada ejecución del programa ambos archivos .csv se sobreescribirán si existian previamente.
      El programa no contabiliza árboles de un barrio que no esta en el archivo de barrios.
      El programa no acepta barrios repetidos en el archivo de barrios. En caso de haberlos, se los ignora. 

# Errores

Si la cantidad de argumentos es incorrecta o no se pudo abrir algún archivo, se notificará por la salida de errores.
Si no hay memoria suficiente, tanto el query1.csv o query2.csv o ambos contendrán el mensaje de "ERROR".



