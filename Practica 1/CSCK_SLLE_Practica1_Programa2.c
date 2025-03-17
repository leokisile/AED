#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion(char**, int);
int EsMayor(char*, char*);
char Amin(char);
void imprimeArreglo(char**, int);

int main ()
{
    char *cadenas[50]={
         "Banco",
         "Manta",
         "Cura",
         "Impresion",
         "Agrupacion",
         "Peces",
         "Empresa",
         "Clientes",
         "Estructura",
         "Sentarse",
         "Animal",
         "Norte",
         "Joven",
         "Dinero",
         "Perro",
         "Casa",
         "Camion",
         "Dedo",
         "Danza",
         "Tela",
         "Calor",
         "Conservar",
         "Terciopelo",
         "Invierno",
         "Remedio",
         "Enfermedad",
         "Mal",
         "Persona",
         "Evento",
         "Idea",
         "Vendedor",
         "Dibujo",
         "Diseño",
         "Idea",
         "Tinta",
         "Efecto",
         "Consecuencia",
         "Consejos",
         "Parabola",
         "Movimiento",
         "Impredecible",
         "Esferico",
         "Nubes",
         "Seco",
         "Aire",
         "Nariz",
         "Irrita",
         "Antipatica",
         "Agradable",
         "Delgado"
         };

        int n = 50;

        imprimeArreglo(cadenas, n);
        insertion(cadenas, n);
        imprimeArreglo(cadenas, n);

    return 0;
}

void insertion(char** arr, int n){
    int i,j;
    char* key; //Se usa char* para recuperar la referencia de cada string
    for(j=1;j<n;j++){
        key = arr[j]; //Se realiza el cambio en la direccion de memoria donde se alamacenan los strings
        for(i = j-1;i>-1 && EsMayor(arr[i],key); i--){
            arr[i + 1] = arr[i];
        }
        arr[i + 1] = key;
    }
}

int EsMayor(char* pal1, char* pal2){
    int i;

    for (i = 0; pal1[i] != '\0' && pal2[i] != '\0'; i++) {
        char c1 = Amin(pal1[i]); //Guardamos temporalmente el caracter convertido a minuscula de cada arreglo
        char c2 = Amin(pal2[i]);

        if (c1 > c2) return 1; //Comparamos si c1 es estrictamente mayor o menor que c2
        if (c1 < c2) return 0;
    }
    return strlen(pal1) > strlen(pal2); //En caso de ser iguales, se usa la longitud de cadena como "desempate"
}

char Amin(char c){ //Devuelve el caracter convertido en minuscula
    if(c>= 'A' && c<= 'Z')
        return c+32;
    else
        return c;
}

void imprimeArreglo(char** arr, int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s ", arr[i]);
    }
    putchar('\n');
}
