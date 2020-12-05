#include <math.h>
#include <stdio.h>
#include <string.h>
#include "cityADT.h"
#define ERROR -1 

typedef struct Ttree{
	char *treeName;         //nombre cientifico del arbol
	size_t count ;          //cantidad de esa especie
	struct Ttree * tail;    //puntero a siguiente
}Ttree;

typedef Ttree * TListTree;

typedef struct TNeigh{
	TListTree firstTree;    //puntero al primero de la lista de arboles
    TListTree mostPop;      //puntero al arbol mas popular
	size_t people;          //habitantes del barrio
	size_t trees;           //cantidad total de arboles
    char *neighName;        //nombre de barrio
    struct TNeigh *tail;   	//puntero al siguiente	
}TNeigh; 

typedef TNeigh * TListNeigh;

typedef struct cityCDT{
	TListNeigh firstNeigh;  //puntero al primer barrio
	size_t count;           //cantidad de barrios
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
    if( list==NULL || (c=strcasecmp(list->neighName,neigh))>0 ){
        TListNeigh aux=malloc(sizeof(TNeigh));
        if(aux==NULL){
          *flag=ERROR;
           return NULL;
        }
        aux->tail=list;
        aux->people=cantHab;
        aux->neighName=malloc(strlen(neigh)+1);
        aux->firstTree=NULL;
        aux->mostPop=NULL;
        aux->trees=0;
        
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

//decidir si es mejor iterativo o recursivo

/*static TListNeigh searchNeigh(TListNeigh list, char *neigh){
    int c;
    if(list==NULL || (c=strcasecmp(list->neighName,neigh))>0 )
        return NULL;
    if(c==0)
        return list;
    return searchNeigh(list->tail, neigh);
}*/

static TListNeigh searchNeigh ( TListNeigh list , char *neigh ){
    int c;
    TListNeigh aux=list;
    while( aux!=NULL && (c=strcasecmp(aux->neighName,neigh))<=0){
        if ( c==0 ){
            return aux;
        }
        aux=aux->tail;
    }
    return NULL;
}

static TListTree addTreeRec(TListTree list, char *tree , int *flag, TListNeigh node){
    int c;
    if( list==NULL || (c=strcasecmp(list->treeName,tree))>0 ){
        TListTree aux=malloc(sizeof(Ttree));
        if ( aux==NULL ){
            *flag=ERROR;
            return list;
        }
        aux->tail=list;
        if(node->mostPop == NULL){
            node->mostPop = aux;
        }
        aux->count=1;
        aux->treeName=malloc(strlen(tree)+1); 
        if(aux->treeName==NULL){
          *flag=ERROR;
           return list;
        }
        strcpy(aux->treeName, tree);
        return aux;
    } 

    if(c==0){
        list->count++;
        if(list->count > node->mostPop->count){
            node->mostPop = list;
        }
        return list; 
    }

    list->tail=addTreeRec(list->tail, tree, flag, node);
    return list;
}
int addTree(cityADT c, char * neigh, char *tree){
    int flag=0;
    TListNeigh aux=searchNeigh(c->firstNeigh,neigh);

    if(aux==NULL)
        return flag;
        
    aux->firstTree=addTreeRec(aux->firstTree, tree , &flag, aux);
    if (flag!=-1){
        aux->trees++;   
    }
    return flag;
}

// static char * findMostPopular ( TListTree list ){
//     TListTree aux=list;
//     size_t max=0;
//     char *new=NULL;
//     while ( aux!=NULL ){
//         if ( aux->count > max ){
//             max=aux->count ;
//             new=realloc(new , ( strlen(aux->treeName))+1 );
//             if ( new == NULL ){
//                 return NULL;
//             }
//             strcpy( new , aux->treeName);
//         }    
//         aux=aux->tail;
//     }
//     return new;
// }

// char ** mostPopularTree(cityADT c ,size_t *dim ){
//     if ( c->count ==0 ){
//         *dim=0;
//         return NULL;
//     }
//     TListNeigh aux=c->firstNeigh;
//     char **new=malloc(sizeof(char*)* c->count);

//     if ( new== NULL ){
//         *dim=0;
//         return NULL;
//     }

//     for(int i=0; i<c->count ; i++){
//         new[i]=findMostPopular( aux->firstTree );
//         if ( new[i]== NULL ){
//             freeRemaining(new,i);
//             return NULL;
//         }
//         aux=aux->tail;
//     }

//     *dim=c->count;
//     return new;
// }
// char ** showAllNeigh( cityADT c , size_t *dim ){
//     if ( c->count ==0 ){
//         *dim=0;
//         return NULL;
//     }

//     char** new= malloc( c->count * sizeof(char*));
//     if ( new== NULL ){
//         *dim = 0;
//         return NULL;
//     }
//     TListNeigh aux=c->firstNeigh ;
//     for (size_t i = 0; i < c->count; i++){
//         new[i]=malloc( strlen(aux->neighName )+1 );
//         if ( new[i]==NULL ){
//             freeRemaining(new,i+1);
//             return NULL;
//         }
//         strcpy(new[i], aux->neighName);
//         aux=aux->tail;
//     }
//     *dim=c->count;
//     return new;
// }


// double* treesPerPerson ( cityADT c, char** neighs, size_t *dim){
//     if ( c->count ==0 ){
//         *dim=0;
//         return NULL;
//     }
//     TListNeigh aux=c->firstNeigh ;
//     double * new= malloc ( c->count * sizeof ( double ));
//     if ( new==NULL ){
//         *dim=0;
//         return NULL;
//     }

//     double numAux;
//     for ( size_t i = 0; i < c->count; i++){
//         //arboles por habitante redondeado a 2 decimales
//         numAux=((floor(((double)aux->trees/aux->people)*100))/100);
//         new[i]=numAux;
//         aux=aux->tail;
//     }
//     *dim=c->count; 
//     return new;
// }
static void freeRemaining(char **vec,size_t dim){
    if(vec == NULL)
        return;
    for (size_t i = 0; i < dim; i++)
        free(vec[i]);
    free(vec);
    return;
}
static void clearData(char ** data1, char ** data2, double * data3, size_t dim){
    freeRemaining(data1,dim);
    freeRemaining(data2,dim);
    free(data3);
}
int retrieveData(cityADT c , char **neighName , char** mostPop, double * avg, size_t *dim){
    if(c->count == 0){
        *dim=0;
        return 0;
    }
    TListNeigh aux = c->firstNeigh;
    neighName = realloc(neighName, c->count * sizeof(char*));
    if(neighName == NULL){
        *dim=0;
        return ERROR;
    }
    mostPop=realloc(mostPop, c->count *sizeof(char*));
    if(mostPop==NULL){
        *dim=0;
        free(neighName);
        return ERROR;
    }
    avg = realloc(avg, c->count *sizeof(double));
    if(avg==NULL){
        *dim=0;
        free(neighName);
        free(mostPop);
        return ERROR;
    }
    size_t i=0;
    while(aux != NULL){
        neighName[i] = malloc(strlen(aux->neighName)+1);
        mostPop[i]=malloc(strlen(aux->mostPop->treeName)+1);
        if(neighName[i] == NULL || mostPop[i] == NULL){
            clearData(neighName,mostPop,avg,i+1);
            *dim=0;
            return ERROR;
        }
        avg[i]=((floor(((double)aux->trees/aux->people)*100))/100);
        strcpy(neighName[i],aux->neighName);
        strcpy(mostPop[i],aux->mostPop->treeName);
        i++;
        aux = aux->tail;
    }
    *dim=c->count;
    return 1;
}


