#ifndef __CSV_H_
#define __CSV_H_
#include <stdio.h>

/*
** Funcion que lee lineas y se encarga de agregar
** al ADT los nodos correspondientes a cada barrio
** con su cantidad total de habitantes
** retorna 1 si lo agrego correctamente
** retorna -1 en caso de error.
*/
int readCity(FILE * file, cityADT myCity);

#endif 