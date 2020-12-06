#include "cityADT.h"
#include "CSV.h"
#include <stdio.h>
#define CITY 1
#define TREE 0

/* Libera los recursos utilizados por los vectores en caso de algún error 
** Aprovechamos NULL como marca de final para unificar los problemas propios de heap
** con los problemas de archivos
*/
void freeRemaining(char **vec );

int main(int argc, char const *argv[]){
    //Chequeo que la cantidad de archivos (3) ingresada sea valida 
    if(argc!=3){                                                
        fprintf(stderr,"Numero de argumentos invalidos\n"); 
        return 1;
    }
    //Creo una nueva ciudad para manejar los datos     
    cityADT myCity = newCity();                                

    //Si myCity es NULL entonces fallo al asignarle lugar el calloc
    if(myCity == NULL){                                         
        fprintf(stderr, "Error de heap\n");
        return 3;
    }

    //Abro el archivo para leer y cargar los barrios
    FILE* nFile=open(argv[NEIGH_FILE],"r");                    
    if ( nFile==NULL  ){
        freeCity(myCity);
        fprintf(stderr,"Error al abrir archivo de los barrios\n");
        return 2;
    }
    
    //Leo el archivo y al mismo tiempo guardo los datos pedidos
    int error=read( nFile,myCity, CITY);              

    //Si hubo algun error, libero los recursos utilizados, cierro el archivo y corto         
    //cierro el archivo, ya que si salio, no lo hizo la misma funcion read
    if ( error==-1 ){                                           
        freeCity(myCity);
        fclose(nFile);                                         
        fprintf(stderr,"Error al cargar los datos de los barrios (heap)\n");
        return 3;
    }
    
    //Abro el archivo y lo cargo
    //Si hubo algun error cierro el archivo y libero la ciudad creada
    FILE* tFile=open(argv[TREE_FILE],"r");                     
    if ( tFile==NULL  ){                                    
        freeCity(myCity);
        fprintf(stderr,"Error al abrir archivo de los arboles\n");
        return 2;
    }

    //Leo el archivo y guardo los datos pedidos
    //Si hubo algun error libero la ciudad creada 
    //cierro el archivo, ya que si salio, no lo hizo la misma funcion read
    error=read( tFile , myCity, TREE);                          
    if ( error==-1 ){                                           
        freeCity(myCity);   
        fclose(tFile);                                          
        fprintf(stderr,"Error al cargar los datos de los arboles (heap)\n");
        return 3;
    }

    //Ahora vamos a cargar los vectores que nos van a servir para resolver las queries.
    size_t n;
    char** neighs=NULL; 
    char** query2=NULL;  
    double* query1=NULL; 

    //Llenamos los vectores de los barrios, los promedios y los arboles mas populares
    //En caso de error libero la cuidad creada
    if(retrieveData(myCity,&neighs,&query2,&query1,&n)==-1){     
        freeCity(myCity);                                       
        freeRemaining(neighs);
        freeRemaining(query2);
        free(query1);
        fprintf(stderr,"Error en el heap\n");
        return 3;
    }

    //Como ya se han cargado todos los datos necesarios para generar las queries, puede liberarse el TAD
    freeCity(myCity);     

    //Creacion del archivo con la especie de árbol más popular por barrio
    //Si fallo al abrirse libero los recursos ya utilizados por los vectores de barrios, arboles mas populares y promedios
    FILE * QUERY2=open("query2.csv","w"); 
    if ( QUERY2==NULL  ){                                           
        freeRemaining( neighs );                                   
        freeRemaining( query2 );
        free(query1);                                               
        fprintf(stderr,"Error al crear el archivo de query2\n");
        return 2;
    }

    //Llegados a este punto lo necesario para generar Q2 se sabe que es valido
    //Lleno el archivo query2.csv con los datos de los barrios y los arboles mas populares
    genQ2( QUERY2 , neighs , query2 , n);                           

    //Creacion del archivo con el total de arboles por habitantes por barrio
    //Si fallo al abrirse libero los recursos ya utilizados por el vector de barrios
    //No hace falta liberar el vector de arboles mas populares porque genQ2 ya libera.
    FILE * QUERY1=open("query1.csv","w");
    if ( QUERY1==NULL  ){
        freeRemaining( neighs );                                    
        free(query1);                                              
        fprintf(stderr,"Error al crear el archivo de query1\n");
        return 2;
    }

    //Llegados a este punto lo necesario para generar Q1 se sabe que es valido
    //Guardamos en el query1.csv la informacion pedida
    genQ1(QUERY1 , neighs , query1, n); 

    return 0;
}

void freeRemaining(char **vec ){
    size_t i=0;
    while ( vec[i]!=NULL ){
        free(vec[i++]);
    }
    free(vec);
    return;
}
