#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#include <stdlib.h>

#define CITY 1
#define TREE 0

/*
Error cantidad de argumentos o falta de definicion de constantes: 1
Error de archivo: 2
Error de heap 3
*/

int main(int argc, const char *argv[]){
    #if !define BUE 
        fprintf(stderr, "No define las constantes\n");
        return 1;
    #endif
    #if !define VAN 
        fprintf(stderr, "No define las constantes\n");
        return 1;
    #endif
    if(argc!=3){
        fprintf(stderr,"Numero de argumentos invalidos\n"); 
        return 1;
    }
    cityADT myCity = newCity();
    
    int error=read( open(argv[NEIGH_FILE],"r") ,myCity, CITY);
   
    if ( error==-1 ){
        freeCity(myCity);
        fprintf(stderr,"Error en el archivo referente a los barrios\n");
        return 2;
    }
    error=read( open(argv[TREE_FILE],"r") , myCity, TREE);

    if ( error==-1 ){
        freeCity(myCity);
        fprintf(stderr, "Error al abrir el archivo referente a los arboles\n");
        return 2;
    }
    FILE * QUERY1= open("query1.csv","w"); //creacion del archivo con el total de arboles por habitantes por barrio
    FILE * QUERY2= open("query2.csv","w"); //creacion del archivo con la especie de árbol más popular por barrio
    
    size_t q1,q2;
    char **neighs = showAllNeigh( myCity , &q1); 
    char **query2 = mostPopularTree( myCity , &q2);
    double *query1 = treesPerPerson(myCity, neighs, &q1);

    freeCity(myCity);

    if(neighs==NULL || query2==NULL || query1==NULL){
        fprintf(stderr,"Error en el heap\n");
        return 3;
    }

    if ( genQ2( QUERY2 , neighs , query2 , q2 ) && genQ1(QUERY1 , neighs , query1, q1)){
        return 0;
    }

    fprintf(stderr,"No se pudo generar alguna de las queries\n");
    return 2; 
}