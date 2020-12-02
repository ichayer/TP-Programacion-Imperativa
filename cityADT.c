#include <math.h>
#include <stdio.h>
#include "cityADT.h"
#define ERROR -1 

typedef struct tree{
	char *treeName;     //nombre cientifico arbol
	size_t count ;      //cant de esa especie
	struct tree * tail ;//puntero a siguiente
}tree;

typedef tree * TListTree;

typedef struct TNeigh{
	TListTree firstTree;//puntero a primero de la lista de arboles
	size_t people;      //habitantes del barrio
	size_t trees;       //cant total de arboles
    char *neighName;    //nombre de barrio
    struct TNeigh *tail;	//puntero a siguiente	
}TNeigh; 

typedef TNeigh * TListNeigh;

typedef struct cityCDT{
	TListNeigh firstNeigh;//puntero a primer barrio
	size_t count;         //cant de barrios
}cityCDT;

cityADT newCity(void){
  return calloc(1,sizeof(cityCDT));
}

/* FIJARSE SI EN LOS CHAR * HACEMOS COPIA O NO :) */
static void freeTreeRec(TListTree list){
    if(list==NULL)
        return;

    freeTreeRec(list->tail);
    free(list);
}

static void freeRecNeigh(TListNeigh list){
    if(list==NULL)
        return;
    
    freeTreeRec(list->firstTree);
    freeRecNeigh(list->tail);
    free(list);
}

void freeCity(cityADT c){
    freeRecNeigh(c->firstNeigh);
    free(c);
}

static TListNeigh addNeighRec(TListNeigh list, char *neigh, size_t cantHab ,char *flag){
    int c;
    if( list==NULL || (c=compare(list->neighName,neigh))>0 ){
        if ( list!=NULL ){
            printf("%d\n", c);
        }
        TListNeigh aux=malloc(sizeof(TNeigh));
        aux->firstTree=NULL;
        aux->tail=list;
        aux->trees=0;
        aux->people=cantHab;
        aux->neighName=neigh; /* ojo */
        (*flag)=1;
        return aux;
    } 

    if(c==0)
        return list;  

    list->tail=addNeighRec(list->tail, neigh, cantHab,  flag);
    return list;
}
int addNeigh(cityADT c, char * neigh, size_t cantHab){
    char flag=0;

    c->firstNeigh=addNeighRec(c->firstNeigh, neigh, cantHab, &flag);
    if(flag!=-1)
        c->count+=flag;

    printf("%ld\n", c->count);

    return flag;
}

static TListNeigh searchNeigh(TListNeigh list, char *neigh){
    int c;
    if(list==NULL || (c=compare(list->neighName,neigh))>0 )
        return NULL;
    if(c==0)
        return list;
    return searchNeigh(list->tail, neigh);
}

static TListTree addTreeRec(TListTree list, char *tree , int *flag){
    int c;
    if( list==NULL || (c=strcmp(list->treeName,tree))>0 ){
        TListTree aux=malloc(sizeof(tree));
        if ( aux==NULL ){
            *flag=ERROR;
            return NULL;
        }

        aux->tail=list;
        aux->count=1;
        aux->treeName=tree; 
        return aux;
    } 

    if(c==0){
        list->count++;
        return list; 
    }

    list->tail=addTreeRec(list->tail, tree, flag);
    return list;
}
int addTree(cityADT c, char * neigh, char *tree){
    int flag=0;
    TListNeigh aux=searchNeigh(c->firstNeigh,neigh);
    if(aux==NULL)
        return flag;

    aux->firstTree=addTreeRec(aux->firstTree, tree , &flag );
    aux->trees++;
    return flag;
}


static char * findMostPopular ( TListTree list ){
    TListTree aux=list;
    size_t max=0;
    char *new=NULL;
    while ( aux!=NULL ){
        if ( aux->count > max ){
            max=aux->count ;
            new=realloc(new , ( strlen(aux->treeName))+1 );
            if ( new== NULL ){
                return NULL;
            }
            strcpy( new , aux->treeName);
        }    
        aux=aux->tail;
    }
    return new;
}
char ** mostPopularTree(cityADT c , long int *dim ){
    if ( c->count ==0 ){
        *dim=0;
        return NULL;
    }
    TListNeigh aux=c->firstNeigh;
    char **new=malloc(sizeof(char*)*c->count);
    if ( new== NULL ){
        *dim=ERROR; 
        return NULL;
    }
    for(int i=0; i<c->count ; i++){
        new[i]=findMostPopular( aux->firstTree );
        if ( new[i]== NULL ){
            *dim=ERROR; 
            return NULL;
        }
        aux=aux->tail;
    }
    return new;
}

char ** showAllNeigh( cityADT c , long int *dim ){
    if ( c->count ==0 ){
        *dim=0;
        return NULL;
    }

    char** new= malloc( c->count * sizeof(char*));
    if ( new== NULL ){
        *dim=ERROR; 
        return NULL;
    }
    TListNeigh aux=c->firstNeigh ;
    for (size_t i = 0; i < c->count; i++){
        new[i]=malloc( strlen(aux->neighName )+1 );
        if ( new[i]==NULL ){
            *dim=ERROR;
            return NULL;
        }
        strcpy(new[i], aux->neighName);
        aux=aux->tail;
    }
    *dim=c->count;
    return new;
}

double* treesPerPerson ( cityADT c , long int *dim){
    if ( c->count ==0 ){
        *dim=0;
        return NULL;
    }
    TListNeigh aux=c->firstNeigh ;
    double * new= malloc ( c->count * sizeof ( double ));
    if ( new==NULL ){
        *dim=ERROR;
        return NULL;
    }

    double numAux;
    for ( size_t i = 0; i < c->count; i++){
        //arboles por habitante redondeado a 2 decimales
        numAux=(double)((floor((aux->trees/aux->people)*100))/100);
        new[i]=numAux;
        aux=aux->tail;
    }
    *dim=c->count; 
    return new;
}
