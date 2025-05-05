typedef struct alumno{
		int boleta;
		char nombre[100];
	}alumno;

//alumno[9]={ultimo, alum1, alum2,...,alumn}={2, al1, al2}
/*
Explicación del programa:

Se tendrán dos listas, la primera es a la que se le aplicarán todas las operaciones (alumnos)
La segunda lista solo contendrá índices ordenados por boleta

Ejemplo:
alumnos = {{1, Juan}, {20, Leo], {5, Arturo}}
indices = {0, 2, 1}

De esta forma se mantienen los datos "ordenados"
 */

//Busca la boleta mediante el arreglo ordenado de indices
int buscarAlumno(int* aux, int obj, int tam, alumno* alumnos){
	int i=1, j=aux[0], m;
	while(i<=j){
        m = (i + j)/2;
        if(alumnos[aux[m]].boleta == obj){
            return m;
        }
        else
            if(alumnos[aux[m]].boleta > obj)
                j = m-1;
            else
                i = m+1;
	}
	return -1;
}
int busquedaBin(int* aux, int obj, int tam, alumno* alumnos){
	int i=1, j=aux[0], m;
	while(i<=j){
        m = (i + j)/2;
        if(alumnos[aux[m]].boleta == obj){
            return m;
        }
        else
            if(alumnos[aux[m]].boleta > obj)
                j = m-1;
            else
                i = m+1;
	}
	return i;
}

void insertaAlumno(alumno* alumnos, alumno al, int pos, int tam, int* aux){
	int i, n;
	if(alumnos[0].boleta+1 <= tam)
	{
	    n = busquedaBin(aux, al.boleta, tam, alumnos);//posicion a insertar
	    if(alumnos[aux[n]].boleta == al.boleta){
            puts("Ya existe un alumno con esa boleta");
            return;
        }
	    printf("n:%d\n", n);
		if(pos > alumnos[0].boleta){
			alumnos[alumnos[0].boleta + 1]=al;//inserta al final
		}
		else{
			for(i=alumnos[0].boleta; pos<=i; i--){//hace el corrimiento e isnerta en la posicion adecuada
				alumnos[i+1] = alumnos[i];
			}
			alumnos[pos] = al;
		}
		for(i=1; i<=aux[0]; i++) //realiza el cambio (sumar 1) en el arreglo de index necesario
            if(aux[i]>=pos)
                aux[i]++;
		for (i = aux[0]; i >= n; i--) {//realiza el corrimiento del arreglo de index
            aux[i + 1] = aux[i];
        }
        aux[n] = (pos > alumnos[0].boleta) ? alumnos[0].boleta + 1 : pos;
		alumnos[0].boleta++;
		aux[0]++;
		puts("Alumno registrado");
	}
	else
		puts("No hay espacio para insertar el elemento");
}

void insertaAlFinal(alumno* alumnos, alumno al, int tam, int* aux){
	insertaAlumno(alumnos, al, alumnos[0].boleta + 1, tam, aux);
}

void borrarAlumno(alumno* alumnos, int boleta, int tam, int* aux){
    int m = buscarAlumno(aux, boleta, tam, alumnos);
    if(m==-1){
        puts("No se encontro al alumno");
        return;
    }
    printf("m:%d\n",m);
    int i;
    alumno borrado = alumnos[aux[m]];
    for(i=aux[m];i<alumnos[0].boleta;i++){
        alumnos[i]=alumnos[i+1];
    }
    for(i=m; i<alumnos[0].boleta; i++){
        aux[i]=aux[i+1];
    }
    int index = aux[m]
    for(i=1;i<alumnos[0].boleta; i++)
        if(aux[i] >= index)
            aux[i]--;
    alumnos[0].boleta--;
    aux[0]--;
    printf("Alumno borrado:\nBoleta:%d\tAlumno:%s\n", borrado.boleta, borrado.nombre);
}

void imprimeLista(alumno* alumnos, int tam, int* aux){
	int i;
	if(alumnos[0].boleta != 0)
        for(i=1; i <= alumnos[0].boleta; i++){
            printf("%d.- Boleta: %d \t Nombre: %s\tAux: %d\n", i, alumnos[i].boleta, alumnos[i].nombre, aux[i]);
            putchar('\n');
        }
    else
        puts("Lista vacia");
}
