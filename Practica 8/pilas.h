typedef struct nodo{
    char c;
    struct nodo *sig;
}nodo;

int vacia(nodo *p){
    return (p == NULL);
}

void anula(nodo **p){
    if (vacia(*p)){
        puts("La lista se ha vaciado");
        return;
    }
    nodo *aux;
    while(*p!= NULL){
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
    puts("La lista se ha vaciado");
}

char tope(nodo *p){
    if (vacia(p)) return '\0';//Valor nulo = Lista vacia
    return p->c;
}

char saca(nodo **p){
    if (vacia(*p)) return '\0'; //Valor nulo = Lista vacia
    nodo *aux = *p;
    *p = aux->sig;
    char valor = aux->c;
    free(aux);
    return valor;
}

void mete(char x, nodo **p){
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->c = x;
    nuevo->sig = *p; //Guarda en sig el ultimo elemento insertado en la pila
    *p = nuevo;//Inserta en la primer posicion el nuevo elemento
}
