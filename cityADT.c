#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
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

static void freeTreeRec(TListTree list){
    if(list==NULL)
        return;

    free(list->treeName);       //Libero el nombre del arbol
    freeTreeRec(list->tail);    //Paso recursivo para el siguiente arbol
    free(list);                 //Finalmente liberamos el nodo de los arboles
}
static void freeRecNeigh(TListNeigh list){
    if(list==NULL)                          
        return;
    free(list->neighName);          //Libero el nombre del barrio
    freeTreeRec(list->firstTree);   //Liberamos los arboles
    freeRecNeigh(list->tail);       //Paso recursivo para el siguiente barrio
    free(list);                     //Finalmente liberamos el nodo de los barrios
}
void freeCity(cityADT c){
    freeRecNeigh(c->firstNeigh);    //Liberamos cada barrio
    free(c);                        //Finalmente liberamos la cuidad
}

static TListNeigh addNeighRec(TListNeigh list, char *neigh, size_t cantHab ,int *flag ){
    int c;
    if( list==NULL || (c=strcasecmp(list->neighName,neigh))>0 ){    //Chequeamos si la lista esta vacia o si el barrio en el que estoy es alfabeticamente mayor
        TListNeigh aux=malloc(sizeof(TNeigh));                      //Si se cumple creamos un nodo auxiliar 
        
        if(aux==NULL){                                              //Si no pudo darle espacio al aux entonces el flag sale con error y corto
          *flag=ERROR;                                              //Devolvemos list pues sino podríamos perder la sublista que sería tail
           return list;                                             //y cuando hagamos freeCity en el front nos quedarían nodos sin liberar
        }
    
        aux->tail=list;                                             //Si no hubo problema el nodo lo asigno adelante de la lista
        aux->people=cantHab;                                        //Asigno la cantidad de habitantes
        aux->neighName=malloc(strlen(neigh)+1);                     //Le doy espacio al nombre debido a que es un char*
        if(aux->neighName==NULL){                                   //Si no pudo darle espacio al nombre, flag sale con error y corto
          *flag=ERROR;
           return list;
        }
        strcpy(aux->neighName,neigh);                               //Si no hubo poblema con el espacio copio el nombre del barrio 
        aux->firstTree=NULL;                                        //Inicializo la lista de arboles, la cantidad de arboles y el arbol mas popular en NULL/0
        aux->mostPop=NULL;                                          //Decidimos usar malloc y no calloc pues la mitad de los campos tiene un valor inicial
        aux->trees=0;                                               //y haríamos un ciclo extra
     
        *flag=1;                                                    //No hubo problema entonces flag sale con 1
        return aux;                                                 //Devuelvo la nueva lista
    } 

    if(c==0)                                                        //Si c==0 quiere decir que el barrio ya existe entonces no modifico y retorno la lista original
        return list;  

    list->tail=addNeighRec(list->tail, neigh, cantHab,  flag );     //Paso recursivo si el nombre que busco es mayor alfabeticamente al barrio en el que estoy, entonces paso al  siguente
    return list;
}
int addNeigh(cityADT c, char * neigh, size_t cantHab){
    int flag=0;                                                        //Creamos un flag por algun error en la funcion addNeighRec
    c->firstNeigh=addNeighRec(c->firstNeigh, neigh, cantHab, &flag );  //Llamamos a la funcion addNeighRec con la lista de los barrios
    if(flag!=-1)                                    
        c->count++;                                                    //Finalmente si el flag no indica error, entonces se suma un nuevo barrio

    return flag;
}

//Funcion para buscar un barrio en particular en la lista
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
static TListTree addTreeRec(TListTree list, char *tree , int *flag, TListNeigh node ){
    int c;
    if( list==NULL || (c=strcasecmp(list->treeName,tree))>0 ){      //Chequeo si la lista de arboles esta vacia o el arbol en el que estoy es mayor alfabeticcamente que el que me piden
        TListTree aux=malloc(sizeof(Ttree));                        //eso indicaria que el que busco no va a estar pues esta ordenada alfabeticamente. Creo un nodo que va a ser el nuevo arbol
        
        if ( aux==NULL ){                                           //Si el malloc tiro algun error (no le pudo asignar memoria), flag sale con error y corto
            *flag=ERROR;
            return list;
        }
        aux->tail=list;                                             //El nuevo arbol va a estar al principio, entonces le asigno la sublista atras
        if(node->mostPop == NULL){                                  //Si el barrio al que estamos agredando el arbol no tiene arbol mas popular se lo asigno
            node->mostPop = aux;                                    
        }
        aux->count=1;                                               //Inicializo la cantidad de arboles en 1 pues es el primero de su tipo
        aux->treeName=malloc(strlen(tree)+1);                       //Le doy espacio al nombre del arbol pues es un char *
        if(aux->treeName==NULL){                                    //Si fallo al darle memoria, flag sale con error y corto
          *flag=ERROR;
           return list;
        }
        strcpy(aux->treeName, tree);                                //Si no hubo problema, copio el nombre del arbol
        return aux;
    } 

    if(c==0){                                                       //Si ya existe el arbol pedido, solamente incremento la catidad
        list->count++;
        if(list->count > node->mostPop->count){                     //Si la cantidad de arboles es mayor a la cantidad de los mas populares
            node->mostPop = list;                                   //entonces le asigno la lista (nodo de arbol cuya cantidad es mayor)
        }
        return list; 
    }

    list->tail=addTreeRec(list->tail, tree, flag, node );            //Si el arbol en el que estoy es menor alfabeticamente del que busco, paso al isguente
    return list;
}
int addTree(cityADT c, char * neigh, char *tree){
    int flag=0 ;                                                    //Flag por si la funcion recursiva tiene algun error
    TListNeigh aux=searchNeigh(c->firstNeigh,neigh);                //Busco el barrio que quiero y lo asigno en un nodo auxiliar
    if(aux==NULL){                                                  //Si no esta el barrio corto
        return flag;
    }
    aux->firstTree=addTreeRec(aux->firstTree, tree , &flag, aux );  //Agrego el arbol al barrio encontrado
    if (flag!=-1){                                                  //Si el flag no indica algun error entonces sumo la cantidad de arboles
        aux->trees++;   
    }
    return flag;
}

int retrieveData(cityADT c , char ***neighName , char *** mostPop, double ** avg,size_t *dim){
    if(c->count == 0){                                              //Valido que haya barrios
        *dim=0;
        return 0;
    }
    TListNeigh aux = c->firstNeigh;                                 //Creo nodo auxiliar con el primer barrio
    *neighName = realloc(*neighName, (c->count+1)* sizeof(char*));  //Le doy espacio al nombre del barrio para los archivos query1.csv y query2.csv
    if(*neighName == NULL){                                         //Si fallo al darle espacio, dim sale en 0 y corto con error
        *dim=0;
        return ERROR;
    }
    *mostPop=realloc(*mostPop, (c->count+1)* sizeof(char *));       //Le doy espacio al vector de arboles mas populares para el archivo query2.csv 
    if(*mostPop==NULL){                                             //Si fallo al darle espacio, dim sale en 0 y corto con error
        *dim=0;
        free(*neighName);                                           //Libero los barrios pues ya le di espacio
        return ERROR;
    }
    *avg = realloc(*avg, (c->count) *sizeof(double));               //Le doy espacio al vector del promedio cantidad de arboles por habitantes
    if(*avg==NULL){                                                 //Si falla al darle espacio, tengo que liberar los recursos, dim sale con 0 y corto ocn error
        *dim=0;
        free(*neighName);
        free(*mostPop);
        return ERROR;
    }
    size_t i=0;                                                     //Inicializo el iterador de los barrios
    while(aux != NULL){
        (*neighName)[i] = malloc(strlen(aux->neighName)+1);         //Le doy espacio para asignar el nombre del barrio
        if ( (*neighName)[i]==NULL ){                               //Si fallo al darle espacio, libero los recursos utilizados, dim sale en 0 y corto con error
            *dim=0;
            (*mostPop)[i]=NULL;
            return ERROR;
        }
     
        (*mostPop)[i] = malloc(strlen(aux->mostPop->treeName)+1);   //Le doy espacio para asignar el nombre del arbol mas popular
        if ( (*mostPop)[i]==NULL ){                                 //Si alguno falla al darle espacio libero los recursos, dim sale con 0 y corto con error
            (*neighName)[i+1]=NULL;                                 //Agrego marca de final en la posicion siguiente pues (*neighName)[i] anduvo, 
            *dim=0;                                                 
            return ERROR;
        }

        (*avg)[i]=((floor(((double)aux->trees/aux->people)*100))/100);  //Si no hubo problema asigno en cada uno su valor correspondiente
        strcpy((*neighName)[i],aux->neighName);
        strcpy((*mostPop)[i],aux->mostPop->treeName);
        i++;                                                            //Incremento el iterador para pasar al siguente
        aux = aux->tail;                                                //Paso  al siguente barrio
    }
    (*neighName)[i]=NULL;                                               //Marca de final para función freeRemaining 
    (*mostPop)[i]=NULL;

    *dim=c->count;                                                      //Dim sale con la cantidad de barrios totales
    return 1;       
}
