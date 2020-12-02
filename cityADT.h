#ifndef __CITYADT_H
#define __CITYADT_H
#include <string.h>

// Valor default de ERROR sera -1 para todo el archivo


typedef struct cityCDT * cityADT;

//para comparar barrios, porque en bueADT son nums 
//y en vanADT son nombres
static int compare ( char* neigh1 , char* neigh2){
    return strcmp(neigh1 , neigh2);
}

/* Crea una nueva ciudad */
cityADT newCity(void);

/* Libera los recursos utilizados por el TAD */
void freeCity(cityADT c);

/* devuelve 1 si lo pudo agregar dado que la lista no contiene repetidos
** 0 si no pues hay repetidos o ERROR
*/
int addNeigh(cityADT c, char * neigh, size_t cantHab);

/*
** Agrega un arbol a un barrio si el barrio es valido. Retorna 1 si pudo agregarlo 0 si no, o ERROR
** Si es un nuevo arbol hace una COPIA del nombre del arbol. Si esta repetido, incrementa la cantidad de ese arbol
** en el barrio dado. 
** Incrementa la cantidad de arboles totales en el barrio.
*/
int addTree(cityADT c, char * neigh, char *tree);

/*
** Devuelve un vector de chars con los nombres cientificos de los arboles mas populares de cada barrio
** dim parametro de entrada y salida con la cantidad de barrios
** el vector esta ordenado de manera alfabetica por barrio.
** retorna NULL y dim en -1 en caso de ERROR, dim en 0 si esta vacio
*/
char ** mostPopularTree(cityADT c , int * dim);

/*
**devuelve barrios en orden alfabético
** dim parametro de entrada y salida con la cantidad de barrios
** retorna NULL y dim en -1 en caso de ERROR, dim en 0 si esta vacio
*/
char ** showAllNeigh( cityADT c , int *dim );

/*devuelve cant de arboles por persona en cada barrio (alfabeticamente)
** retorna NULL y dim en -1 en caso de ERROR, dim en 0 si esta vacio
*/
double* treesPerPerson ( cityADT c , int *dim);

#endif