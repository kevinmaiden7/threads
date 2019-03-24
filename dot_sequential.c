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

	// Función main
int main(int argc, char *argv[]){
	if(argc != 4){
		strcpy(mensajeFinalizacion, "Argumentos de entrada no validos");
		strcat(mensajeFinalizacion, "\nFormato permitido: ./sequential.out numVariables file1 file2");
		terminarPrograma();
	}
	numVariables = atoi(argv[1]);
	strcat(file1, argv[2]);
	strcat(file2, argv[3]);
	vector1 = getVector(file1, numVariables);
	vector2 = getVector(file2, numVariables);
	if(vector1 == 0 || vector2 == 0){
		strcpy(mensajeFinalizacion, "No se pudieron cargar correctamente los vectores");
		terminarPrograma();
	}
	printf("Se cargaron correctamente los vectores\n");
	// Calcular el producto punto

	return(0);
}

void terminarPrograma(){
	printf("%s\n", mensajeFinalizacion);
	printf("Fin del programa\n");
	exit(0);
}

int productoPunto(int vector1[], int vector2[]){
	//
	return(0);
}
