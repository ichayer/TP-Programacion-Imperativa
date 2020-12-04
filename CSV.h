 #ifndef __CSV_H_
#define __CSV_H_
#include <stdio.h>

/*genera un FILE* en el modo deseado*/
FILE* open( const char *file , char * mode);

/*
** Funcion que lee lineas y agrega al ADT los nodos correspondientes a cada barrio o arbol segun el dataType.
** Retorna 1 si lo agrego correctamente, -1 en caso de error. 
*/
int read( FILE* file, cityADT c, int dataType);
/* 
** Llena el archivo de query1.csv con los datos pedidos 
*/
int genQ1 ( FILE* csv, char** neighs , double * avg , size_t dim);
/* 
** Llena el archivo de query2.csv con los datos pedidos
*/
int genQ2 ( FILE* csv , char** neighs , char **trees , size_t dim);

#endif 