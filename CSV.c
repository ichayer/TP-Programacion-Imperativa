#include <stdlib.h>
#include <math.h>
#include "cityADT.h"
#include "CSV.h"
#define EPSILON 0.01
#define BLOCK 20
#define ERROR -1

FILE* open( const char *file, char * mode) {
	  return fopen( file , mode ) ;
}

static char **tokenLine( char * line , char* delim){
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

int read( FILE* file, cityADT c, int dataType){
	char myLine[BUFFER_SIZE]; 
	char ** aux; 
	fgets(myLine, BUFFER_SIZE, file);
	//como primer linea son heads, la primera vez que entro no llamo a funciones
	if(dataType){
		while ( fgets(myLine , BUFFER_SIZE, file)!=NULL ){
			aux=tokenLine(myLine, DELIM);
      if (aux==NULL){
        return ERROR;
      }
			if (addNeigh( c , aux[NEIGH_NAME-1], atoi(aux[NEIGH_POP-1]) )==ERROR){
				free(aux);
				return ERROR;
			}
			free(aux);
		}
	}
	else{
		while ( fgets(myLine , BUFFER_SIZE, file)!=NULL ){
			aux=tokenLine(myLine, DELIM);
      if (aux==NULL){
        return ERROR;
      }
			if (addTree( c , aux[NEIGH_TREE-1] , aux[SPNAME-1])==ERROR){
				free(aux);
				return ERROR;
			}
			free(aux);
		}
	}
	fclose(file);
	return 1;
}

/*void sortq1(double arr[],char *cArr[], int lim_izq, int lim_der){
  int izq=lim_izq;
  int der=lim_der;
  int piv=lim_der;
  double aux;
  
  char *swap;

  while (izq<der){
    while ( (arr[izq]-arr[piv])>0 && izq<lim_der) 
		izq++;
    while( (arr[piv]-arr[der])>0 && der > lim_izq) 
		der--;
       
       if(izq<der){
         aux=arr[izq];
         arr[izq]=arr[der];
         arr[der]=aux;
         swap=cArr[izq];
         cArr[izq]=cArr[der];
         cArr[der]=swap;
         //izq++; der--;
       }
  } 

	aux=arr[piv];
  	arr[piv]=arr[der];
  	arr[der]=aux;
	sortq1(arr,cArr,lim_izq,der);
  	sortq1(arr,cArr,izq,lim_der);
}*/

/*void sortq1(char ** neigh, double * q, size_t dim){
  sortingRec(q,neigh,0,dim-1);
}*/


//mejorar	
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
void genQ1 ( FILE* csv, char** neighs , double * avg , size_t dim){
		//sortq1( avg,neighs,0,dim-1);
    sortq1(neighs,avg,dim);
    fprintf(csv,"BARRIO;PROMEDIO_ARBOLES_HABITANTES\n"); //Head del archivo 1
    for (size_t i = 0; i < dim; i++){
          fprintf(csv,"%s;", neighs[i]); //Agregamos barrios ya ordenados
          fprintf(csv,"%g\n", avg[i]); //Agregamos el promedio 
          free(neighs[i]); 
    }
    
    fclose(csv); //Cerramos el archivo y luego liberamos los recursos utilizados
    free(avg);
    free(neighs);
}
	
void genQ2 ( FILE* csv , char** neighs , char **trees , size_t dim){
  fprintf(csv,"BARRIO;NOMBRE_CIENTIFICO\n"); //Head del archivo 2
  for (size_t i = 0; i < dim ; i++){
      fprintf(csv,"%s\n", trees[i]);
      fprintf(csv,"%s;", neighs[i]);
      free(trees[i]);
  }
  fclose(csv); //Cerramos el archivo y luego liberamos los recursos utilizados
	free(trees);

}

