//aca tenemos un main que va  a llamar csv.h, y de ahí lee todo
#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPSILON 0.001

void sortq1(char ** neigh, double * q, size_t dim){
    char * swap;
    int i=0, j=0; 
    double aux,diff;
    int flag = 0; 
    for(i = dim-1; i>0 && !flag; i--){
     flag=1;
     for(j=0;j<i;j++) { 
           if( (diff=q[j]-q[j+1])<0 && fabs(diff)>EPSILON){
                aux = q[j];
                q[j]=q[j+1];
                q[j+1] = aux;  
                swap=neigh[j];
                neigh[j]=neigh[j+1];
                neigh[j+1]=swap;        
                flag = 0;
            }
        }
    }
}
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
    FILE * QUERY1=NULL;
    FILE * QUERY2=NULL;

    size_t q1;
    char **neighs1 = showAllNeigh( myCity , &q1);
    //guardo copia del ordenado alfabeticametne para el query2
    double *query1=treesPerPerson(myCity, &q1);

    if (  neighs1!= NULL && query1!=NULL ){
        sortq1(neighs1, query1, q1);
        for (size_t i = 0; i < q1; i++){
            printf("%s; ", neighs1[i]);
            printf("%g\n", query1[i]);
            free(neighs1[i]);
        }
    }
    else{
        fprintf(QUERY1,"ERROR\n");
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
            printf("%s; ", neighs2[i]);
            printf("%s\n", query2[i]);
            free(neighs2[i]);
            free(query2[i]);
        }
    }
    else{
        fprintf(QUERY2,"Error\n");
        exit(1);
    }
    free(query2);
    free(neighs2);
    
    freeCity(myCity);
    return 0;
}

