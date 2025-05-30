
typedef struct nodo2{
    int c;
    struct nodo2 *sig;
}nodo2;

int vacia2(nodo2 *p){
    return (p == NULL);
}

void anula2(nodo2 **p){
    if (vacia2(*p)){
        puts("La lista se ha vaciado");
        return;
    }
    nodo2 *aux;
    while(*p!= NULL){
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
    puts("La lista se ha vaciado");
}

char tope2(nodo2 *p){
    if (vacia2(p)) return 0;//Valor nulo = Lista vacia
    return p->c;
}

char saca2(nodo2 **p){
    if (vacia2(*p)) return 0; //Valor nulo = Lista vacia
    nodo2 *aux = *p;
    *p = aux->sig;
    char valor = aux->c;
    free(aux);
    return valor;
}

void mete2(int x, nodo2 **p){
    nodo2 *nuevo = (nodo2*)malloc(sizeof(nodo2));
    nuevo->c = x;
    nuevo->sig = *p; //Guarda en sig el ultimo elemento insertado en la pila
    *p = nuevo;//Inserta en la primer posicion el nuevo elemento
}
