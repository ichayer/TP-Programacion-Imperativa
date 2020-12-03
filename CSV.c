#include <stdlib.h>
#include "cityADT.h"
#include "CSV.h"
#define BUFFER_SIZE 2048
#define BLOCK 20

//por ahora seguimos así, despues si hace falta modificamos
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

	return new;
}

int readCity( const char* file, cityADT c){
 	FILE* myFile= fopen( file, "r");
	if(myFile==NULL){
		return -1;
	}

	char myLine[BUFFER_SIZE]; char ** aux; 
	fgets(myLine, BUFFER_SIZE, myFile);
	//como primer linea son heads, la primera vex que entro no llamo a addNeigh

 	while(fgets(myLine, BUFFER_SIZE, myFile)!=NULL) {
		aux=readLine( ";" , myLine );
		if ( aux[1][0]!='\0'){
			if (addNeigh( c , aux[0], atoi(aux[1]) )==-1){
				return -2;
			}
		}
		free(aux);
 	}
 	fclose(myFile);
	return 1;
}

int readTree( const char *file, cityADT c){
	FILE* myFile= fopen( file, "r");
	if(myFile==NULL){
		return -1;
	}
	char myLine[BUFFER_SIZE]; char ** aux; 
	fgets(myLine, BUFFER_SIZE, myFile);
 	while(fgets(myLine, BUFFER_SIZE, myFile)!=NULL) {
		aux=readLine( ";" , myLine );

		//cambiar los numeros por las constantes del makefile
		if (addTree( c , aux[12] , aux[4])==-1){
			return -2;
		}
	
		free(aux);
 	}
 	fclose(myFile);
	return 1;
}
