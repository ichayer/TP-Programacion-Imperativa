#ifndef __CSV_H_
#define __CSV_H_
#include <stdio.h>

/*
** Funcion que lee lineas y se encarga de agregar
** al ADT los nodos correspondientes a cada barrio
** con su cantidad total de habitantes
** retorna 1 si lo agrego correctamente
** retorna -1 en caso de error al abrir el archivo
** retorna -2 en caso de error al intentar agregar el barrio
*/
int readCity( const char* file, cityADT c);

/*
** Funcion que lee lineas y se encarga de agregar
** al ADT los campos necesarios asociados a cada arbol
** retorna 1 si lo agrego correctamente
** retorna -1 en caso de error.
** retorna -2 en caso de error al intentar agregar el arbol
*/
int readTree( const char *file, cityADT c);


#endif 