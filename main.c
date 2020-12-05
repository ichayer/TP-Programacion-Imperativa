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

/* Libera los recursos utilizados por los vectores */
void freeRemaining(char **vec,size_t dim);

int main(int argc, const char *argv[]){
    #if !defined VAN && !defined BUE      //como se compilan ambos archivos a la vez, si las dos constantes faltaran deberíamos abortar
        fprintf(stderr, "No define las constantes\n");
        return 1;
    #endif
    
    if(argc!=3){
        fprintf(stderr,"Numero de argumentos invalidos\n"); 
        return 1;
    }
    
    cityADT myCity = newCity();
    FILE* nFile=open(argv[NEIGH_FILE],"r");

    if ( nFile==NULL  ){
        fprintf(stderr,"Error al abrir archivo de los barrios\n");
        freeCity(myCity);
        return 2;
    }
    FILE* tFile=open(argv[TREE_FILE],"r");

    if ( tFile==NULL  ){
        fprintf(stderr,"Error al abrir archivo de los arboles\n");
        fclose(nFile);
        freeCity(myCity);
        return 2;
    }
    int error=read( nFile,myCity, CITY);
   
    if ( error==-1 ){
        freeCity(myCity);
        fclose(tFile);
        fclose(nFile);
        fprintf(stderr,"Error en el archivo referente a los barrios\n");
        return 2;
    }
    error=read( tFile , myCity, TREE);

    if ( error==-1 ){
        freeCity(myCity);
        fclose(tFile);
        fprintf(stderr, "Error en el archivo referente a los barrios\n");
        return 2;
    }
    size_t n;

    //Ahora vamos a cargar los vectores que nos van a servir para resolver las querys.
    char** neighs=NULL; char** query2=NULL;  double* query1=NULL; 
    if(retrieveData(myCity,&neighs,&query2,&query1,&n)==-1){
        fprintf(stderr,"Error en el heap\n");
        return 3;
    }

    //creacion del archivo con la especie de árbol más popular por barrio
    FILE * QUERY2= open("query2.csv","w"); 
    if ( QUERY2==NULL  ){
        fprintf(stderr,"Error al crear el archivo de query2\n");
        freeRemaining(neighs , n);
        freeRemaining(query2 , n);
        return 2;
    }
    genQ2( QUERY2 , neighs , query2 , n);

    if ( query1==NULL ){
        freeRemaining(neighs , n);
        freeRemaining(query2 , n);
        fprintf(stderr,"Error en el heap\n");
        return 3;
    }

    //creacion del archivo con el total de arboles por habitantes por barrio
    FILE * QUERY1= open("query1.csv","w");
    if ( QUERY1==NULL  ){
        fprintf(stderr,"Error al crear el archivo de query1\n");
        freeRemaining(neighs , n);
        free(query1);
        return 2;
    }
    genQ1(QUERY1 , neighs , query1, n);
    freeCity(myCity);     
    return 0;
}

void freeRemaining(char **vec,size_t dim){
    for (size_t i = 0; i < dim; i++)
        free(vec[i]);
    free(vec);
    return;
}