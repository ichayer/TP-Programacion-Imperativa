#ifndef __CSV_H_
#define __CSV_H_
#include <stdio.h>

/*
** Funcion que lee lineas y agrega al ADT los nodos correspondientes a cada barrio o arbol segun el dataType.
** Retorna 1 si lo agrego correctamente, -1 en caso de error. 
*/
int read( const char* file, cityADT c, int dataType);//reciba FILE *

FILE* open ( char *file);

//funciones a agregar
int genQ1 ( FILE* csv, char** neighs , double * avg );

int genQ2 ( FILE* csv , char** neighs , char **trees);


#endif 