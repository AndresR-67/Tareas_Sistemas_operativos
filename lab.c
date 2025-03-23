#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_ARCHIVOS 100
#define BUFFER_SIZE 1024

void menu(){
    int opcion;
    char archivosCreados[MAX_ARCHIVOS][100];
    int contadorArchivos = 0; 
    char nombreLibro[100], origen[100], destino[100], archivoLeer[100];
    int fd;
    int encontrado = 0;
    int fd_origen, fd_destino, fd_leer;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_leidos, bytes_escritos;

    do {
        printf("\n Menu \n");
        printf(" 1. Crear archivo \n");
        printf(" 2. Lista de archivos \n");
        printf(" 3. Copiar archivos \n");
        printf(" 4. Ver contenido de un archivo \n");
		printf(" 5. Salir \n");
        
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                if (contadorArchivos >= MAX_ARCHIVOS) {
                    printf("Limite de archivos alcanzado\n");
                    break;
                }

                char mensaje[] = "satoru gojo ha sido sellado";
                printf("Nombre del archivo (sin espacios): \n");
                scanf("%99s", nombreLibro);

                fd = open(nombreLibro, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("Error al crear el archivo");
                    break;
                }

                write(fd, mensaje, strlen(mensaje)); // Escribe el mensaje
                close(fd);

                strcpy(archivosCreados[contadorArchivos], nombreLibro);
                contadorArchivos++;
                printf("El archivo ha sido creado correctamente\n");
                break;

            case 2:
                if (contadorArchivos == 0) {
                    printf("No hay archivos creados\n");
                } else {
                    printf("Archivos creados:\n");
                    for (int i = 0; i < contadorArchivos; i++) {
                        printf("%s\n", archivosCreados[i]);
                    }
                }
                break;

            case 3:
                if (contadorArchivos == 0) {
                    printf("No hay archivos para copiar\n");
                    break;
                }

                printf("Ingrese el nombre del archivo origen: ");
                scanf("%99s", origen);

                // Verificar si el archivo origen existe en la lista
                encontrado = 0;
                for (int i = 0; i < contadorArchivos; i++) {
                    if (strcmp(archivosCreados[i], origen) == 0) {
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Error: El archivo origen no existe en la lista\n");
                    break;
                }

                printf("Ingrese el nombre del archivo destino: ");
                scanf("%99s", destino);

                // Abrir archivo origen
                fd_origen = open(origen, O_RDONLY);
                if (fd_origen == -1) {
                    perror("Error al abrir el archivo de origen");
                    break;
                }

                // Crear archivo destino
                fd_destino = open(destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_destino == -1) {
                    perror("Error al crear el archivo de destino");
                    close(fd_origen);
                    break;
                }

                // Copiar contenido
                while ((bytes_leidos = read(fd_origen, buffer, BUFFER_SIZE)) > 0) {
                    bytes_escritos = write(fd_destino, buffer, bytes_leidos);
                    if (bytes_escritos != bytes_leidos) {
                        perror("Error al escribir en el archivo de destino");
                        close(fd_origen);
                        close(fd_destino);
                        break;
                    }
                }

                if (bytes_leidos == -1) {
                    perror("Error al leer el archivo de origen");
                }

                // Cerrar archivos
                close(fd_origen);
                close(fd_destino);

                printf("Archivo copiado correctamente de %s a %s\n", origen, destino);

                // Agregar el nuevo archivo a la lista
                if (contadorArchivos < MAX_ARCHIVOS) {
                    strcpy(archivosCreados[contadorArchivos], destino);
                    contadorArchivos++;
                }

                break;

            case 4: // Ver contenido del archivo
                if (contadorArchivos == 0) {
                    printf("No hay archivos creados para leer\n");
                    break;
                }

                printf("Ingrese el nombre del archivo a leer: ");
                scanf("%99s", archivoLeer);

                // Verificar si el archivo existe en la lista
                encontrado = 0;
                for (int i = 0; i < contadorArchivos; i++) {
                    if (strcmp(archivosCreados[i], archivoLeer) == 0) {
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Error: El archivo no existe en la lista\n");
                    break;
                }

                // Abrir archivo en modo lectura
                fd_leer = open(archivoLeer, O_RDONLY);
                if (fd_leer == -1) {
                    perror("Error al abrir el archivo para lectura");
                    break;
                }

                printf("Contenido del archivo %s:\n", archivoLeer);
                while ((bytes_leidos = read(fd_leer, buffer, BUFFER_SIZE)) > 0) {
                    write(STDOUT_FILENO, buffer, bytes_leidos); // Imprimir en pantalla
                }

                if (bytes_leidos == -1) {
                    perror("Error al leer el archivo");
                }

                close(fd_leer);
                break;
        }
    } while (opcion != 5);
}

int main() {
    menu();
}

