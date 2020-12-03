#include <math.h>
#include <stdio.h>
#include "cityADT.h"
#define ERROR -1 
#define EPSILON 0.001

typedef struct Ttree{
	char *treeName;     //nombre cientifico arbol
	size_t count ;      //cant de esa especie
	struct Ttree * tail ;//puntero a siguiente
}Ttree;

typedef Ttree * TListTree;

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

/*Hacer el free de cada nombre */
static void freeTreeRec(TListTree list){
    if(list==NULL)
        return;

    free(list->treeName);
    freeTreeRec(list->tail);
    free(list);
}
static void freeRecNeigh(TListNeigh list){
    if(list==NULL)
        return;
    free(list->neighName);
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
        TListNeigh aux=calloc(1,sizeof(TNeigh));
        if(aux==NULL){
          *flag=ERROR;
           return NULL;
        }
        aux->tail=list;
        aux->people=cantHab;
        aux->neighName=malloc(strlen(neigh)+1);
        if(aux->neighName==NULL){
          *flag=ERROR;
           return NULL;
        }

        strcpy(aux->neighName,neigh);
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
    if(flag!=-1)
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

static TListTree addTreeRec(TListTree list, char *tree , int *flag){
    int c;
    if( list==NULL || (c=strcasecmp(list->treeName,tree))>0 ){
        TListTree aux=malloc(sizeof(Ttree));
        if ( aux==NULL ){
            *flag=ERROR;
            return NULL;
        }
        aux->tail=list;
        aux->count=1;
        aux->treeName=malloc(strlen(tree)+1); 
        if(aux->treeName==NULL){
          *flag=ERROR;
           return NULL;
        }
        strcpy(aux->treeName, tree);
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
    if (flag!=-1){
        aux->trees++;   
    }
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
char ** mostPopularTree(cityADT c ,size_t *dim ){
    if ( c->count ==0 ){
        *dim=0;
        return NULL;
    }
    TListNeigh aux=c->firstNeigh;
    char **new=malloc(sizeof(char*)* c->count);

    if ( new== NULL ){
        *dim=0;
        return NULL;
    }

    for(int i=0; i<c->count ; i++){
        new[i]=findMostPopular( aux->firstTree );
        if ( new[i]== NULL ){
            return NULL;
        }
        aux=aux->tail;
    }

    *dim=c->count;
    return new;
}
char ** showAllNeigh( cityADT c , size_t *dim ){
    if ( c->count ==0 ){
        *dim=0;
        return NULL;
    }

    char** new= malloc( c->count * sizeof(char*));
    if ( new== NULL ){
        *dim = 0;
        return NULL;
    }
    TListNeigh aux=c->firstNeigh ;
    for (size_t i = 0; i < c->count; i++){
        new[i]=malloc( strlen(aux->neighName )+1 );
        if ( new[i]==NULL ){
            return NULL;
        }
        strcpy(new[i], aux->neighName);
        aux=aux->tail;
    }
    *dim=c->count;
    return new;
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
double* treesPerPerson ( cityADT c, char** neighs, size_t *dim){
    if ( c->count ==0 ){
        *dim=0;
        return NULL;
    }
    TListNeigh aux=c->firstNeigh ;
    double * new= malloc ( c->count * sizeof ( double ));
    if ( new==NULL ){
        *dim=0;
        return NULL;
    }

    double numAux;
    for ( size_t i = 0; i < c->count; i++){
        //arboles por habitante redondeado a 2 decimales
        numAux=((floor(((double)aux->trees/aux->people)*100))/100);
        new[i]=numAux;
        aux=aux->tail;
    }
    sortq1( neighs , new , *dim );
    *dim=c->count; 
    return new;
}

