//aca tenemos un main que va  a llamar csv.h, y de ahí lee todo
#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]){

    if(argc!=3){
        fprintf(stderr,"Invalid amount of arguments"); /* esto nose si esta bien, hay que separar front de back */
        return 1;
    }
    cityADT myCity = newCity();

    //despues cambiar
    int error=readCity((FILE*)argv[1],myCity);

    if ( error==-1){
        printf("fatal error\n");
        exit(1);
    }

    long int dim;
    char **neighs = showAllNeigh( myCity , &dim);
    if ( dim!= -1){
        for (size_t i = 0; i < dim; i++){
            printf("%s\n", neighs[i]);
            free(neighs[i]);
        }
        
    }
    free(neighs);
    freeCity(myCity);
    return 0;
}

