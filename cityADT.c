#include <stdlib.h>
#include "cityADT.h"

typedef struct tree{
	char *treeName;     //nombre cientifico arbol
	size_t count ;      //cant de esa especie
	struct tree * tail ;//puntero a siguiente
}tree;

typedef tree * TListTree;

typedef struct neigh{
	TListTree firstTree;//puntero a primero de la lista de arboles
	size_t people;      //habitantes del barrio
	size_t trees;       //cant total de arboles
    char *neighName;         //nombre de barrio
    struct neigh *tail;	//puntero a siguiente	
}neigh; 

typedef neigh * TListNeigh;

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

/* ******************************************************************************* */
static TListNeigh addNeighRec(TListNeigh list, char *neigh, size_t cantHab ,char *flag){
    int c;
    if( list==NULL || (c=compare(list->neighName,neigh))>0 ){
        TListNeigh aux=calloc(1,sizeof(neigh));
        aux->tail=list;
        aux->people=cantHab;
        aux->neighName=neigh; /* ojo */
        *flag=1;
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
    c->count+=flag;
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

static TListTree addTreeRec(TListTree list, char *tree){
    int c;
    if( list==NULL || (c=strcmp(list->treeName,tree))>0 ){
        TListTree aux=malloc(sizeof(tree));
        aux->tail=list;
        aux->count=1;
        aux->treeName=tree; /* ojo */
        return aux;
    } 

    if(c==0){
        list->count++;
        return list; 
    }

    list->tail=addTreeRec(list->tail, tree);
    return list;
}
int addTree(cityADT c, char * neigh, char *tree){
    TListNeigh aux=searchNeigh(c->firstNeigh,neigh);
    if(aux==NULL)
        return 0;

    aux->firstTree=addTreeRec(aux->firstTree, tree);
    aux->trees++;
    return 1;
}


static char * findMostPopular ( TListTree list ){
    TListTree aux=list;
    size_t max=0;
    char *new=NULL;
    while ( aux!=NULL ){
        if ( aux->count > max ){
            max=aux->count ;
            new=realloc(new , ( strlen(aux->treeName))+1 );
            strcpy( new , aux->treeName);
        }    
        aux=aux->tail;
    }
    return new;
}
char ** mostPopularTree(cityADT c){
    TListNeigh aux=c->firstNeigh;
    char **new=malloc(sizeof(char*)*c->count);

    for(int i=0; i<c->count ; i++){
        new[i]=findMostPopular( aux->firstTree );
        aux=aux->tail;
    }

    return new;
}

char ** showAllNeigh( cityADT c ){
    char** new= malloc( c->count * sizeof(char*));
    TListNeigh aux=c->firstNeigh ;
    for (size_t i = 0; i < c->count; i++){
        new[i]=malloc( strlen(aux->neighName )+1 );
        strcpy(new[i], aux->neighName);
        aux=aux->tail;
    }
    return new;
}

double* treesPerPerson ( cityADT c ){
    TListNeigh aux=c->firstNeigh ;
    double * new= malloc ( c->count * sizeof ( double ));
    double numAux;

    for ( size_t i = 0; i < c->count; i++){
        //arboles por habitante redondeado a 2 decimales
        numAux=((floor((aux->trees/aux->people)*100))/100);
        new[i]=numAux;
        aux=aux->tail;
    }
    //Hay que modificar la funcion porque los ordena alfabeticamente y aca tiene que quedar asi:
    /* 9;0.24
    ** 10;0.20
    ** 11;0.20
    ** 15;0.16
    ** 12;0.11
    ** Notar que el promedio mas grande es el primero y si hubiera empate en el truncado, se desempata
    ** con el orden alfabetico.
    */
    return new;
}
