#include "fileManager.h"

FILE *file;

/*
	Función que obtiene los valores de un vector a través de un archivo y los retorna
	como un arreglo de numeros enteros. Si el archivo no se puede abrir, la función retorna
	un 0 significando que ocurrió un error en la apertura.
*/
int * getVector(char *fileName, int numVariables){
	file = fopen(fileName, "r");
	if(file == NULL) return(0);
	int *vector, maxLongitud = 10;
	char linea[maxLongitud];
	vector = (int *)malloc(numVariables*sizeof(int));
	for(int i=0; fgets(linea, maxLongitud, file) != NULL; i++){
		vector[i] = atoi(linea);
	}
	fclose(file);
	return(vector);
}
