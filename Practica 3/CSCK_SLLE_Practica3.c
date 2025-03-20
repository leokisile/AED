#include <stdio.h>
#include <string.h>
long indice[27] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, -1, -1};//Tabla donde se guardan los indices

void construirIndice(char *);
int compTabla(char *);
void imprimeIndice();
void imprimeTabla(char *);
int buscar(char*, char*);

int main(){
    char valor[10];
    long resultado;
    construirIndice("SALIDA.txt");//Construye tabla indexada
    puts("Introduce la clave a buscar");
    scanf("%s", valor);
    resultado = buscar("SALIDA.txt", valor);
    resultado ? printf("La clave esta en la linea %d\n", resultado): puts("Clave no encontrada");
    //imprimeIndice();
    //imprimeTabla("SALIDA.txt");
    return 0;
}

void construirIndice(char *narchivo){
    int o = compTabla(narchivo);
    printf("%d \n\n", o);
    if(o){
        puts("Tabla ya existente leida correctamente");
        return;
    }
    FILE *archivo = fopen(narchivo, "r");//Abrimos el archivo
    FILE *ctabla = fopen("TABLA.txt", "w");//Creamos el archivo del index
    if(!archivo || !ctabla){
        puts("No se pudo abrir el archivo de claves");//Mensaje de error
        return;
    }
    char linea[10];//Damos un arreglo para leer las claves
    long posicion = ftell(archivo);//Posicion actual del archivo en bytes

    while(fgets(linea, sizeof(linea), archivo)){//Mientras haya una "cadena" en el texto
        char letra = linea[0];//Recupera el primer caracater (la letra)
        int idx = letra -'A';//Calcula el index de la tabla restando A a la letra

        if(indice[idx] == -1){
            indice[idx] = posicion;//Comprueba si ya hay un indice para esa letra, de lo contrario se lo asigna
        }
        posicion = ftell(archivo);//Actualiza la posicion del archivo
    }
        // Escribir tabla de índices
    indice[26] = ftell(archivo);
    for (int i = 0; i < 27; i++) {
        fprintf(ctabla, "%c\n%ld\n", 'A' + i, indice[i]);
    }
    fclose(ctabla);
    fclose(archivo);

}

int compTabla(char *narchivo){
    FILE *archivo = fopen(narchivo, "r");
    if(!archivo){
        puts("Error al abrir el archivo");
        return 0;
    }
    // Obtener tamaño real del archivo
    fseek(archivo, 0, SEEK_END);
    long tamanoReal = ftell(archivo);
    fclose(archivo);

    FILE *tabla = fopen("TABLA.txt", "r");
    char letraTabla;
    long posTabla;
    if(tabla){
        while(fscanf(tabla, " %c %ld", &letraTabla, &posTabla) == 2){
            printf("%c\t%ld\n", letraTabla, posTabla);
            if(indice[letraTabla - 'A'] == -1)
                indice[letraTabla - 'A'] = posTabla;
        }
    }else{
        puts("No hay tabla de index, se generara una nueva");
        return 0;
    }
    fclose(tabla);
    posTabla = indice[26];
    printf("%ld\t%ld\n", posTabla, tamanoReal);
    if(tamanoReal == posTabla){
        puts("La tabla es valida");
        return 1;
    }
    puts("La tabla no es valida");
    return 0;
}

//Los de impresion solo fueron para probar que si se genere la tabla
void imprimeIndice(){
    int i;
    for (i = 0; i < 27; i++) {
        if (indice[i] != -1) {
            printf("Letra %c inicia en posición %ld\n", 'A' + i, indice[i]);
        }
    }

}

void imprimeTabla(char *narchivo){
    int i;
    char linea[10];
    FILE *archivo = fopen(narchivo, "r");
    for (i = 0; i < 27; i++) {
        if (indice[i] != -1) {
            fseek(archivo, indice[i], SEEK_SET);
            fgets(linea, sizeof(linea), archivo);
            printf("Letra %c inicia en %s\n", 'A' + i, linea);
        }
    }
    fclose(archivo);

}
int buscar(char *narchivo, char *clave){
    long ini, fin, medio, i, j , k; // Varaibles ini, fin y medio son para bytes; i, j y k para lineas, asi se evitan errores
    int encontrado = 1;//Bandera para terminar el bucle
    char let = clave[0];//Se extrae la letra de la clave
    char linea[10];//Guarda la linea que lee el archivo
    if((let > 'Z' && let < 'A') || (strlen(clave))!=6) //Verifica que la clave sea valida
        puts("Clave no valida");
    else{
        FILE *archivo = fopen(narchivo, "r");

        //Posiciones de inicio y fin de busqueda extraidas de la tabla indexada
        ini = indice[let-'A'];
        fin = indice[let-'A'+1];

        //Se convierten a lineas, cada linea tiene 8 caracteres A00001\r\n
        i = ini /8;
        j = fin /8;


        while(i <= j){
            k =(i+j)/2;//Calculo de la linea de en medio
            medio = k * 8;//Convierte la linea de en medio en la direccion de bytes
            printf("%d %d %d\n", i, j, k);//Imprime valores para comprobar
            fseek(archivo, medio, SEEK_SET);//Posiciona el puntero en el valor de en medio
            fgets(linea, sizeof(linea), archivo);//Lee la linea
            encontrado = strcmp(strtok(linea, "\r\n"), clave);//Compara la linea con el valor a buscar
            if(!encontrado){//Si la encuentra termina el bucle
                fclose(archivo);
                return k+1;//Devuelve k+1 porque el archivo inicia en el byte 0 y eso lo interpreta como linea 0
            }
            else if(encontrado > 0)//Si la linea es mayor al valor buscado reduce el rango de busqueda a la mitad izquierda
                j = k - 1;
            else
                i = k + 1;//En caso contrario lo reduce a la mitad derecha
        }
        return 0;//Si se acaba el bucle no esta la clave
    }
}
