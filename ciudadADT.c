#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "ciudadADT.h"

typedef struct arbol
{
	//char *nombre;
    //double min ;
	//double max ;
    //char *nombreCalle;
	char *nombrecientifico;
	size_t cant ;
	struct arbol * tail ;  
}arbol;

typedef arbol * TListArbol;

typedef struct Tbarrio 
{
	TListArbol firstTree;
	size_t habitantes;
	size_t totalArboles;
    char * name;
    struct Tbarrio *tail;		
}Tbarrio; 

typedef Tbarrio * TBarrios;

typedef struct ciudadCDT 
{
	TBarrios firstBarrio;
	size_t cant;
}ciudadCDT;

ciudadADT newCity(void)
{
  return calloc(1,sizeof(ciudadCDT));
}

/* FIJARSE SI EN LOS CHAR * HACEMOS COPIA O NO :) */
static void freeTreeRec(TListArbol list)
{
    if(list==NULL)
        return;

    freeTreeRec(list->tail);
    free(list);
}

static void freeRecNeigh(TBarrios list)
{
    if(list==NULL)
        return;
    
    freeTreeRec(list->firstTree);
    freeRecNeigh(list->tail);
    free(list);
}

void freeCity(ciudadADT c)
{
    freeRecNeigh(c->firstBarrio);
    free(c);
}

/* ******************************************************************************* */
static TBarrios addNeighRec(TBarrios list, char *neigh, size_t cantHab ,char *flag)
{
  int c;
  if( list==NULL || (c=strcmp(list->name,neigh))>0 )
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

  list->tail=addNeighRec(list->tail, neigh, flag);
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
  if( list==NULL || (c=strcmp(list->name,neigh))>0 )
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

char ** mostPopularTree(ciudadADT c)
{
    TBarrios aux=c->firstBarrio;
    char **new=malloc(sizeof(char*)*c->cant);

    for(int i=0; i<c->cant ; i++)
    {
        new[i]=malloc(sizeof());

    }
    return new;
}
