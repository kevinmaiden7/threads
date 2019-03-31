#include "fileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

// Macros
#define MAX_LENGTH 64

// Estructuras
struct rangoEjecucion{
	int inicio;
	int final;
};

typedef struct rangoEjecucion Rango;

// Prototipos
void terminarPrograma();
void calcularRangos(Rango *, int numVariables, int numHilos);
void* productoPunto(void* rank);

// Variables globales
char mensajeFinalizacion[MAX_LENGTH];
char file1[MAX_LENGTH] = "./benchmark/", file2[MAX_LENGTH] = "./benchmark/";
int numVariables, numHilos, *vector1, *vector2;
struct timeval start, end;

	// Función main
int main(int argc, char *argv[]){
	if (argc != 5){
		strcpy(mensajeFinalizacion, "Argumentos de entrada no validos");
		strcat(mensajeFinalizacion, "\nFormato permitido: ./parallel.out <numVariables> <file1> <file2> <numHilos>");
		terminarPrograma();
	}

	numVariables = atoi(argv[1]);
	numHilos = atoi(argv[4]);
	
	if((numVariables % numHilos) != 0){ // Validación de la división de tareas
		strcpy(mensajeFinalizacion, "El numero de iteraciones (variables) no se puede dividir de manera exacta por el numero de hilos");
		terminarPrograma();
	}
	strcat(file1, argv[2]);
	strcat(file2, argv[3]);
	vector1 = getVector(file1, numVariables);
	vector2 = getVector(file2, numVariables);
	if(vector1 == 0 || vector2 == 0){
		strcpy(mensajeFinalizacion, "No se pudieron cargar correctamente los vectores");
		terminarPrograma();
	}
	printf("Se cargaron correctamente los vectores\n");
	int hilo;
	pthread_t *hilo_handler;
	hilo_handler = malloc(numHilos * sizeof(pthread_t)); // Arreglo de hilos
	int *resultadosPorHilo = (int *)malloc(numHilos*sizeof(int));  // Arreglo de enteros para guardar los resultados parciales que calcula cada hilo
	Rango rangos[numHilos]; // Arreglo de variables tipo Rango(struct) para delimitar el rango de ejecucion de cada hilo
	calcularRangos(rangos, numVariables, numHilos);

	for(int i=0; i<numHilos; i++) // Mostrar en pantalla la división de tareas a través de los hilos
		printf("Hilo %d -> inicio: %d / final: %d\n", i, rangos[i].inicio, rangos[i].final);
		
	gettimeofday(&start, NULL); // Iniciando toma de tiempo

	for(hilo = 0; hilo < numHilos; hilo++) // Creación de hilos
		pthread_create(&hilo_handler[hilo], NULL, &productoPunto, &rangos[hilo]);

	for(hilo = 0; hilo < numHilos; hilo++) // Join de hilos
		pthread_join(hilo_handler[hilo], (void *)&resultadosPorHilo[hilo]);

	int dot_product = 0; // Unificando el resultado: Se suman los resultados parciales obtenidos por cada hilo
	for(int i=0; i < numHilos; i++)
		dot_product += resultadosPorHilo[i];

	gettimeofday(&end, NULL); // Finalizando toma de tiempo

	double time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
	printf("\nDot product result = %d\n", dot_product);
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
	Función que calcula, de acuerdo al numero de variables y al numero de hilos,
	cuantas operaciones deberá ejecutar cada hilo y su rango de ejecución sobre
	los vectores(posiciones inicial y final). 
*/
void calcularRangos(Rango *rangos, int numVariables, int numHilos){
	int operacionesPorHilo = numVariables / numHilos, contador = 0;
	for(int i=0; i<numHilos; i++){
		rangos[i].inicio = contador;
		rangos[i].final = contador + (operacionesPorHilo - 1);
		contador += operacionesPorHilo;
	}
}

/*
	Función de ejecución en paralelo para calcular parcialmente el producto punto
	de dos vectores. Cada hilo ejecuta las operaciones correspondientes sobre una porción
	de los vectores demarcada por los valores del parámetro entregado(estructura Rango). 
	Se retorna el valor parcial del producto punto calculado por el hilo.
*/
void* productoPunto(void* parameters){
	Rango *rango = (Rango *) parameters;
	int i, product, dot_product = 0;
	for (i = rango->inicio; i <= rango->final; i++){
		product = vector1[i] * vector2[i];
		dot_product = dot_product + product;
	}
	return(dot_product);
}
