typedef struct nodo{
    int num;
    struct nodo *sig;
}nodo;

int total(nodo *p){
    int n=0;
    nodo *aux=p;
    while(aux != NULL){//Se considera solo el nodo actual y no el que le sigue
            n++;
            aux = aux->sig;
    }
    return n;
}

void agregarElemento(nodo **p,int numero){
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->num=numero;
    nuevo->sig=NULL;
    if(*p==NULL){
        *p=nuevo;
        return;
    }else{
        nodo *aux=*p;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig=nuevo;
    }
}

void imprimeLista(nodo *p){
    nodo *aux =p;
    while(aux != NULL){//Se pregunta si aux es null para imprimir todos los nodos, pq en el ultimo elemento no existiria aux->sig
        printf("%d\t", aux->num);
        aux = aux->sig;
    }
    putchar('\n');
}

void agregarOrdenado(nodo **p, int numero){
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->num=numero; //Se agrega nodo por nodo en la nueva lista ordenada
    nuevo->sig=NULL;
    if(*p == NULL || numero < (*p)->num){//Pregunta si esta vacia o es menor al primer numero de la lista
        nuevo->sig = *p;
        *p = nuevo;
        return;
    }else{
        nodo *aux=*p;//Se utiliza aux para recorrer la lista
        while(aux->sig != NULL && (aux->sig->num)<numero){ //Se pregunta si existe un siguiente nodo y si el valor del siguiente nodo es menor que el numero
            aux = aux->sig;
        }
        nuevo->sig=aux->sig;//Se asigna el nodo correspondiente para no perder los elementos que le siguen en la lista
        aux->sig=nuevo;//Se agrega el nodo nuevo
    }
}
void liberarLista(nodo **p) {
    nodo *aux;
    while (*p != NULL) {
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
}
void ordenar(nodo *p, nodo **ord){
    liberarLista(ord);
    if(total(p)==0)return;
    nodo *aux=p;
    while(aux != NULL){
        agregarOrdenado(ord,aux->num);//Se agrega cada nodo de p en ord de forma ordenada
        aux=aux->sig;
    }
}

void invertir(nodo **p){
    if(total(*p)==0)return;
    nodo *aux = *p;
    nodo *next;
    nodo *prev = NULL;
    while(aux != NULL){
        next = aux->sig;
        aux->sig=prev;
        prev = aux;
        aux = next;
    }
    *p=prev;
}

void eliminaDuplicados(nodo **p){
    if(total(*p)==0)return;
    nodo *actual=*p;//Se guarda el nodo actual

    while(actual != NULL && actual->sig != NULL){//Se pregunta si existe el nodo y su consecutivo
        nodo *anterior = actual;//Se realiza una copia del nodo actual
        nodo *comparador = actual->sig;//El comparador inicia en actual+1
        while(comparador != NULL){//Se busca mientras exista un comparador
            if(actual->num == comparador->num){//Si es el mismo numero borra el nodo comparador y conecta la lista con anterior
                anterior->sig = comparador->sig;
                free(comparador);
                comparador=anterior->sig;//Itera en la lista
            }else{
                anterior = comparador;//Iguala anterior con comparador e itera comparador en 1
                comparador = comparador->sig;
            }
        }
        actual = actual->sig;//Itera sobre el valor actual
    }

}
float media(nodo *p){
    int n = total(p);
    if(n==0)return 0;

    float sum = 0;
    nodo *aux = p;
    while(aux != NULL){//Se pregunta si aux es null para imprimir todos los nodos, pq en el ultimo elemento no existiria aux->sig
        sum+=(float)aux->num;
        aux = aux->sig;
    }
    return (float)sum/n;
}
float mediana(nodo *p, nodo **ord){
    int n = total(p);
    if(n==0)return 0;
    int mediana = n/2;
    int contador = 0;
    ordenar(p,ord);
    nodo *aux = *ord;
    if(n%2!=0){
        while(aux != NULL){
            if(++contador == mediana+1){
                return aux->num;
            }
            aux = aux->sig;
        }
    }
    else{
        float sum = 0;
        while(aux != NULL){
            if(++contador == mediana){
                sum += aux->num;
                sum += aux->sig->num;
                return sum/2;
            }
            else
                aux = aux->sig;
        }
    }
}
float varianza(nodo *p){
    float med = media(p), sum=0;
    int n = total(p);
    nodo *aux = p;
    while(aux != NULL){
        sum += (float)(aux->num-med)*(aux->num-med);
        aux = aux->sig;
    }
    return (float)sum/n;
}

float desviacion(nodo *p){
    float var = varianza(p);
    return sqrt(var);
}

void moda(nodo *p, nodo **ord){
    int n = total(p);
    if(n == 0){
        printf("La lista esta vacia.\n");
        return;
    }

    int *nums;
    int *rep;
    nums = (int*)calloc(n, sizeof(int));
    rep = (int*)calloc(n, sizeof(int));
    int i = 0;
    ordenar(p, ord);
    nodo *aux = *ord;
    int anterior = aux->num;
    nums[0] = anterior;
    rep[0] = 1;
    aux = aux->sig;

    while(aux != NULL){
        if(anterior == aux->num){
            rep[i]+=1;
        }
        else{
            nums[++i] = aux->num;
            rep[i]+=1;
        }
        anterior = aux->num;
        aux = aux->sig;
    }
    int max_rep = 0;
    int contaModas = 0;
    for(int j = 0; j <= i; j++){
        if(rep[j] > max_rep){
            max_rep = rep[j];
            contaModas = 1;
        }
        else if(rep[j] == max_rep){
            contaModas++;
        }
    }
    if(contaModas > 3){
            printf("No hay moda (%d numeros con la misma frecuencia)", contaModas);
            return;
    }

    printf("Moda(s): \n");
    for(int j = 0; j <= i; j++){
        if(rep[j] == max_rep){
            printf("%d (%d repeticiones)", nums[j], max_rep);
            printf("\n");
        }
    }
    printf("\n");

    free(nums);
    free(rep);
}
