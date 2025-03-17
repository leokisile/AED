#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void intercambia(int*, int*);
void imprimeArreglo(int*, int);
void llenaArreglo(int*, int, int, int);
void selectionSort(int*, int);
int minimo(int*, int);

int main(){
    int nums[10];
    srand(time(NULL));
    llenaArreglo(nums,10, 99, 1);
    imprimeArreglo(nums, 10);
    selectionSort(nums, 10);
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

void selectionSort(int* arr, int n){
    int i, aux, m=0;
    for(i=0; i<n; i++){
        m = minimo(arr + i, n - i);
        printf("\n %d \n", m);
        if(m>-1){
            printf("\n %d %d\n",arr[i], arr[m + i]);
            intercambia(&arr[i], &arr[m+i]);
        }
        else break;
    imprimeArreglo(arr, 10);
    putchar('\n');
   }
}

int minimo(int* arr, int n){
    int min = 0, i, comp = -1;
    for(i=1;i<n;i++){
        if(arr[i]<arr[i-1])
            comp = 0;
        if(arr[i]<arr[min])
            min=i;
   }
   imprimeArreglo(arr, n);
    if(comp < 0)
        return -2;
    return min;
}
