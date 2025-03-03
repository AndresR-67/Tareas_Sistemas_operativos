#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int variable_global=66;
int variable_global2=10;
int variable_global3=110;
int variable_global4=34;
static int variable_g2=33;




// Función para mostrar direcciones de memoria de distintos segmentos
void mostrar_segmentos() {
 int variable_local=14;
 int variable_local2=6;
 int variable_local3=99;


 static int variable_l2=12;
 static int variable_l3=77;
 static int variable_l4=16;
 
 //Punteros de variables globales (inicio)//
  int *memoriaDinamica_global = (int *) malloc(sizeof(int));
  int *memoriaDinamica_global2 = (int *) malloc(sizeof(int));
  int *memoriaDinamica_global3 = (int *) malloc(sizeof(int));
  int *memoriaDinamica_global4 = (int *) malloc(sizeof(int));
  int *memoriaDinamica_globalestatica = (int *) malloc(sizeof(int)); //puntero estatico global

  *memoriaDinamica_global=variable_global;
  *memoriaDinamica_global2=variable_global2;
  *memoriaDinamica_global3=variable_global3;
  *memoriaDinamica_global4=variable_global4;
  *memoriaDinamica_globalestatica=variable_g2;
  //Punteros de variables globales (fin)//

  //punteros de variables locales //
  int *memoria_local = (int *) malloc(sizeof(int));
  int *memoria_local2 = (int *) malloc(sizeof(int));
  int *memoria_local3 = (int *) malloc(sizeof(int));

  *memoria_local=variable_local;
  *memoria_local2=variable_local2;
  *memoria_local3=variable_local3;
  //fin punteros locales//

  //inicio puntero estaticas locales//
  
  int *memoriaEstatica_Local = (int *)malloc(sizeof(int));
  int *memoriaEstatica_Local2 = (int *)malloc(sizeof(int));
  int *memoriaEstatica_Local3 = (int *)malloc(sizeof(int));

  *memoriaEstatica_Local=variable_l2;
  *memoriaEstatica_Local2=variable_l3;
  *memoriaEstatica_Local3=variable_l4;


  printf ("Dirrecion de memoria variables globales: %p  %p %p %p \n",&variable_global,&variable_global2,&variable_global3,&variable_global4);
  printf("Direccion de memoria variable estatica global: %p \n",&variable_g2);
  printf("Direccion de memoria variables locales: %p %p %p \n",&variable_local,&variable_local2,&variable_local3);
  printf ("Dirrecion de memoria variables estaticas locales: %p %p %p \n", &variable_l2,&variable_l3,&variable_l4);

   free(memoriaDinamica_global);
   free(memoriaDinamica_global2);
   free(memoriaDinamica_global3);
   free(memoriaDinamica_global4);
   free(memoriaDinamica_globalestatica);
   free(memoria_local);
   free(memoria_local3);
   free(memoria_local2);
   free(memoriaEstatica_Local);
   free(memoriaEstatica_Local2);
   free(memoriaEstatica_Local3);
   
 

}

// Función para mostrar el consumo de memoria del proceso usando /proc/self/status
void mostrar_consumo_memoria() {

 char comando[100];
 snprintf(comando, sizeof(comando), "cat /proc/%d/status | grep -E 'VmSize|VmRSS'", getpid());
 printf ("Consumo de memoria \n");
 system(comando);

} 
  



// Función para asignar memoria dinámica
void asignar_memoria_dinamica() {
    int *arreglo;
    int tamano;

    
    printf ("consumo de memoria antes de la asignacion \n");
    mostrar_consumo_memoria();
    
     printf ("Ingrese el tamaño del arreglo \n");
    scanf("%d", &tamano);

    
    arreglo = (int *) malloc(tamano * sizeof(int));

    
    if (arreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return;  // Salir si malloc falla
    }

    // Medir el consumo de memoria despues
    printf ("Consumo despues de la asignacion");
    mostrar_consumo_memoria();

    // Llenar el arreglo con datos
    for (int i = 0; i < tamano; i++) {
        arreglo[i] = i + 1;
    }

    // Mostrar los valores del arreglo
    printf("Los valores del arreglo son:\n");
    for (int i = 0; i < tamano; i++) {
        printf("%d \n", arreglo[i]);
    }

    // Liberar la memoria asignada
    free(arreglo);

    
    printf("\nConsumo de memoria despues de liberar la memoria dinamica:\n");
    mostrar_consumo_memoria();
}





// Menú interactivo
void menu() {
    int opcion;
    size_t size;

    do {
        printf("\n--- Menú de Gestión de Memoria ---\n");
        printf("1. Mostrar direcciones de memoria\n");
        printf("2. Mostrar consumo de memoria\n");
        printf("3. Asignar memoria dinámica\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer de entrada

        switch (opcion) {
            case 1:
                mostrar_segmentos();
                break;
            case 2:
                mostrar_consumo_memoria();
                break;
            case 3:
                asignar_memoria_dinamica ();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 4);
}

int main() {  //gracias Dios
    mostrar_consumo_memoria();
    menu();
    return 0;
}

