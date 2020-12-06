#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cityADT.h"
#include "CSV.h"
#define EPSILON 0.01
#define BLOCK 10
#define ERROR -1

FILE* open( const char *file, char * mode) {
	  return fopen( file , mode ) ;
}
//Funcion para limpiar la linea de ';'. Recibe la linea completa y la devuelve sin ';'
static char **tokenLine( char * line , char* delim){
	  char * token;	char ** new=NULL; size_t i=0;           //Inicializo el vector auxiliar y un contador que va a reprensentar la dimension
	  token= strtok( line , delim );                        //Leo la linea hasta el primer ';' (primer string)
    while ( token!=NULL){                                 
		  if ( i%BLOCK ==0  ){                                //Me fijo si tengo espacio para guardar el nuevo bloque de linea (entre ';')
		  	new=realloc( new , ( i +BLOCK )* sizeof(char*));  //Si no tengo, le doy espacio
			  if(new==NULL)                                     //Si falla al darle espacio, corto
				    return NULL;
		  }
		  new[i++]=token;                                     //Le asigno la linea a mi auxiliar e incremento el iterador
		  token=strtok(NULL, delim );                         //Le paso NULL para que "pase al siguiente token" (pase al siguente bloque sin ';') 
    }
	  new=realloc( new , i * sizeof(char*));		            //Si me sobro espacio, achico el vector a la cantidad real de elementos que guarde
	  return new;                                           //Retorno el vector que guarda cada string de la linea por separado
}

int read( FILE* file, cityADT c, int dataType){
	char myLine[BUFFER_SIZE]; 
	char ** aux; 
	fgets(myLine, BUFFER_SIZE, file); //Leo la primer linea del archivo. Como la primer linea son heads, la primera vez que entro no llamo a funciones
	if(dataType){                     //Me fijo si llame a la funcion para los barrios o para los arboles. 
		while ( fgets(myLine , BUFFER_SIZE, file)!=NULL ){ //Si la llame para los barrios leo la linea
			aux=tokenLine(myLine, DELIM);                    //y se la paso a la funcion tokenLine para que la deje sin ';'
      if (aux==NULL){                                  //Si fallo corto con error.
        return ERROR;
      }
      //ya chequeado con las pruebas del ADT
			if (addNeigh( c , aux[NEIGH_NAME-1], atoi(aux[NEIGH_POP-1]) )==ERROR){  //Si no hubo error agrego el barrio, chequeando que no falle
				free(aux);                                                            //Si fallo, libero los recursos utlizados y corto con error.
				return ERROR;
			}
			free(aux);                                                              //Libero la auxiliar utilizada
		}
	}
	else{                                                           //Si la llame para los arboles, leo la linea  
		while ( fgets(myLine , BUFFER_SIZE, file)!=NULL ){            //y se la paso a la funcion tokenLine para que la deje sin ';'
			aux=tokenLine(myLine, DELIM);   
      if (aux==NULL){                                             //Si fallo corto y salgo con error
        return ERROR;
      }
			if (addTree( c , aux[NEIGH_TREE-1] , aux[SPNAME-1])==ERROR){//Si no hubo problema agrego el arbol chequeando que no falle al agregar
				free(aux);                                                //Si  fallo, libero los recursos y corto con error
				return ERROR;
			}
			free(aux);                                                  //libero aux para seguir leyendo la siguiente linea
		}
	}
	fclose(file);                                                   //Cierro el archivo
	return 1;
}

//Funcion para ordenar los vectores de barrios y promedio de arboles por habitantes decrecientemente y con orden alfabetico
//mejorar	
static void sortq1(char ** neigh, double * q, size_t dim){
  char * swap;                                            
  int i=0, j=0;                                           
  double aux,diff;                                        
  int flag = 0; 
  for(i = dim-1; i>0 && !flag; i--){                      
  flag=1;
    for(j=0; j<i ; j++) {                                 
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
void genQ1 ( FILE* csv, char** neighs , double * avg , size_t dim){
    sortq1(neighs,avg,dim);                                             //Ordenamos los vectores para guardarlos de manera correcta
    fprintf(csv,"BARRIO;PROMEDIO_ARBOLES_HABITANTES\n");                //Head del archivo 1
    for (size_t i = 0; i < dim; i++){
          fprintf(csv,"%s;", neighs[i]);                                //Agregamos barrios ya ordenados
          fprintf(csv,"%g\n", avg[i]);                                  //Agregamos el promedio 
          free(neighs[i]);                                              //Liberamos el nombre de cada barrio
    }
    fclose(csv);                                                        //Cerramos el archivo y luego liberamos los recursos utilizados
    free(avg);                                                          //Liberamos el puntero de los promedios
    free(neighs);                                                       //Liberamos el puntero de los barrios
}
	
void genQ2 ( FILE* csv , char** neighs , char **trees , size_t dim){
  fprintf(csv,"BARRIO;NOMBRE_CIENTIFICO\n");                            //Head del archivo 2
  for (size_t i = 0; i < dim ; i++){        
      fprintf(csv,"%s;", neighs[i]);                                    //LLenamos el archivo con el nombre del barrio
      fprintf(csv,"%s\n", trees[i]);                                    //Llenamos el archivo con el arbol mas popular de dicho barrio
      free(trees[i]);                                                   //Liberamos el puntero con el nombre del arbol mas popular
  }
  fclose(csv);                                                          //Cerramos el archivo y luego liberamos los recursos utilizados
	free(trees);                                                          //Liberamos el puntero de los arboles mas populares creado para llenar el archivo
}

