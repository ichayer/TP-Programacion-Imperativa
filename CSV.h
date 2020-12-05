#ifndef __CSV_H_
#define __CSV_H_
#include <stdio.h>

#define BUFFER_SIZE 1024

#define DELIM ";"

//Columnas donde se encuentra cada informacion necesaria
#ifdef VAN
#define NEIGH_FILE 1 
#define TREE_FILE 2
#define NEIGH_NAME 1
#define NEIGH_POP 2
#define SPNAME 7
#define NEIGH_TREE 13
#endif 

#ifdef BUE
#define NEIGH_FILE 1 
#define TREE_FILE 2
#define NEIGH_NAME 1
#define NEIGH_POP 2
#define SPNAME 8
#define NEIGH_TREE 3
#endif

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
void genQ1 ( FILE* csv, char** neighs , double * avg , size_t dim);
/* 
** Llena el archivo de query2.csv con los datos pedidos
*/
void genQ2 ( FILE* csv , char** neighs , char **trees , size_t dim);

#endif 
