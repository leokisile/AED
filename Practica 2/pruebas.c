#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void intercambia(int*, int*);
void imprimeArreglo(int*, int);
void llenaArreglo(int*, int, int, int);
void merge(int*, int, int, int);
void mergeSort(int*, int, int);

int main(){
    int nums[10];
    srand(time(NULL));
    llenaArreglo(nums,10, 99, 1);
    imprimeArreglo(nums, 10);
    mergeSort(nums, 0, 9);
    imprimeArreglo(nums, 10);
    return 0;
}

void intercambia(int* a, int* b){
    int aux = *a;
    *a = *b;
    *b = aux;
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
