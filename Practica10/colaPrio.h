int* creaCola(int tam){//Crea el espacio de memoeria y devuelve el apuntador
    return (int*)malloc(tam * sizeof(int));
}

void llenaCola(int* colaP, int tam, int Max, int Min){//Llena con números aleatorios
    int i;
    for(i=0;i<tam;i++){
        colaP[i] = rand() % (Max-Min+1) + Min;
    }
}

int esVacia(int* colaP){
    if(colaP == NULL) return 1; return 0;
}

int* copiaCola(int** ord, int* colaP, int tam){//Copia la cola a otra para el ordenamiento
    if(!esVacia(*ord)){
        free(*ord);
    }
    *ord = (int*)malloc(tam * sizeof(int));
    int i;
    for(i = 0; i<tam; i++){
        (*ord)[i] = colaP[i];
    }
}

void imprimeCola(int* colaP, int tam){
    if(esVacia(colaP)){
        puts("La cola es vacia");
        return;
    }
    int i;
    for(i=0; i<tam; i++)
        printf("%d\t", colaP[i]);
    putchar('\n');
}

int padre(int index){//identifica al valor padre del hijo
    return (index-1)/2;
}

int izq(int* colaP, int index){//Identifica a su primer hijo
    if(!esVacia(colaP)) return index*2 + 1; return 0;
}

int der(int* colaP, int index){//Identifica a su segundo hijo
    if(!esVacia(colaP)) return index*2 + 2; return 0;
}

void intercambia(int* num1, int* num2){
    int aux = *num1;
    *num1 = *num2;
    *num2 = aux;
}

void max_heapify(int* colaP, int index, int tam){//Realiza el intercambio entre los elementos para mantener la relación padre-hijos
    if(esVacia(colaP)) return;
    int l = izq(colaP, index), r=der(colaP, index), grande=0;
    if(l<tam && colaP[l]>colaP[index])//Identifica el elemento más grande entre el index y sus respectivos hijos
        grande = l;
    else
        grande = index;
    if(r<tam && colaP[r]>colaP[grande])
        grande = r;
    if(grande != index){
        intercambia(&colaP[index],&colaP[grande]);//Intercambia las posiciones en caso de que algún hijo sea más grande
        max_heapify(colaP, grande, tam);//Llama recursivamente
    }
}

void build_max_heap(int* colaP, int tam){//"Ordena" el heap usando la función anterior, de forma que el arreglo queda padre, hijo, hijo, nieto1, nieto2, nieto3, nieto4
    if(esVacia(colaP)) return;
    int heapSize=tam, i;
    for(i=tam/2-1; i>=0; i--){
        max_heapify(colaP, i, tam);
    }
}

int heapMaximum(int* colaP){//Devuelve el elemento raíz
    if(!esVacia(colaP)) return colaP[0]; return 0;
}

int heap_extract_max(int** colaP, int* tam){//Elimina el elemento raíz, ordena todo y devuelve el valor eliminado
    if(esVacia(*colaP)){
        puts("La cola es vacia");
        return 0;
    }
    int mx = (*colaP)[0];
    (*colaP)[0] = (*colaP)[*tam-1];
    (*tam) = (*tam)-1;
    *colaP = realloc(*colaP, *tam * sizeof(int));
    max_heapify(*colaP, 0, *tam);
    return mx;
}

void heap_increase_key(int* colaP, int index, int key){//Cambia el valor de un elemento y lo vuelve a ordenar
    if(key < colaP[index]){
        puts("El nuevo valor es menor que el anterior");
        return;
    }
    colaP[index] = key;
    while(index>0 && colaP[padre(index)]<colaP[index]){
        intercambia(&colaP[index], &colaP[padre(index)]);
        index = padre(index);
    }
}

void max_heap_insert(int** colaP, int* tam, int key){//Inserta un elemento al final y posteriormente lo ordena
    (*tam)=(*tam)+1;
    *colaP = realloc(*colaP, *tam * sizeof(int));
    (*colaP)[*tam-1]=0;
    heap_increase_key(*colaP, *tam-1, key);
}

void heapSort(int* colaP, int tam){//Extra el elemento raíz, lo pasa al final, ordena todos los elementos de 0 hasta el raízz-1 de forma recursiva
    build_max_heap(colaP, tam);
    int i, heapt = tam;
    for(i = tam-1; i>0; i--){
        intercambia(&colaP[0], &colaP[i]);
        heapt--;
        max_heapify(colaP, 0, heapt);
    }
}
