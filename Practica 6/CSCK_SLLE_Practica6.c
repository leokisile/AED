#include <stdio.h>
#include "lista.h"

int main(){
    char c='n';
    int opc, opc2,pos,boleta, aux[9], tam=8;
    alumno alumnos[9];
    alumno al;
    alumnos[0].boleta = 0;
    aux[0] = 0;
    printf("%d %d\n", alumnos[0].boleta, aux[0]);
    do{
        printf("Elija una opcion:\n1.-Dar de alta a un alumno\n2.-Buscar a un alumno\n3.-Borrar un alumno\n4.-Imprimir lista\n");
        fflush(stdin);
        scanf("%d", &opc);
        switch(opc){
            case 1:
                printf("1.-Al final\n2.-Posicion especifica\n");
                scanf("%d", &opc2);
                puts("Escribe la boleta del alumno");
                scanf("%d",&al.boleta);
                puts("Escribe el nombre del alumno");
                fflush(stdin);
                scanf("%s", &al.nombre);
                if(opc2 ==  1){
                    insertaAlFinal(alumnos, al, tam, aux);
                }else{
                    puts("Escriba la posicion en la que lo quiere insertar");
                    fflush(stdin);
                    scanf("%d", &pos);
                    insertaAlumno(alumnos, al, pos, tam, aux);
                }
                break;
            case 2:
                puts("Escriba la boleta a buscar");
                fflush(stdin);
                scanf("%d", &boleta);
                pos = buscarAlumno(aux, boleta, tam, alumnos);
                (pos == -1)?puts("No se encontro el alumno"):printf("%d.- Boleta: %d \tNombre: %s \tPosicion: %d",pos, alumnos[aux[pos]].boleta, alumnos[aux[pos]].nombre, aux[pos]);
                break;
            case 3:
                puts("Escriba la boleta a eliminar");
                fflush(stdin);
                scanf("%d", &boleta);
                borrarAlumno(alumnos, boleta, tam, aux);
                break;
            case 4:
                imprimeLista(alumnos, tam, aux);
                break;
        }
        fflush(stdin);
        puts("Desea realizar otra accion (y/n)");
        scanf("%c", &c);
    }while(c=='y');
    return 0;
}
