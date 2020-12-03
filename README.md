# Trabajo práctico final de Programación Imperativa primer fecha (09/12/2020).

En el siguiente archivo, se detallará cómo generar los ejecutables y de cómo ejecutarlos. 

# MAKEFILE
Para el MAKEFILE deben indicarse las columnas de interés. 

      -D SPNAME=X -D NEIGH=Y
      
Donde SPNAME es la columna de la especie del árbol y NEIGH la columan de los barrios en los archivos csv. 

      make all 
      make clean 
      
make all se encarga de generar los dos ejecutables pedidos para este trabajo practico, make clean de eliminar todos los archivos generados por el makefile.
Para nuestro trabajo practico analizaremos la ciudad de Vancouver y de Buenos Aires. Si se quisiera generar los ejecutables de una ciudad en particular ejecutar el siguiente comando:

      make arbolesADTBUE 
      make arbolesADTVEN
      
# Ejecución
Si se desea procesar los archivos CSV de :flag_ar: y se llaman arboles.csv y barrios.csv y están en el mismo directorio que el ejecutable arbolesADTBUE, el programa se debe invocar como: 

      $> ./arbolesADTBUE barrios.csv arboles.csv
 
Si ambos archivos CSV se llaman arb.csv y bar.csv y están en el directorio superior al ejecutable arbolesADTBUE, se invocará como 
 
      $> ./arbolesADTBUE ../bar.csv ../arb.csv
      
Analogamente para los archivos CSV de :flag_can:

# Resultado final
Se crearan dos archivos en el directorio donde haya sido ejecutado el programa que corresponden a los querys de la primer fecha de entrega:

      query1.csv
      query2.csv
      
Nota: Por cada ejecución del programa ambos archivos .csv se sobreescribirán.
