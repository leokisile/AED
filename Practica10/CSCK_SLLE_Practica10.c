#include <stdio.h>
#include <stdlib.h>
#include "colaPrio.h"

int main(){
    int tam, opc, num;
    int *p, *ord=NULL;
    char c = 'y';

    //Crea la cola con valores entre 1 y 99 (0 se considera valor nulo)
    puts("Introduce el numero de elementos a ingresar");
    scanf("%d", &tam);
    p = creaCola(tam);
    llenaCola(p, tam, 99, 1);
    imprimeCola(p, tam);

    //Crea el montículo con los valores "ordenados"
    build_max_heap(p, tam);
    imprimeCola(p, tam);

    while(c == 'y'){
        printf("Selecciona una opcion\n1.-Encolar un elemento\n2.-Desencolar un elemento\n3.-Desencolar todos los elementos\n4.-Imprimir elementos\n5.-Ordenar elementos\n");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                puts("Ingrese el elemento");
                scanf(" %d", &num);
                max_heap_insert(&p, &tam, num);
                break;
            case 2:
                num = heap_extract_max(&p, &tam);
                printf("Se ha desencolado el numero %d\n", num);
                break;
            case 3:
                free(p);
                p = NULL;
                puts("Se ha vaciado la cola");
                break;
            case 4:
                imprimeCola(p, tam);
                break;
            case 5:
                copiaCola(&ord, p, tam);
                heapSort(ord, tam);
                puts("Elementos ordenados");
                imprimeCola(ord, tam);
                break;
            default:
                puts("No se encontro la opcion");
                break;
        }
        puts("Quiere realizar otra accion?(y/n)");
        scanf(" %c", &c);
    }

    return 0;
}
