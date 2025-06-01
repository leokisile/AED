#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colas.h"
#include "pilas2.h"

void leeNum(char* num, nodo **p){
    int i;
    for(i=strlen(num); i>=0; i--){
        pone_en_cola(p, num[i]-'0');
    }
}

void colocaResultado(char* res, nodo **p){
    int i =0;
    while(!vacia(*p)){
        res[i++] = saca2(p) + '0';
    }
    res[i] = '\0';
}

int main(){
    nodo *primero = NULL, *segundo = NULL, *acarreo = NULL, *resultado = NULL;
    char num1[100], num2[100], numres[100], c;
    int n1=0, n2=0, ac=0, res=0;
    do{
        //Introduce los datos
        puts("Ingresa el primer numero");
        scanf(" %s", &num1);
        puts("Ingresa el segundo numero");
        scanf(" %s", &num2);

        //Lee numeros
        leeNum(num1, &primero);
        leeNum(num2, &segundo);

        //Suma numeros si primero o segundo tienen numeros en la cola
        while(!vacia(primero) || !vacia(segundo) || !vacia(acarreo)){
            ac=quita_de_cola(&acarreo);//Como quita devuelve 0 si no hay nada se puede sumar el acarreo directamente
            n1 = quita_de_cola(&primero);
            n2 = quita_de_cola(&segundo);
            //Realiza la suma. si es 10 o mas divide en unidades (las mete a una pila) y decenas (se mete al acarreo)
            res = n1 + n2 + ac;
            if(res>9){
                mete2(res%10, &resultado);
                pone_en_cola(&acarreo, res/10);
            }else mete2(res, &resultado);
        }

        //Transcribe la pila de resultado en una cadena y la imprime
        colocaResultado(numres, &resultado);
        printf("El resultado es: %s \n", numres);

        //Vacia las colas y la pila
        anula(&primero);
        anula(&segundo);
        anula(&acarreo);
        anula2(&resultado);
        puts("Quieres realizar otra operacion? (y/n)");
        scanf(" %c", &c);
    }while(c == 'y');

    return 0;
}
