#ifndef __CIUDADADT_H
#define __CIUDADADT_H

typedef struct ciudadCDT * ciudadADT;

//para comparar barrios, porque en bueADT son nums 
//y en vanADT son nombres
static int compare ( char* neigh1 , char* neigh2){
    return strcmp(neigh1 , neigh2);
}

/* Crea una nueva ciudad */
ciudadADT newCity(void);

/* Libera los recursos utilizados por el TAD */
void freeCity(ciudadADT c);

/* devuelve 1 si lo pudo agregar dado que la lista no contiene repetidos
** 0 si no pues hay repetidos
*/
int addNeigh(ciudadADT c, char * neigh, size_t cantHab);

/*
** Agrega un arbol a un barrio si el barrio es valido. Retorna 1 si pudo agregarlo 0 si no.
** Si es un nuevo arbol hace una COPIA del nombre del arbol. Si esta repetido, incrementa la cantidad de ese arbol
** en el barrio dado. 
** Incrementa la cantidad de arboles totales en el barrio.
** Actualiza los valores de max y min diametro. (a chequear)
*/
int addTree(ciudadADT c, char * neigh, char *tree);

/*
** Devuelve un vector de chars con los nombres cientificos de los arboles mas populares de cada barrio
** el vector esta ordenado de manera alfabetica por barrio.
*/
char ** mostPopularTree(ciudadADT c);


/*
**devuelve barrios en orden alfabético
*/
char ** showAllNeigh( ciudadADT c);

double* treesPerPerson ( ciudadADT c );


#endif