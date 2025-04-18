#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int tamanio_inicial = 5;   // Tamaño inicial del array
    int nuevo_tamanio, i;

    // 1. Usar malloc para asignar memoria inicial para el array de enteros (completar)
    // array = malloc(...);

     array=(int*)malloc(sizeof(int)*5);
    if (array == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Inicializar el array con valores (completar)
    for (i = 0; i < tamanio_inicial; i++) {
        // Asignar valores a array[i]
        array[i]=i+1;
    }

    // Mostrar el contenido inicial del array
    printf("Contenido inicial del array:\n");
    for (i = 0; i < tamanio_inicial; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // 2. Solicitar un nuevo tamaño al usuario y reasignar la memoria (completar)
    printf("Ingresa el nuevo tama�o del array: ");
    scanf("%d", &nuevo_tamanio);
       if (nuevo_tamanio < 1) {  // Validaci�n de tama�o
        printf("Tamano no valido.\n");
        free(array);
        return 1;
    }
    // Usar realloc para redimensionar el array
    // array = realloc(...);
     array=(int *)realloc(array, nuevo_tamanio * sizeof(int));
    if (array == NULL) {
        printf("Error al redimensionar memoria\n");
        return 1;
    }

    // Inicializar los nuevos elementos a un valor por defecto (completar)
    for (i = tamanio_inicial; i < nuevo_tamanio; i++) {
        // Asignar valor por defecto a array[i]
        array[i]=i+1;
    }

    // Mostrar el contenido del array redimensionado
    printf("Contenido del array redimensionado:\n");
    for (i = 0; i < nuevo_tamanio; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // 3. Liberar la memoria asignada con free (completar)
    // free(...);
    free(array);
    // Validar si la memoria fue liberada correctamente mostrando un mensaje
    printf("Memoria liberada correctamente.\n");

    return 0;
}
