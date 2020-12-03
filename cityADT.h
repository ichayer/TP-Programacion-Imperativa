#ifndef __CITYADT_H
#define __CITYADT_H
#include <strings.h>
#include <stdlib.h>
#include <string.h>

// Valor default de ERROR sera -1 para todo el archivo

typedef struct cityCDT * cityADT;

/* Crea una nueva ciudad */
cityADT newCity(void);

/* Libera los recursos utilizados por el TAD */
void freeCity(cityADT c);

/* Agrega un barrio. 
** devuelve 1 si lo pudo agregar dado que la lista no contiene repetidos,
** 0 si no pues hay repetidos o ERROR
*/
int addNeigh(cityADT c, char * neigh, size_t cantHab);

/*
** Agrega un arbol a un barrio si el barrio es valido. Retorna 1 si pudo agregarlo 0 si no existe el barrio, o ERROR
** Si es un nuevo arbol hace una COPIA del nombre del arbol. Si esta repetido, incrementa la cantidad de ese arbol
** en el barrio dado. 
** Incrementa la cantidad de arboles totales en el barrio.
*/
int addTree(cityADT c, char * neigh, char *tree);

/*
** Devuelve un vector de chars ordenado alfabeticamente,con los nombres cientificos de los arboles mas populares de cada barrio.
** Dim parametro de entrada y salida con la cantidad de barrios.
** Retorna NULL en caso de ERROR y dim en 0 si esta vacio.
*/
char ** mostPopularTree(cityADT c , size_t * dim);

/*
** Devuelve un vector de chars de los barrios en orden alfabético.
** Dim parametro de entrada y salida con la cantidad de barrios.
** Retorna NULL en caso de ERROR y dim en 0 si esta vacio o hubo algo ERROR.
*/
char ** showAllNeigh( cityADT c , size_t *dim );

/* Devuelve la cantidad de arboles por persona en cada barrio, ordenado alfabeticamente.
** Retorna NULL y dim en -1 en caso de ERROR o dim en 0 si esta vacio.
*/
double* treesPerPerson ( cityADT c, char **neighs , size_t *dim);

#endif