#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void insertion(int*, int);
void imprimeArreglo(int*, int);
void llenaArreglo(int*, int, int, int);

int main(){
    srand(time(NULL)); //Se coloca la semilla a utilizar para rand
    int n, i;
    int *arr;
    puts("Introduce la cantidad de elementos: \n");
    scanf("%d", &n);
    arr = (int*) malloc(sizeof(int) * n); //Asignación de memoria para n enteros
    llenaArreglo(arr,n, 99, 1); //Llenado del arreglo con n elementos en un rango de [1,99]
    imprimeArreglo(arr, n);
    puts("----------");
    insertion(arr, n);
    imprimeArreglo(arr, n);

    (n%2==0) ? printf("La mediana es %.2f", (arr[(n/2)-1]+arr[n/2])/2.00): printf("La mediana es %d", arr[n/2]);
    //If taquigrafico de la forma ---  condicion ? acc si verdadero: acc si falso;

    return 0;
}

void insertion(int* arr, int n){
    int i,j, key;
    for(j=1;j<n;j++){
        key = arr[j];
        for(i = j-1;i>-1 && arr[i]>key; i--){
            arr[i+1] = arr[i];
        }
        arr[i+1] = key;
    }
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
