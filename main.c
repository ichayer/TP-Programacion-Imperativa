//aca tenemos un main que va  a llamar csv.h, y de ahí lee todo
#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#include <stdlib.h>
#define CITY 1
#define TREE 0

int main(int argc, const char *argv[]){

    if(argc!=3){
        fprintf(stderr,"Numero de argumentos invalidos\n"); 
        return 1;
    }
    cityADT myCity = newCity();
    
    int error=read( openToRead(argv[1]) ,myCity, CITY);
   
    if ( error==-1 ){
        fprintf(stderr,"Error en el archivo referente a los barrios\n");
        return 1;
    }
    error=read( openToRead(argv[2]) , myCity, TREE);

    if ( error==-1 ){
        fprintf(stderr, "Error al abrir el archivo referente a los arboles\n");
        return 1;
    }
    FILE * QUERY1= openToWrite("query1.csv"); //creacion del archivo con el total de arboles por habitantes por barrio
    FILE * QUERY2= openToWrite("query2.csv"); //creacion del archivo con la especie de árbol más popular por barrio
    
    size_t q1,q2;
    char **neighs = showAllNeigh( myCity , &q1); 
    char **query2 = mostPopularTree( myCity , &q2);
    double *query1=treesPerPerson(myCity, neighs, &q1);
    freeCity(myCity);

    if ( genQ2( QUERY2 , neighs , query2 , q2 ) && genQ1(QUERY1 , neighs , query1, q1)){
        return 0;
    }  
    
    return 1;
}