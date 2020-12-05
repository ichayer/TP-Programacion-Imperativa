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
    #if !defined VAN && !defined BUE
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

    //si alguno de los datos recolectados para resolver las queries, se liberan los recursos de las demas
    //se alterna la llamada con el caso de error para simplificar como se liberan los mismos

    // char **neighs = showAllNeigh( myCity , &n); 
    // if ( neighs==NULL ){
    //     fprintf(stderr,"Error en el heap\n");
    //     return 3;
    // }

    // char **query2 = mostPopularTree( myCity , &q2);
    // if ( query2==NULL ){
    //     free(neighs);//y de cada palabra    
    //     fprintf(stderr,"Error en el heap\n");
    //     return 3;
    // }
    //chequear que tal vez q2 y n son !=?
    char** neighs = NULL;
    char** query2=NULL;
    double*query1=NULL;
    if(retrieveData(myCity,neighs,query2,query1,&n)==-1){
        fprintf(stderr,"Error en el heap\n");
    }
    FILE * QUERY2= open("query2.csv","w"); //creacion del archivo con la especie de árbol más popular por barrio
    if ( QUERY2==NULL  ){
        fprintf(stderr,"Error al crear el archivo de query2\n");
        free(neighs);//y de cada palabra 
        free(query2);//y de cada palabra
        return 2;
    }
    genQ2( QUERY2 , neighs , query2 , n) ;
    //llegado a este punto todos los datos usados por genQ2 funcionan, no hacen falta más chequeos?

    // double *query1 = treesPerPerson(myCity, neighs, &q1);
    // if ( query1==NULL ){
    //     free(neighs);//y de cada palabra 
    //     free(query2);//y de cada palabra
    //     fprintf(stderr,"Error en el heap\n");
    //     return 3;
    // }
    //chequear que tal vez q1 y n son !=?

    FILE * QUERY1= open("query1.csv","w"); //creacion del archivo con el total de arboles por habitantes por barrio
    if ( QUERY1==NULL  ){
        fprintf(stderr,"Error al crear el archivo de query1\n");
        free(neighs);//y de cada palabra;
        free(query1);
        return 2;
    }

    genQ1(QUERY1 , neighs , query1, n);
    //llegado a este punto todos los datos usados por genQ1 funcionan, no hacen falta más chequeos?

    freeCity(myCity);     

    return 0;
}
