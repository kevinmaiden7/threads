#include "fileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Macros
#define MAX_LENGTH 64

// Prototipos
void terminarPrograma();
int productoPunto(int vector1[], int vector2[]);

// Variables globales
char mensajeFinalizacion[MAX_LENGTH];
char file1[MAX_LENGTH] = "./benchmark/", file2[MAX_LENGTH] = "./benchmark/";
int numVariables, *vector1, *vector2;
struct timeval start, end;

	// Función main
int main(int argc, char *argv[]){
	if (argc != 4){
		strcpy(mensajeFinalizacion, "Argumentos de entrada no validos");
		strcat(mensajeFinalizacion, "\nFormato permitido: ./sequential.out <numVariables> <file1> <file2>");
		terminarPrograma();
	}
	numVariables = atoi(argv[1]);
	strcat(file1, argv[2]);
	strcat(file2, argv[3]);
	vector1 = getVector(file1, numVariables);
	vector2 = getVector(file2, numVariables);
	if (vector1 == 0 || vector2 == 0){
		strcpy(mensajeFinalizacion, "No se pudieron cargar correctamente los vectores");
		terminarPrograma();
	}
	printf("Se cargaron correctamente los vectores\n");
	gettimeofday(&start, NULL); // Iniciando toma de tiempo
	int dot_product = productoPunto(vector1,vector2);
	gettimeofday(&end, NULL); // Finalizando toma de tiempo
	double time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
	printf("Dot product result = %d\n", dot_product);
 	printf("time elapsed (milliseconds): %.2lf\n", time);
	return (0);
}

void terminarPrograma()
{
	printf("%s\n", mensajeFinalizacion);
	printf("Fin del programa\n");
	exit(0);
}

/*
 * Function:       productoPunto
 * Purpose:        Realizar producto punto entre dos vectores
 * In arg:         Vectores 
 * Global in vars: numVariables
 * Global out var: dot_product
 */
int productoPunto(int vector1[], int vector2[]){
	int i, product;
	int dot_product = 0;
	for (i = 0; i < numVariables; i++){
		product = vector1[i] * vector2[i];
		dot_product = dot_product + product;
	}
	return(dot_product);
}
