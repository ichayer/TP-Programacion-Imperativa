#include <stdlib.h>
#include "cityADT.h"
#include "CSV.h"
#define BUFFER_SIZE 1024
#define BLOCK 20

static char ** readLine(char* delim, char * line){
	char * token;	char ** new=NULL; size_t i=0;
	token= strtok( line , delim );
    while ( token!=NULL){
		if ( i%BLOCK ==0  ){
			new=realloc( new , ( i +BLOCK )* sizeof(char*));
			if(new==NULL)
				return NULL;
		}
		new[i++]=token;
		token=strtok(NULL, delim );
    }
	new=realloc( new , i * sizeof(char*));

	if(new==NULL)
	  return NULL;		

	return new;
}

int readCity(FILE * file, cityADT c){
 	FILE* myFile= fopen( (char*) file, "r");

	if(myFile==NULL){
    	printf("No abrio correctamente");
		return -1;
	}

	char myLine[BUFFER_SIZE]; char ** aux; char firstLine=1;

 	while(fgets(myLine, BUFFER_SIZE, myFile)!=NULL) {
		aux=readLine( ";" , myLine );
		if ( !firstLine ){
			if ( aux[1][0]!='\0'){
				if (addNeigh( c , aux[0], atoi(aux[1]) )==-1){
					return -1;
				}
			}
		}else{
			//como primer linea son heads, la primera vex que entro no llamo a addNeigh
			//apago el flag de que era la primera para poder empezar a agregaar
			firstLine=0;
		}
		free(aux);
 	}
 	fclose(myFile);
	return 1;
}

