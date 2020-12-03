//aca tenemos un main que va  a llamar csv.h, y de ahí lee todo
#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    if(argc!=3){
        fprintf(stderr,"Numero de argumentos invalidos\n"); /* esto nose si esta bien, hay que separar front de back */
        return 1;
    }
    cityADT myCity = newCity();

    //despues cambiar
    int error=readCity( argv[1],myCity);

   
    if ( error==-1 ){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    else if ( error==-2){
        printf("Error al cargar los barrios\n");
        exit(1);
    }
    error=readTree( argv[2] , myCity );

    if ( error==-1 ){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    else if ( error==-2){
        printf("Error al cargar los arboles\n");
        exit(1);
    }

    size_t q1;
    char **neighs1 = showAllNeigh( myCity , &q1);
    //guardo copia del ordenado alfabeticametne para el query2
    double *query1=treesPerPerson(myCity, &q1);

    if (  neighs1!= NULL && query1!=NULL ){
        for (size_t i = 0; i < q1; i++){
            printf("%s: ", neighs1[i]);
            printf("%g\n", query1[i]);
            free(neighs1[i]);
        }
    }
    else{
        printf("Error en query1\n");
        exit(1);
    }
    free(query1);
    free(neighs1);

    putchar('\n');
    putchar('\n');
    putchar('\n');

    size_t q2;
    char **query2 = mostPopularTree( myCity , &q2);
    char **neighs2 =showAllNeigh(myCity , &q2 );

    if (  neighs2!= NULL && query2!=NULL ){
        for (size_t i = 0; i < q2 ; i++){
            printf("%s: ", neighs2[i]);
            printf("%s\n", query2[i]);
            free(neighs2[i]);
            free(query2[i]);
        }
    }
    else{
        printf("Error en query2\n");
        exit(1);
    }
    free(query2);
    free(neighs2);
    
    freeCity(myCity);
    return 0;
}

