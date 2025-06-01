int vacia2(nodo *p){
    return (p == NULL);
}

void anula2(nodo **p){
    if (vacia2(*p)){
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

char tope2(nodo *p){
    if (vacia2(p)) return 0;//Valor nulo = Lista vacia
    return p->num;
}

char saca2(nodo **p){
    if (vacia2(*p)) return 0; //Valor nulo = Lista vacia
    nodo *aux = *p;
    *p = aux->sig;
    char valor = aux->num;
    free(aux);
    return valor;
}

void mete2(int x, nodo **p){
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->num = x;
    nuevo->sig = *p; //Guarda en sig el ultimo elemento insertado en la pila
    *p = nuevo;//Inserta en la primer posicion el nuevo elemento
}
