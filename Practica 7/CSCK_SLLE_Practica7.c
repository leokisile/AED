#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "listas.h"

int main(){
    int numero, opc, opc2;
    char c;
    nodo *p = NULL;
    nodo *ord=NULL;
    puts("Introduzca numeros enteros, teclee 0 para terminar");
    while(1){
        scanf(" %d", &numero);
        if(numero == 0){
            break;
        }
        agregarElemento(&p, numero);
    }
    puts("Se ha terminado de introducri los datos");
    do{
        printf("Elija una opcion\n1.-Copiar y ordenar la lista\n2.-Invierte los elementos\n3.-Elimina duplicados\n4.-Total de valores\n5.-Media\n6.-Mediana\n7.-Moda\n8.-Varianza\n9.-Desviacion estandar\n10.-Imprimir lista\n");
        fflush(stdin);
        scanf("%d",&opc);
        switch(opc){
            case 1:
                ordenar(p,&ord);
                puts("Lista copiada y ordenada");
                break;
            case 2:
                invertir(&p);
                puts("Lista invertida");
                break;
            case 3:
                eliminaDuplicados(&p);
                puts("Duplicados eliminados");
                break;
            case 4:
                printf("Hay %d numeros en total\n", total(p));
                break;
            case 5:
                printf("La media es: %.2f\n", media(p));
                break;
            case 6:
                printf("La mediana es: %.2f\n", mediana(p,&ord));
                break;
            case 7:
            	moda(p, &ord);
                break;
            case 8:
                printf("La varianza es: %.2f\n", varianza(p));
                break;
            case 9:
                printf("La desviacion estandar es: %0.2f\n", desviacion(p));
                break;
            case 10:
                puts("Quiere imprimir la lista normal(1) o la ordenada(2)?");
                scanf("%d", &opc2);
                if(opc2==1){
                    imprimeLista(p);
                }else if(opc2==2){
                    imprimeLista(ord);
                }else
                    puts("Opcion no encontrada");
                break;
            default:
                puts("Opcion no encontrada");
                break;
        }
        puts("Desea realizar otra accion? (y/n)");
        scanf(" %c", &c);
    }while(c == 'y');

    return 0;
}
