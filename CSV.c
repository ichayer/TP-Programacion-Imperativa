#include <stdlib.h>
#include <math.h>
#include "cityADT.h"
#include "CSV.h"
#define BUFFER_SIZE 2048
#define BLOCK 20
#define ERROR -1
#define DELIM ";"
#define EPSILON 0.001

static char ** tokenLine(char* delim, char * line){
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

FILE* open( const char *file, char * mode) {
	return fopen( file , mode) ;
}


int read( FILE* file, cityADT c, int dataType){
	if(file==NULL){
		return ERROR;
	}
	char myLine[BUFFER_SIZE]; char ** aux; 
	fgets(myLine, BUFFER_SIZE, file);
	//como primer linea son heads, la primera vex que entro no llamo a addNeigh
	if(dataType){
		readLine(myLine);
 	while(fgets(myLine, BUFFER_SIZE, file)!=NULL){
		aux=tokenLine( DELIM , myLine );
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
	fclose(file);
	return 1;
}
static void sortq1(char ** neigh, double * q, size_t dim){
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
int genQ1 ( FILE* csv, char** neighs , double * avg , size_t dim){
	int err=1;
	if (  neighs!= NULL && avg!=NULL ){
		sortq1(neighs, avg,dim);
        fprintf(csv,"BARRIO;PROMEDIO_ARBOLES_HABITANTES\n"); //Head del archivo 1
        for (size_t i = 0; i < dim; i++){
            fprintf(csv,"%s;", neighs[i]); //Agregamos barrios ya ordenados
            fprintf(csv,"%g\n", avg[i]); //Agregamos el promedio 
            free(neighs[i]); 
        }
    }
    else{
        fprintf(csv,"ERROR\n"); //En caso de que neighs y query1 sean NULL, indicaria que o no pudo generar espacio o no hay barrios,
								//entonces en el archivo solamente indicaria ERROR.
        err = 0;
    }
    fclose(csv); //Cerramos el archivo y luego liberamos los recursos utilizados
    free(avg);
    free(neighs);

	return err;
}
	
int genQ2 ( FILE* csv , char** neighs , char **trees , size_t dim){
	int err=1;
	if (  neighs!= NULL && trees!=NULL ){
        fprintf(csv,"BARRIO;NOMBRE_CIENTIFICO\n"); //Head del archivo 2
        for (size_t i = 0; i < dim ; i++){
            fprintf(csv,"%s;", neighs[i]);
            fprintf(csv,"%s\n", trees[i]);
            free(trees[i]);
        }
    }
    else{
        fprintf(csv,"ERROR\n"); //En caso de que neighs y query2 sean NULL, indicaria que o no pudo generar espacio o no hay barrios, entonces en el archivo solamente indicaria ERROR.
        err = 0;
    }
    fclose(csv); //Cerramos el archivo y luego liberamos los recursos utilizados
	free(trees);

	return err;
}

