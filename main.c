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
        fprintf(stderr,"Error al abrir el archivo\n");
        exit(1);
    }
    else if ( error==-2){
        fprintf(stderr, "Error al cargar los barrios\n");
        exit(1);
    }
    error=readTree( argv[2] , myCity );

    if ( error==-1 ){
        fprintf(stderr, "Error al abrir el archivo\n");
        exit(1);
    }
    else if ( error==-2){
        fprintf(stderr,"Error al cargar los arboles\n");
        exit(1);
    }
    char err = 0;
    FILE * QUERY1= fopen("query1.csv","w");
    FILE * QUERY2= fopen("query2.csv","w");

    size_t q1;
    char **neighs1 = showAllNeigh( myCity , &q1);
    //guardo copia del ordenado alfabeticametne para el query2
    double *query1=treesPerPerson(myCity, &q1);
    if (  neighs1!= NULL && query1!=NULL ){
        sortq1(neighs1, query1, q1);
        fprintf(QUERY1,"BARRIO;PROMEDIO_ARBOLES_HABITANTES\n");
        for (size_t i = 0; i < q1; i++){
            fprintf(QUERY1,"%s;", neighs1[i]);
            fprintf(QUERY1,"%g\n", query1[i]);
            free(neighs1[i]);
        }
    }
    else{
        fprintf(QUERY1,"ERROR\n");
        err = 1;
    }
    fclose(QUERY1);
    free(query1);
    free(neighs1);

    putchar('\n');
    putchar('\n');
    putchar('\n');

    size_t q2;
    char **query2 = mostPopularTree( myCity , &q2);
    char **neighs2 =showAllNeigh(myCity , &q2 );

    if (  neighs2!= NULL && query2!=NULL ){
        fprintf(QUERY2,"BARRIO;NOMBRE_CIENTIFICO\n");
        for (size_t i = 0; i < q2 ; i++){
            fprintf(QUERY2,"%s;", neighs2[i]);
            fprintf(QUERY2,"%s\n", query2[i]);
            free(neighs2[i]);
            free(query2[i]);
        }
    }
    else{
        fprintf(QUERY2,"Error\n");
        err = 1;
    }
    fclose(QUERY2);
    free(query2);
    free(neighs2);
    
    freeCity(myCity);
    return err;
}

