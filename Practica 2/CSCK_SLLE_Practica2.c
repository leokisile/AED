#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void insertionSort(int*, int);
void bubbleSort(int*, int);
void selectionSort(int*, int);
void mergeSort(int*, int, int);
void imprimeArreglo(int*, int);
void llenaArreglo(int*, int, int, int);
void intercambia(int*, int*);
int minimo(int*, int);
void merge(int*, int, int, int);

int main(){
    int opc, n;
    int* arr;

    srand(time(NULL));
    do{

        puts("Seleccione una opcion\n1.Insercion\n2.Burbuja\n3.Seleccion\n4.Mezcla\n5.Salir");
        scanf("%d", &opc);
        if(opc != 5){
            puts("Introduce la cantidad de elementos: \n");
            scanf("%d", &n);
            arr = (int*) malloc(sizeof(int) * n);
            llenaArreglo(arr,n, 99, 1);
            imprimeArreglo(arr, n);
            putchar('\n');
        }
        switch(opc){
            case 1: insertionSort(arr, n);
                    break;
            case 2: bubbleSort(arr, n);
                    break;
            case 3: selectionSort(arr, n);
                    break;
            case 4: mergeSort(arr, 0, n-1);
                    break;
            case 5: puts("Hasta luego :D");
                    break;
        }
        if(opc != 5){
            imprimeArreglo(arr, n);
        }
        free(arr);
    }while(opc != 5);
    return 0;
}

void imprimeArreglo(int* arr, int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

void llenaArreglo(int* arr, int n, int Max, int Min){
    int i;
    for(i=0;i<n;i++){
        arr[i] = rand() % (Max-Min+1) + Min;
    }
}

void intercambia(int* a, int* b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void insertionSort(int* arr, int n){
    int i,j, key;
    for(j=1;j<n;j++){
        key = arr[j];//Se toma un valor base
        for(i = j-1;i>-1 && arr[i]>key; i--){//Se compara el valor base con los otros
            arr[i+1] = arr[i];//Hace un corrimiento hacia la derecha de todos los elementos
        }
        arr[i+1] = key;//Coloca el valor base en su respectivo lugar
    }
}

void selectionSort(int* arr, int n){
    int i, m=0;//Se declara m=0 ya que se maneja con el index del arreglo
    for(i = 0; i<n; i++){
        m = minimo(arr+i, n-i);//Retorna -2 si ya esta ordenado, o el index del valor mas chico
        if(m > -1){
            intercambia(&arr[i], &arr[m+i]);//Se realiza el intercambio del minimo con la posicion de la iteracion
        }
        else
            break;//Si ya esta ordenado se sale del ciclo
    }
}

int minimo(int* arr, int n){
    int i, min = 0, comp = -1;//Se toma min como el index con el valor minimo, comp nos dice si ya esta ordenado

    for(i = 1; i<n; i++){
        if(arr[i] < arr[i-1]){
            comp = 0;//En caso de encontrar un elemento desordenado pone 0 (falso)
        }
        if(arr[i] < arr[min]){
            min=i;//Guarda el index con el valor minimo
        }
    }
    if(comp < 0)
            return -2;//Retorna -2 si ya se esta ordenado
    return min;//Retorna el index del valor minimo si no esta ordenado
}

void merge(int arr[], int l, int m, int r)//Variables l(left), m(middle) y r(right)
{
    int i, j, k;
    int n1 = m - l + 1;//Calculamos el punto medio para los subarreglos
    int n2 = r - m;

    int L[n1], R[n2];//Declaramos los subarreglos

    for (i = 0; i < n1; i++)//Llenamos los arreglos con sus respectivos datos
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;//Inicializamos los punteros para los subarreglos en 0
    j = 0;
    k = l;//Inicializamos k (puntero del arreglo original) en el valor de l (primer valor a ordenar)

    while (i < n1 && j < n2) {//Se realiza la comparacion de las pilas y se van colocando de menor a mayor
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    //Esta parte del codigo cambia, no hay valor centinela, en cambio,
    //se termina cuando una de las pilas se acaba y se llena con las cartas restantes de la otra pila
    //Es decir, si sobraron 2 numeros en R, se colocan al final de nuestro arreglo
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);//Llamadas recursivas
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void bubbleSort(int* arr, int n){
    int i=0, j, ord=0;
    while((i<n) && (!ord)){
        i++;
        ord = 1;
        for(j=0;j<n-i;j++){//Suben las burbujas (numeros) mas grandes (n-i), hay i burbujas ya ordenadas
            if(arr[j]>arr[j+1]){//Se comparan los elementos en pares adyacentes y va subiendo la mas grande
                intercambia(&arr[j], &arr[j+1]);
                ord = 0;//Se usa ord para verificar si ya esta ordenado el arreglo
            }
        }
    }
}
