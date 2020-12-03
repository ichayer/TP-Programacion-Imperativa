#include <stdlib.h>
#include "cityADT.h"
#include "CSV.h"
#define BUFFER_SIZE 2048
#define BLOCK 20
#define ERROR -1
#define DELIM ";"

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

int read( const char* file, cityADT c, int dataType){
 	FILE* myFile= fopen( file, "r");
	if(myFile==NULL){
		return ERROR;
	}

	char myLine[BUFFER_SIZE]; char ** aux; 
	fgets(myLine, BUFFER_SIZE, myFile);
	//como primer linea son heads, la primera vex que entro no llamo a addNeigh
 	while(fgets(myLine, BUFFER_SIZE, myFile)!=NULL){
		aux=readLine( DELIM , myLine );
		if(dataType){
			if ( aux[1][0]!='\0'){
				if (addNeigh( c , aux[NEIGH_NAME-1], atoi(aux[NEIGH_POP-1]) )==-1){
					free(aux);
					return ERROR;
				}
			}
		}
		else{
			if (addTree( c , aux[NEIGH_TREE-1] , aux[SPNAME-1])==-1){
				free(aux);
				return ERROR;
			}
 		}
		 free(aux);
	 }
	 fclose(myFile);
	return 1;
}
	
	


