#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int idMascota;
    char nombreMascota[50];
             int tipo; // 1=gato 2=perro 3=loro
}stMascota ;

typedef struct {
    int idMascota;
    struct nodoDobleMascota * siguiente;
    struct nodoDobleMascota * anterior;
}nodoDobleMascota;

typedef struct {
    stMascota dato ;
    struct nodoMascota* siguiente;
}nodoMascota;

typedef struct {
    nodoDobleMascota * primero;
    nodoDobleMascota * ultimo;
}fila ;

nodoMascota* crearNodomascota(stMascota);
stMascota cargarmascota(stMascota);
nodoMascota* agregarenorden(nodoMascota*,nodoMascota*);
void mostrartipoparticular(nodoMascota*,int);
nodoDobleMascota* crearNododoble(int);
nodoDobleMascota* agregarFinal2(nodoDobleMascota*,nodoDobleMascota*);
fila* agregar(fila*,int);
void extraer(fila*);
int comprobarID(nodoMascota*,int);
fila* pasarListaSimpleaFila(fila*,nodoMascota*);
void eliminarnodo(nodoMascota*,int );
int vaciarFila(fila*);
stMascota cargarmascotaautomatico(stMascota);
void mostrarLista(nodoMascota*);

int main()
{

    int tipo;
    printf("tipo 1:gato \n");
    printf("tipo 2: perro \n");
    printf("tipo 3: loro \n");
    printf("que tipo de mascota quiere ver: \n");
    fflush(stdin);
    scanf("%d",&tipo);
    stMascota mascota=cargarmascota(mascota);
    nodoMascota* aux=crearNodomascota(mascota);
    nodoMascota* lista=aux;
    for(int i=0;i<10;i++){
        stMascota aux2;
        nodoMascota* mascotarandom=crearNodomascota(cargarmascotaautomatico(aux2));
        agregarenorden(aux,mascotarandom);
    }
    mostrartipoparticular(lista,tipo);
    mostrarLista(lista);
    return 0;
}

///funcion auxiliar
stMascota cargarmascotaautomatico(stMascota aux){
    srand(time(NULL));
    aux.idMascota=rand()%100+1;
    strcpy(aux.nombreMascota,"pepe");
    aux.tipo=rand()%3+1;
    return aux;
}
///funcion punto 1
nodoMascota* crearNodomascota(stMascota dato){
    nodoMascota* aux=malloc(sizeof(nodoMascota));
    aux->dato=dato;
    aux->siguiente=NULL;
    return aux;
}
///funcion punto 1
stMascota cargarmascota(stMascota aux){
    int flag=0;
    printf("ingrese el id: \n");
    fflush(stdin);
    scanf("%d",&aux.idMascota);
    printf("ingrese el nombre: \n");
    fflush(stdin);
    gets(aux.nombreMascota);
    while(flag==0){
    printf("ingrese el tipo: \n");
    fflush(stdin);
    scanf("%d",&aux.tipo);
    if((aux.tipo>3)&&(aux.tipo<1)){
        printf("ingrese un numero del 1 al 3");
        }else{
            flag=1;
        }
    }
    return aux;
}
///funcion punto 2
nodoMascota* agregarenorden(nodoMascota* lista,nodoMascota* nuevo){
    if(lista==NULL){
        lista=nuevo;
    }else if(nuevo->dato.tipo<=lista->dato.tipo){
        nuevo->siguiente=lista;
        lista=nuevo;
    }else{
        nodoMascota* ante;
        nodoMascota* seg=lista;
        while((seg->siguiente!=NULL)&&(nuevo->dato.tipo<lista->dato.tipo)){
            ante=seg;
            seg=seg->siguiente;
        }
        if(seg->siguiente!=NULL){
        ante->siguiente=nuevo;
        nuevo->siguiente=seg;
        }else{
            seg->siguiente=nuevo;
        }
    }
    return lista;
}
///funcion punto 3
void mostrartipoparticular(nodoMascota* lista,int tipo){
    if(lista->siguiente!=NULL){
        mostrartipoparticular(lista->siguiente,tipo);
        if(lista->dato.tipo==tipo){
        printf("%d\n",lista->dato.idMascota);
        printf("%s\n",lista->dato.nombreMascota);
        }
    }
}
///funcion auxiliar
nodoDobleMascota* crearNododoble(int idmascota){
    nodoDobleMascota* aux=malloc(sizeof(nodoDobleMascota));
    aux->idMascota=idmascota;
    aux->anterior=NULL;
    aux->siguiente=NULL;
    return aux;
}
///funcion auxiliar
nodoDobleMascota* agregarFinal2(nodoDobleMascota* lista,nodoDobleMascota* nuevo){
    if(lista==NULL){
        nuevo->anterior=lista;
        lista=nuevo;
    }else{
        nodoDobleMascota* seg=lista;
        while(seg->siguiente!=NULL){
            seg=seg->siguiente;
        }
        seg->siguiente=nuevo;
        nuevo->anterior=seg;
        nuevo->siguiente=NULL;
    }
    return lista;
}
///funcion punto 4
fila* agregar(fila* filin,int idmascota){
    nodoDobleMascota* nuevo=crearNododoble(idmascota);
    if(filin->primero==NULL){
        filin->primero=nuevo;
        filin->ultimo=nuevo;
    }else{
        filin->primero=agregarFinal2(filin->primero,nuevo);
        filin->ultimo=nuevo;
    }
    return filin;
}
///funcion punto 4
void extraer(fila* filin){
    if(filin->primero!=NULL){
    nodoDobleMascota* aborrar=filin->primero;
    filin->primero=aborrar->siguiente;
    free(aborrar);
    }
}
///funcion punto 5
int comprobarID(nodoMascota* lista,int aComprobar){
    int flag=0;
    if(lista!=NULL){
        nodoMascota* seg=lista;
        while(seg!=NULL){
            if(seg->dato.idMascota==aComprobar){
                flag=1;
            }
            seg=seg->siguiente;
        }
    }
    return flag;
}
///funcion punto 6
fila* pasarListaSimpleaFila(fila* filin,nodoMascota* lista){
    char control='s';
    int flag=0;
    int aux;
    while(control=='s'){
        while((flag==0)&&(lista!=NULL)){
            printf("ingrese un id: \n");
            fflush(stdin);
            scanf("%d",&aux);
            int check=comprobarID(lista,aux);
            if(check==0){
                printf("esa id no existe.");
                system("cls");
            }else{
                flag=1;
            }
        }if(lista!=NULL){
            eliminarnodo(lista,aux);
            filin=agregar(filin,aux);
            printf("desea agregar otro: s/n\n");
            fflush(stdin);
            scanf("%c",&control);
        }else{
            printf("la lista esta vacia.");
            system("cls");
        }
    }
    return filin;
}
///funcion auxiliar
void eliminarnodo(nodoMascota* lista,int dato){
    if(lista!=NULL){
        nodoMascota* ante;
        nodoMascota* seg=lista;
        int flag=0;
        while((seg!=NULL)&&(flag==0)){
            if(seg->dato.idMascota==dato){
                flag=1;
            }else{
                ante=seg;
                seg=seg->siguiente;
            }
        }
        ante->siguiente=seg->siguiente;
        free(seg);
    }
}
///funcion punto 7
int vaciarFila(fila* filin){
    int cantidadElementos=0;
    while(filin->primero!=NULL){
        extraer(filin);
       cantidadElementos++;
    }
    return cantidadElementos;
}
///funcion auxiliar
void mostrarLista(nodoMascota* lista){
    nodoMascota* aux=lista;
    while(aux!=NULL){
        printf("id: %d\n\n",aux->dato.idMascota);
        printf("nombre: %s\n\n",aux->dato.nombreMascota),
        printf("tipo: %d\n\n",aux->dato.tipo);
        aux=aux->siguiente;
    }
}
