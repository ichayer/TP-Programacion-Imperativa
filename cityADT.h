#ifndef __CITYADT_H
#define __CITYADT_H
#include <stdlib.h>

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

/* Funcion que lee toda la informacion necesaria para resolver los queries en un ciclo
** Todos los vectores se guardan según orden alfabético de los barrios
** En los punteros de char** pone NULL como marca de final.
** Devuelve -1 en caso de ERROR y 1 si no hubo problemas al crear la memoria para los vectores
*/
int retrieveData(cityADT c , char ***neighName , char *** mostPop, double ** avg, size_t *dim);

#endif
