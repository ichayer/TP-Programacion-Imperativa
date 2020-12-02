#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ciudadADT.h"

//cambios de nombre mas adelante para que quede mas mejor, no relevante en este momento

//chequear campos comentados si realmente los necesito o no 
//ver si hay que hacer mas funciones

//fprintf puede copiar doubles directamente
//double es cantHab/cantTotal de arboles (redondeado a 2 decimales)
//hacer funcion aux? 

//orden de operaciones de CSV

//agrego todos los barrios primero
//agrego todos los arboles
//si hay arboles que estan en barrios no listados, NO se agregan

//despues, llamar a acada funcion segun query
//cuando tenemos eso lo pasamos a un nuevo FILE * para devolver

typedef struct arbol{
	//char *nombre;
    //double min ;
	//double max ;
    //char *nombreCalle;
	char *nombrecientifico;
	size_t cant ;
	struct arbol * tail ;  
}arbol;

typedef arbol * TListArbol;

typedef struct Tbarrio{
	TListArbol firstTree;
	size_t habitantes;
	size_t totalArboles;
    char * name;
    struct Tbarrio *tail;		
}Tbarrio; 

typedef Tbarrio * TBarrios;

typedef struct ciudadCDT{
	TBarrios firstBarrio;
	size_t cant;
}ciudadCDT;

ciudadADT newCity(void){
  return calloc(1,sizeof(ciudadCDT));
}

/* FIJARSE SI EN LOS CHAR * HACEMOS COPIA O NO :) */
static void freeTreeRec(TListArbol list){
    if(list==NULL)
        return;

    freeTreeRec(list->tail);
    free(list);
}

static void freeRecNeigh(TBarrios list){
    if(list==NULL)
        return;
    
    freeTreeRec(list->firstTree);
    freeRecNeigh(list->tail);
    free(list);
}

void freeCity(ciudadADT c){
    freeRecNeigh(c->firstBarrio);
    free(c);
}

/* ******************************************************************************* */
static TBarrios addNeighRec(TBarrios list, char *neigh, size_t cantHab ,char *flag){
    int c;
    if( list==NULL || (c=compare(list->name,neigh))>0 )
    {
        TBarrios aux=calloc(1,sizeof(Tbarrio));
        aux->tail=list;
        aux->habitantes=cantHab;
        aux->name=neigh; /* ojo */
        *flag=1;
        return aux;
    } 

    if(c==0)
        return list;  

    list->tail=addNeighRec(list->tail, neigh, cantHab,  flag);
    return list;
}

int addNeigh(ciudadADT c, char * neigh, size_t cantHab)
{
    char flag=0;
    c->firstBarrio=addNeighRec(c->firstBarrio, neigh, cantHab, &flag);
    c->cant+=flag;
    return flag;
}

static TBarrios searchNeigh(TBarrios list, char *neigh)
{
    int c;
    if(list==NULL || (c=strcmp(list->name,neigh))>0 )
        return NULL;
    if(c==0)
        return list;
    return searchNeigh(list->tail, neigh);
}

static TListArbol addTreeRec(TListArbol list, char *tree)
{
    int c;
    if( list==NULL || (c=strcmp(list->nombrecientifico,tree))>0 )
    {
        TListArbol aux=malloc(sizeof(arbol));
        aux->tail=list;
        aux->cant=1;
        aux->nombrecientifico=tree; /* ojo */
        return aux;
    } 

    if(c==0)
    {
        list->cant++;
        return list; 
    }

    list->tail=addTreeRec(list->tail, tree);
    return list;
}

int addTree(ciudadADT c, char * neigh, char *tree)
{
    TBarrios aux=searchNeigh(c->firstBarrio,neigh);
    if(aux==NULL)
        return 0;

    aux->firstTree=addTreeRec(aux->firstTree, tree);
    aux->totalArboles++;
    return 1;
}


static char * findMostPopular ( TListArbol list ){
    TListArbol aux=list;
    size_t max=0;
    char *new=NULL;
    while ( aux!=NULL ){
        if ( aux->cant > max ){
            max=aux->cant ;
            new=realloc(new , ( strlen(aux->nombrecientifico))+1 );
            strcpy( new , aux->nombrecientifico);
        }    
        aux=aux->tail;
    }
    return new;
}

char ** mostPopularTree(ciudadADT c){
    TBarrios aux=c->firstBarrio;
    char **new=malloc(sizeof(char*)*c->cant);

    for(int i=0; i<c->cant ; i++){
        new[i]=findMostPopular( aux->firstTree );
        aux=aux->tail;
    }

    return new;
}

char ** showAllNeigh( ciudadADT c){
    char** new= malloc( c->cant * sizeof(char*));
    TBarrios aux=c->firstBarrio ;
    for (size_t i = 0; i < c->cant; i++){
        new[i]=malloc( strlen(aux->name )+1 );
        strcpy(new[i], aux->name);
        aux=aux->tail;
    }
    return new;
}

double* treesPerPerson ( ciudadADT c ){
    TBarrios aux=c->firstBarrio ;
    double * new= malloc ( c->cant * sizeof ( double ));
    double numAux;

    for ( size_t i = 0; i < c->cant; i++){
        //arboles por habitante redondeado a 2 decimales
        numAux=((floor((aux->totalArboles/aux->habitantes)*100))/100);
        new[i]=numAux;
        aux=aux->tail;
    }
    //ordenado segun orden alfabetico de barrios, falta ordenar por orden de mayor a menor
    
    return new;
}
