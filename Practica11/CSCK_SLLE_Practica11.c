char minus(char c){if(c>='a' && c<='z') return c; return c-32;}
char mayus(char c){if(c>='A' && c<='Z') return c; return c+32;}

char* normMinus(char *cad){//Normaliza los nombres y apellidos
    int i;
    if(cad[0] != '\0'){
        cad[0] = mayus(cad[0]);
        for(i=1; cad[i] != '\0'; i++){
            if(cad[i] - 1 == ' '){
                cad[i] = mayus(cad[i]);
            }
            cad[i] = minus(cad[i]);
        }
    }

    return cad;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "alumno.h"
#include "nodoD.h"

int main(){
    nodoD *p=NULL, *q=NULL;
    int boleta, opc;
    char nombre[30], apellidos[30], c='y';

    do{
        printf("Elige una opcion\n1.-Alta de alumnos\n2.-Mostrar alumnos dados de alta\n3.-Modificar alumno\n4.-Salir\n");
        scanf("%d", &opc);
        switch(opc){
            case 1:
                puts("Inserte la boleta");
                scanf("%d", &boleta);
                puts("Inserte el/los nombre(s)");
                scanf(" %29[^\n]", &nombre);
                puts("Inserte el/los apellido(s)");
                scanf(" %29[^\n]", &apellidos);
                insertaOrdenado(&p, &q, boleta, nombre, apellidos);
                break;
            case 2:
                puts("Forma ascendente: ");
                ascendente(p);
                puts("Forma descendete: ");
                descendente(q);
                break;
            case 3:
                puts("Inserte la boleta a modificar");
                scanf("%d", &boleta);
                puts("Inserte el/los nombre(s)");
                scanf(" %29[^\n]", &nombre);
                puts("Inserte el/los apellido(s)");
                scanf(" %29[^\n]", &apellidos);
                modificaElemento(&p, &q, boleta, nombre, apellidos);
                break;
            case 4:
                puts("Hasta luego");
                return 0;
                break;
            default:
                puts("Opcion no encontrada");
                break;
        }
        puts("Quiere realizar otra accion? (y/n)");
        scanf(" %c", &c);
    }while(c == 'y');

    return 0;
}
