#include <stdio.h>
#include <stdlib.h>

void imprimeMatriz(int, int, int**);
void imprimeLabe(int, int, int**);
void leeLaberinto(int**, FILE*, int, int);
void saltarSaltosDeLinea(FILE *);
void recorreLaberinto(int **, int , int , int*, int*);

int main(){
    FILE *labe;
    int fil, col, i, num;
    int inicio[2], fin[2];
    int **laberinto;

    puts("Teclee un numero del 1 al 3");
    scanf("%d", &num);
    if(num == 1)
        labe = fopen("Laberinto1.txt", "r");
    else if(num == 2)
        labe = fopen("Laberinto2.txt", "r");
    else if(num == 3)
        labe = fopen("Laberinto3.txt", "r");

    fscanf(labe," %d %d %d %d %d %d", &fil, &col, &inicio[0],&inicio[1],&fin[0],&fin[1]);
    printf("El laberinto tiene %d filas y %d columnas\nInicia en (%d,%d)\nTermina en (%d,%d)\n", fil, col, inicio[0],inicio[1], fin[0], fin[1]);

    //Inicialización de la matriz con 0s
    laberinto = (int **)malloc(fil * sizeof(int*));
    for(i=0; i<fil; i++){
        laberinto[i] = (int*)calloc(col, sizeof(int));
    }

    //Lectura del laberinto en una matriz
    saltarSaltosDeLinea(labe);
    leeLaberinto(laberinto,labe, fil, col);
    putchar('\n');
    imprimeMatriz(fil, col, laberinto);

    //Recorre el laberinto e imprime la respuesta
    recorreLaberinto(laberinto, fil, col, inicio, fin);
    imprimeMatriz(fil, col, laberinto);
    imprimeLabe(fil, col, laberinto);

    return 0;
}

void imprimeMatriz(int fila, int col, int **mat){
    int i, j;
    for(i=0; i<fila; i++){
        for(j=0; j<col; j++)
            printf("%d", mat[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

void leeLaberinto(int** mat, FILE* laberinto, int fil, int col){
    int i = 0, j = 0;
    char c;

    while ((c = fgetc(laberinto)) != EOF) {
        printf("%c", c);

        if (c == '\n') {
            i++;
            j = 0; // Reinicia columnas al cambiar de fila
        } else if (i < fil && j < col) {
            if (c == '#') {//Utiliza los # como paredes (1) y el resto como 0
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
            j++;
        }
    }
    putchar('\n');
}
void saltarSaltosDeLinea(FILE *laberinto) {//Funcion para quitar saltos que existan antes del laberinto
    char c;
    // Lee el caracter mientras sean saltos de lineas
    while ((c = fgetc(laberinto)) == '\n');
    // Regresar un carácter atrás si no fue un salto de línea
    if (c != EOF) {
        ungetc(c, laberinto);
    }
}

void recorreLaberinto(int **mat, int fil, int col, int punto[2], int salida[2]) {
    // Si el punto no existe en el laberinto se acaba
    if (punto[0] < 0 || punto[0] >= fil || punto[1] < 0 || punto[1] >= col) return;

    // Si es una pared o ya visitado se acaba
    if (mat[punto[0]][punto[1]] == 1 || mat[punto[0]][punto[1]] == 2) return;

    // Marcar la celda como parte del camino
    mat[punto[0]][punto[1]] = 2;

    // Si es la salida acaba
    if (punto[0] == salida[0] && punto[1] == salida[1]) {
        puts("¡Completaste el laberinto!");
        return;
    }

    // Define los movimientos (arriba, abajo, izquierda, derecha)
    int movimientos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int exito = 0; // Indica si encontramos un camino válido

    for (int i = 0; i < 4; i++) {
        int nuevaX = punto[0] + movimientos[i][0];
        int nuevaY = punto[1] + movimientos[i][1];

        if (nuevaX >= 0 && nuevaX < fil && nuevaY >= 0 && nuevaY < col && mat[nuevaX][nuevaY] == 0) {
            recorreLaberinto(mat, fil, col, (int[2]){nuevaX, nuevaY}, salida);
            //Espera a la resolución de la llamada recursiva para determinar un valor en las coordenadas
            //Nuevax, NuevaY. En caso de ser un camino válido (2) sigue por esa ruta
            if (mat[nuevaX][nuevaY] == 2) exito = 1;  // Si encuentra la salida lo marca como exito
        }
    }

    // Si no hay salida desde aquí, marcarlo como camino muerto
    //Espera la llamada de la función recursiva, haciendo que se llene de 3 desde la pared hasta la casilla actual
    if (!exito) {
        mat[punto[0]][punto[1]] = 3;
    }
}
void imprimeLabe(int fila, int col, int **mat){
    int i, j;
    for(i=0; i<fila; i++){
        for(j=0; j<col; j++){
            if(mat[i][j] == 1)
                putchar('#');
            else if(mat[i][j] == 3)
                putchar(' ');
            else if(mat[i][j] == 2)
                putchar('*');
        }
        putchar('\n');
    }
    putchar('\n');
}



