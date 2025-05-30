#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pilas.h"
#include "pilas2.h"

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
char correspondiente(char c) {
    if (c == ')') return '(';
    if (c == ']') return '[';
    if (c == '}') return '{';
    return '\0';
}

int esOperador(char c, char operadores[4][3]){
    int i,j, n=0;
    for(i=0; i<5; i++)
        for(j=0; j<3; j++)
            if(c == operadores[i][j])
                return i+1;
    return 0;
}

void insertaElemento(char c, char* sal){
    int len = 0;
    len = strlen(sal);
    sal[len] = c;
    sal[len+1] = '\0';
}

void postfija(nodo** p, char* cad, char* sal, char operadores[4][3]){
    int i, len=0;
    char c, actual;
    for(i=0; cad[i]!='\0'; i++){
        actual = cad[i];

        if((actual >= 'a' && actual <= 'z') || (actual >= 'A' && actual <= 'Z') || (actual >= '0' && actual <= '9')){//Verifica que sea letra o numero
            insertaElemento(actual, sal);
        }

        else if(actual == '(' || actual == '[' || actual == '{'){//Mete parentesis, llaves y corchetes
            mete(actual, p);
        }

        else if(actual == ')' || actual == ']' || actual == '}'){//Itera hasta encontrar el abierto
            char abierto = correspondiente(actual);
            while(!vacia(*p) && tope(*p) != abierto){
                insertaElemento(saca(p), sal);
            }
             saca(p); // Saca el paréntesis abierto correspondiente
        }

        else if(esOperador(actual, operadores)){//Verifica los operadores
            while(!vacia(*p) && esOperador(tope(*p), operadores) != 0 && esOperador(tope(*p), operadores) <= esOperador(actual, operadores)){
                insertaElemento(saca(p), sal);
            }
            mete(actual, p);
        }
    }
    while (!vacia(*p)) {//Mete los elementos restantes en caso de que haya
        insertaElemento(saca(p), sal);
    }
}

int evaluar(nodo2 **p, char* cad, char operadores[4][3]){
    char actual;
    int i;
    for(i=0; (actual=cad[i])!='\0';i++){
        if((actual >= '0' && actual <= '9')){//Verifica que sea numero
            mete2(actual-'0', p);
        }
        else{
            if(vacia2(*p) || (*p)->sig == NULL){
                puts("No hay suficientes operandos");
                break;
            }
            else{
                int op2 = saca2(p);
                int op1 = saca2(p);
                int r = 0;
                switch(actual){
                    case '+':r= op1 + op2;
                    break;
                    case '-':r= op1 - op2;
                    break;
                    case '*':r= op1 * op2;
                    break;
                    case '/':r= op1 / op2;
                    break;
                    case '%':r= op1 % op2;
                    break;
                    case '^':r= (int)pow(op1, op2);
                    break;
                    default: puts("Operador desconocido");
                }
                mete2(r,p);
            }
        }
    }
    if(vacia2(*p)) {
        puts("Error: no queda resultado");
        return -1;
    }
    return saca2(p);  // resultado final
}

int main(){
    char operadores[4][3] = {
    {'^', ' ', ' '},
    {'*', '/', '%'},
    {'+', '-', ' '},
    {'=', ' ', ' '}
    };
    nodo *p = NULL;
    nodo2 *eval = NULL;
    char c = 'y', x;
    char exp[100], temp[4], sal[100];
    int i, validado=0, res=0;
    do{
        sal[0]='\0';
        puts("Inserte una expresion matematica como (c*2x){2[(x-y)-4(z+a)]}");
        fgets(exp, sizeof(exp), stdin);

        //Verifica si la funcion esta balanceada correctamente
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
            if(!vacia(p)){
                puts("La expresion no esta correctamente balanceada (no se cerro alguno de los simbolos)");
            }
            else
                puts("La expresion esta correctamente balanceada");
        }
        anula(&p);//Anula P para pasar a la conversion a postfija

        postfija(&p,exp,sal,operadores);
        printf("%s\n", sal);
        res = evaluar(&eval, sal, operadores);
        printf("El resultado es: %d\n", res);

        puts("Quiere ingresar otra expresion?(y/n)");
        scanf(" %c", &c);
        getchar();
    }while(c == 'y');
    return 0;
}
