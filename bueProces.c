//aca tenemos un main que va  a llamar csv.h, y de ahí lee todo
#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>


int main(int argc, const char *argv[]){
    //leer todo con csv.h

    //vamos a pasarselo al back con cityadt para las queries

    //lo que vaya devolviendo el back lo escribimos con csv

    //liberamos todo 


    if(argc>3){
        fprintf(stderr,"Invalid amount of arguments"); /* esto nose si esta bien, hay que separar front de back */
        return 1;
    }
    cityADT myCity = newCity();
    readCity(argv[2],myCity);
    return 0;
}

