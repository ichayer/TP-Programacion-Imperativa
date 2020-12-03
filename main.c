//aca tenemos un main que va  a llamar csv.h, y de ahí lee todo
#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#include <stdlib.h>
#define CITY 1
#define TREE 0

int main(int argc, const char *argv[]){

    if(argc!=3){
        fprintf(stderr,"Numero de argumentos invalidos\n"); /* esto nose si esta bien, hay que separar front de back */
        return 1;
    }
    cityADT myCity = newCity();
    int error=read( argv[1],myCity, CITY);

   
    if ( error==-1 ){
        fprintf(stderr,"Error en el archivo referente a los barrios\n");
        return 1;
    }
    error=read( argv[2] , myCity, TREE);

    if ( error==-1 ){
        fprintf(stderr, "Error al abrir el archivo referente a los arboles\n");
        return 1;
    }
    char err = 0;
    FILE * QUERY1= fopen("query1.csv","w"); //creacion del archivo con el total de arboles por habitantes por barrio
    FILE * QUERY2= fopen("query2.csv","w"); //creacion del archivo con la especie de árbol más popular por barrio

    size_t q1;
    char **neighs = showAllNeigh( myCity , &q1); //Creamos
    size_t q2;
    char **query2 = mostPopularTree( myCity , &q2);

    if (  neighs!= NULL && query2!=NULL ){
        fprintf(QUERY2,"BARRIO;NOMBRE_CIENTIFICO\n"); //Head del archivo 2
        for (size_t i = 0; i < q2 ; i++){
            fprintf(QUERY2,"%s;", neighs[i]);
            fprintf(QUERY2,"%s\n", query2[i]);
            free(query2[i]);
        }
    }
    else{
        fprintf(QUERY2,"ERROR\n"); //En caso de que neighs y query2 sean NULL, indicaria que o no pudo generar espacio o no hay barrios, entonces en el archivo solamente indicaria ERROR.
        err = 1;
    }
    fclose(QUERY2); //Cerramos el archivo y luego liberamos los recursos utilizados
    free(query2);

    double *query1=treesPerPerson(myCity, neighs, &q1);

    if (  neighs!= NULL && query1!=NULL ){
        fprintf(QUERY1,"BARRIO;PROMEDIO_ARBOLES_HABITANTES\n"); //Head del archivo 1
        for (size_t i = 0; i < q1; i++){
            fprintf(QUERY1,"%s;", neighs[i]); //Agregamos barrios ya ordenados
            fprintf(QUERY1,"%g\n", query1[i]); //Agregamos el promedio 
            free(neighs[i]); 
        }
    }
    else{
        fprintf(QUERY1,"ERROR\n"); //En caso de que neighs y query1 sean NULL, indicaria que o no pudo generar espacio o no hay barrios, entonces en el archivo solamente indicaria ERROR.
        err = 1;
    }
    fclose(QUERY1); //Cerramos el archivo y luego liberamos los recursos utilizados
    free(query1);
    free(neighs);
    
    freeCity(myCity);
    return err;
}

