typedef struct Alumno{
    int boleta;
    char nombre[30];
    char apellidos[30];
}Alumno;

Alumno leerDatos(int boleta, char *nombre, char *apellidos){
    Alumno nuevo;
    nuevo.boleta = boleta;
    strcpy(nuevo.nombre, nombre);
    strcpy(nuevo.apellidos, apellidos);
    return nuevo;
}
