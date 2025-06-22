#include <stdlib.h>
#include <stdio.h>
//proyecto final laberinto Angel Gael Andrade Ovalle
char laberinto[10][10] = {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'P','.','#','.','.','.','.','.','.','#'},
        {'#','.','#','.','#','.','#','#','.','#'},
        {'#','.','.','.','#','.','#','.','.','#'},
        {'#','#','#','#','#','.','#','.','#','#'},
        {'#','.','.','.','.','.','#','.','.','#'},
        {'#','.','#','#','#','.','.','#','.','#'},
        {'#','.','#','.','#','.','#','#','.','#'},
        {'#','.','.','.','#','.','.','.','.','X'},
        {'#','#','#','#','#','#','#','#','#','#'},
    };

extern void PrintMaze(char *matriz, int filas, int cols);
extern int GameTime(char *matriz, int filas, int cols, char movimiento);

int menu();

int main(){
    int respuesta;
    
    do{
        respuesta = menu();
        switch (respuesta)
        {
        case 1:
            system("cls");
            PrintMaze(&laberinto[0][0], 10, 10);
            char movimiento;

            while (1) {
                printf("Ingrese movimiento (w,a,s,d): ");
                scanf(" %c", &movimiento);

                int resultado = GameTime(&laberinto[0][0], 10, 10, movimiento);

                if (resultado == -1) {
                    printf("Movimiento inválido, hay muro.\n");
                } else if (resultado == 1) {
                    system("cls");
                    PrintMaze(&laberinto[0][0], 10, 10);
                    printf("¡Has llegado a la salida!\n");
                    break;
                }

                // Limpiar pantalla y volver a imprimir el laberinto, podría ser llamado a ensamblador también
                system("cls");
                PrintMaze(&laberinto[0][0], 10, 10);
            }
            break;
    
        case 2:
            printf("Saliendo del programa....\n");
            break;
        default:
            printf("\n[ERROR INESPERADO, SELECCIONE UNA RESPUESTA UTIL]\n\n");
            system("pause");
            system("cls");
        }

    }while(respuesta<1 || respuesta>2);

    system("pause");
    return 0;
}

int menu(){
    int respuesta;

    printf(
    ".######..#####....####...##..##..#####...##......######..........##...##...####...######..######.\n"
    "...##....##..##..##..##..##..##..##..##..##......##..............###.###..##..##.....##...##.....\n"
    "...##....#####...##..##..##..##..#####...##......####............##.#.##..######....##....####...\n"
    "...##....##..##..##..##..##..##..##..##..##......##..............##...##..##..##...##.....##.....\n"
    "...##....##..##...####....####...#####...######..######..........##...##..##..##..######..######.\n"
    ".................................................................................................\n"
    );

    printf("[ 1 ] EMPEZAR JUEGO\n");
    printf("[ 2 ] SALIR DE LA PANTALLA\n");
    printf("SELECCIONE: ");

    scanf("%d",&respuesta);
    return respuesta;
}