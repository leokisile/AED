#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilas.h"

char* fragmento(char *inicio, char *temp) {
    strncpy(temp, inicio, 3);
    temp[3] = '\0';
    return temp;
}
int esBalanceada(char ch, nodo **p){
    char abierto = saca(p);
    if(ch-abierto!=2 && ch-abierto!=1){//La diferencia entre () en ASCII es 1, mientras que [] y {} es 2
        return 0;
    }
    return 1;
}


int main(){
    nodo *p = NULL;
    char c = 'y', x;
    char exp[100], temp[4];
    int i, validado=0;
    do{
        puts("Inserte una expresion matematica como (c*2x){2[(x-y)-4(z+a)]}");
        fgets(exp, sizeof(exp), stdin);
        for(i=0;exp[i]!='\0';i++){
            if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
                mete(exp[i],&p);
            else if(exp[i] == ')' || exp[i] == ']' || exp[i] == '}'){
                if(!esBalanceada(exp[i],&p)){
                    printf("La expresion no esta correctamente balanceada, error en el fragmento %s\n", fragmento(exp+i-1,temp));
                    validado = 1;
                    break;
                }
            }
        }
        if(validado == 0){
            if(!vacia(p))
                puts("La expresion no esta correctamente balanceada (no se cerro alguno de los simbolos)");
            else
                puts("La expresion esta correctamente balanceada");
        }

        anula(&p);
        puts("Quiere ingresar otra expresion?(y/n)");
        scanf(" %c", &c);
    }while(c == 'y');
    return 0;
}
