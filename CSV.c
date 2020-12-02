#include <stdio.h>
#include "cityADT.h"
#include "CSV.h"
#define BUFFER_SIZE 1024
#define BLOCK 20

void readCity(FILE * file, cityADT myCity){
	FILE * myFile;
 	myFile= fopen(file, "r");

	if(myFile==NULL){
    	printf("No abrio correctamente");
		return NULL;
	}

char myLine[BUFFER_SIZE]; 
char * token;
char ** aux;


 while(fgets(myLine, BUFFER_SIZE, myFile)!=NULL) {
    
 }
 fclose(myFile);
}
static char ** readLine(char * rta, char * line){


	 token= strtok( myLine , ";" );
	 aux = malloc(sizeof(char*));
     while ( (aux=strtok(NULL, ";" ))!=NULL){
        printf("%s\n" ,aux);
     }
}
