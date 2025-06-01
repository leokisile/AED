typedef struct nodo{
    int num;
    struct nodo *sig;
} nodo;

int vacia(nodo *p){
    if(p == NULL) return 1;
    else return 0;
}

void pone_en_cola(nodo **p, int n){
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->num = n;
    if(*p==NULL){
        nuevo->sig = nuevo;
    }
    else{
        nuevo->sig = (*p)->sig;
        (*p)->sig = nuevo;
    }
    *p = nuevo;
}

int frente(nodo *p){
    if(p == NULL) return 0;//Valor nulo
    return p->num;
}

int quita_de_cola(nodo **p){
    if((*p) == NULL) return 0;
    int ret = (*p)->sig->num;
    if(*p == (*p)->sig){
        free(*p);
        *p = NULL;
    }
    else{
        nodo *aux = (*p)->sig;
        (*p)->sig = aux->sig;
        free(aux);
    }
    return ret;
}

void anula(nodo **p){
    if ((*p)==NULL){
        puts("La lista se ha vaciado");
        return;
    }
    nodo *actual = (*p)->sig;
    nodo *sig;
    while (actual != *p) {
        sig = actual->sig;
        free(actual);
        actual = sig;
    }

    // Libera el último nodo (el que apunta a sí mismo)
    free(*p);
    *p = NULL;

    puts("La lista se ha vaciado");
}
