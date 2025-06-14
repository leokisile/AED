typedef struct nodoD{
    Alumno alumno;
    struct nodoD* sig;
    struct nodoD* ant;
}nodoD;

int esVacia(nodoD *p){
    if(p == NULL) return 1;
    return 0;
}

int totalElementos(nodoD *p){
    nodoD *aux = p;
    int i = 0;
    if(esVacia(p)) return 0;
    while(aux != NULL){
        aux = aux->sig;
        i++;
    }
    return i;
}

nodoD* buscarElemento(nodoD *p, int boleta){
    nodoD *aux = p;
    if(esVacia(p)) return NULL;
    while(aux != NULL && aux->alumno.boleta != boleta){
        aux = aux->sig;
    }
    return aux;
}

void ascendente(nodoD *p){
    nodoD *aux = p;
    int i = 1;
    if(esVacia(p)){
        puts("La lista esta vacia");
        return;
    }
    while(aux != NULL){
        printf("%d.- %d\t%s\t%s\n", i++, aux->alumno.boleta, aux->alumno.apellidos, aux->alumno.nombre);
        aux = aux->sig;
    }
}

void descendente(nodoD *q){
    nodoD *aux = q;
    int i = 1;
    if(esVacia(q)){
        puts("La lista esta vacia");
        return;
    }
    while(aux != NULL){
        printf("%d.- %d\t%s\t%s\n", i++, aux->alumno.boleta, aux->alumno.apellidos, aux->alumno.nombre);
        aux = aux->ant;
    }
}

void insertaOrdenado(nodoD **p, nodoD **q, int boleta, char nombre[30], char apellidos[30]) {
    nodoD *nuevo = (nodoD *)malloc(1 * sizeof(nodoD));
    nuevo->alumno = leerDatos(boleta, normMinus(nombre), normMinus(apellidos));
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    // Si es vacia
    if (esVacia(*p)) {
        *p = nuevo;
        *q = nuevo;
        return;
    }

    nodoD *aux = *p;

    // Si va al inicio
    if (strcmp(nuevo->alumno.apellidos, aux->alumno.apellidos) < 0) {
        nuevo->sig = *p;
        (*p)->ant = nuevo;
        *p = nuevo;
        return;
    }

    // Identificar el lugar a insertar
    while (aux->sig != NULL && strcmp(nuevo->alumno.apellidos, aux->sig->alumno.apellidos) > 0) {
        aux = aux->sig;
    }

    // Si es al final
    if (aux->sig == NULL) {
        aux->sig = nuevo;
        nuevo->ant = aux;
        *q = nuevo;
    }
    // Si es en medio
    else {
        nuevo->sig = aux->sig;
        nuevo->ant = aux;
        aux->sig->ant = nuevo;
        aux->sig = nuevo;
    }
}

void moverOrdenado(nodoD **p, nodoD **q, nodoD *dato){
    nodoD *aux;

    // Desconectamos el nodo
    if (dato->ant != NULL)
        dato->ant->sig = dato->sig;
    else
        *p = dato->sig;  // Era el primero

    if (dato->sig != NULL)
        dato->sig->ant = dato->ant;
    else
        *q = dato->ant;  // Era el ultimo

    dato->sig = NULL;
    dato->ant = NULL;

    // Si la lista queda vacia (solo era 1)
    if (*p == NULL) {
        *p = *q = dato;
        return;
    }

    aux = *p;

    // Si se inserta al inicio
    if (strcmp(dato->alumno.apellidos, aux->alumno.apellidos) < 0) {
        dato->sig = *p;
        (*p)->ant = dato;
        *p = dato;
        return;
    }

    // Si se inserta en medio o al final
    while (aux->sig != NULL && strcmp(dato->alumno.apellidos, aux->sig->alumno.apellidos) > 0) {
        aux = aux->sig;
    }

    if (aux->sig == NULL) {
        // Se inserta al final
        aux->sig = dato;
        dato->ant = aux;
        *q = dato;
    } else {
        // Se inserta en medio
        dato->sig = aux->sig;
        dato->ant = aux;
        aux->sig->ant = dato;
        aux->sig = dato;
    }
}

void modificaElemento(nodoD **p, nodoD **q, int boleta, char nombre[30], char apellidos[30]){
    if(esVacia(*p)){
        puts("La lista esta vacia");
        return;
    }
    else{
        nodoD *modificar = buscarElemento(*p, boleta);//Trae el nodo directamente
        if (modificar == NULL) {//Por si no existe
            puts("Elemento no encontrado");
            return;

        }
        modificar->alumno = leerDatos(boleta, normMinus(nombre), normMinus(apellidos));
        moverOrdenado(p, q, modificar);//Lo mueve y ordena
    }
}
