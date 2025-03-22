#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct objeto{
    int numero;
    int peso;
    int valor;
}objeto;

void generarObjeto(objeto*, int, int);
void generarArrObjeto(objeto*, int, int);
void imprimeArrObjeto(objeto*, int);
void incrementar(int*, int);
void imprimeArreglo(int*, int);
void generaOpciones(objeto**, objeto*, int, int, int, int*);
void imprimeMatObjeto(objeto**, int, int);

int main(){
    srand(time(NULL));
    objeto *lista, **opciones;
    int n, ptotal, *contador, i;

    puts("Introduzca el peso maximo de la mochila: ");
    scanf("%d", &ptotal);
    puts("Introduzca el numero de objetos: ");
    scanf("%d", &n);
    lista = (objeto *)malloc(sizeof(objeto)*n);//Generar elementos de forma aleatoria y dinamica
    contador = (int *)calloc(n, sizeof(int));//Contador se usa como un contador binario para la permutacion
    generarArrObjeto(lista, n, ptotal);
    imprimeArrObjeto(lista, n);

    int total = 1<<n;//Recorre n bits a la izquierda el 1, calculando las potencias de 2**n
    //Generar matriz de forma dinamica
    opciones = (objeto **)malloc(total * sizeof(objeto*));
    for(i = 0; i < total; i++)
        opciones[i] = (objeto *)malloc(n * sizeof(objeto));
    //Genera las combinaciones y las imprime
    generaOpciones(opciones,lista,n,total,ptotal,contador);
    imprimeMatObjeto(opciones, n, total);

/*
Este fragmento de codigo imprime un contador binario que se usa para generar las posibles combinaciones
de objetos

    int i;
    for(i = 0; i < total; i++){
        imprimeArreglo(contador, n);
        incrementar(contador, n);
    }
*/

    return 0;
}

void generarObjeto(objeto *Obj, int ptotal, int num){
    Obj->numero = num + 1;
    Obj->peso = rand() % (ptotal/2+1) + (ptotal/5);
    Obj->valor = rand()%(15)+1;
}
void generarArrObjeto(objeto *lista, int n, int ptotal){
    int i;
    for(i=0; i < n; i++){
        generarObjeto(&lista[i], ptotal, i);
    }
}
void imprimeArrObjeto(objeto *lista, int n){
    int i;
    for(i=0; i < n; i++){
        printf("Objeto %d\t Peso: %d\t Valor: %d\n", lista[i].numero, lista[i].peso, lista[i].valor);
    }
}

void incrementar(int *contador, int n){//Incrementa en 1 el contador binario
    int i, carry = 1;
    for(i = 0; i < n; i++){
        contador[i]+=carry;
        if(contador[i] == 2){
            contador[i] = 0;
            carry = 1;
        }
        else{
            carry = 0;
            break;
        }
    }
}

void imprimeArreglo(int *contador, int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d", contador[i]);
    }
    putchar('\n');
}

void generaOpciones(objeto **opciones, objeto *lista, int n, int numOpc, int ptotal, int *contador){
    int i, j, pesoAct=0, valorAct=0, valorAnt=0, mejor;
    objeto vacio;//Declaracion de un objeto vacio
    vacio.numero=0;
    vacio.peso=0;
    vacio.valor=0;
    for(i=0; i < numOpc; i++){
        for(j=0; j<n; j++){
            if(contador[j]){//Pregunta si hay un 1 en el arreglo contador (permutacion)
                if((pesoAct + lista[j].peso)<=ptotal){//Si no sobrepasa el peso se agrega el objeto
                    opciones[i][j]=lista[j];
                    pesoAct += lista[j].peso;
                    valorAct += lista[j].valor;
                }
                else//Si lo sobrepasa pone el objeto vacio
                    opciones[i][j]=vacio;
            }else{//Si no le corresponde la permutacion agrega el objeto vacio en su lugar
                opciones[i][j]=vacio;
            }
        }
        if(valorAct > valorAnt){//Compara si la permutacion tiene un valor mas alto que la anterior
            mejor = i;//Guarda la iteracion con el valor mas alto
            valorAnt = valorAct;
        }
        valorAct = 0;
        pesoAct = 0;//reinicia los valores de peso y valor
        incrementar(contador, n);//Incrementa en 1 el contador
    }
    printf("La mejor opcion es la combinacion: %d\n", mejor);
}

void imprimeMatObjeto(objeto **opciones, int n, int total){
    int i, j;
    for(i=0; i< total; i++){
        printf("%d.- ", i);
        for(j=0; j<n; j++){
            if(opciones[i][j].numero != 0)//Omite los objetos "vacios" en la impresion
                printf("Obj %d|| ", opciones[i][j].numero);
        }
        putchar('\n');
    }
}
