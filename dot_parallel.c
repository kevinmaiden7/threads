#include "fileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <pthread.h>
// Macros
#define MAX_LENGTH 64

// Prototipos
void terminarPrograma();
void *productoPunto(void *args);

// Variables globales
char mensajeFinalizacion[MAX_LENGTH];
char file1[MAX_LENGTH] = "./benchmark/", file2[MAX_LENGTH] = "./benchmark/";
int numVariables, *vector1, *vector2, numHilos;
int dot_product = 0;

// Función main
int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		strcpy(mensajeFinalizacion, "Argumentos de entrada no validos");
		strcat(mensajeFinalizacion, "\nFormato permitido: ./sequential.out <numHilos> <numVariables> <file1> <file2>");
		terminarPrograma();
	}

	int hilo;
	pthread_t *hilo_handler;

	numHilos = atoi(argv[1]);
	numVariables = atoi(argv[2]);
	strcat(file1, argv[3]);
	strcat(file2, argv[4]);
	vector1 = getVector(file1, numVariables);
	vector2 = getVector(file2, numVariables);

	hilo_handler = malloc(numHilos * sizeof(pthread_t));

	if (vector1 == 0 || vector2 == 0)
	{
		strcpy(mensajeFinalizacion, "No se pudieron cargar correctamente los vectores");
		terminarPrograma();
	}
	printf("Se cargaron correctamente los vectores\n");

	struct timeval start, end;
	gettimeofday(&start, NULL);

	// Calcular el producto punto
	for (hilo = 0; hilo < numHilos; hilo++)
		pthread_create(&hilo_handler[hilo], NULL, productoPunto, (void *)hilo);

	for (hilo = 0; hilo < numHilos; hilo++)
		pthread_join(hilo_handler[hilo], NULL);

	printf("Resultado %d\n", dot_product);

	gettimeofday(&end, NULL);
	long seconds = (end.tv_sec - start.tv_sec);
	long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tiempo ejecutandose %ld\n", micros);
	
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
 * In arg:         vectores 
 * Global in vars: numVariables
 * Global out var: dot_product
 */
void *productoPunto(void *args)
{
	int hilo = (int) args;
	int i, product;
	for (i = 0; i <= numVariables - 1; i++)
	{
		product = vector1[i] * vector2[i];
		dot_product = dot_product + product;
		printf("Hilo %d --> suma %d  \n", hilo, product);
	}

	return NULL;
}
