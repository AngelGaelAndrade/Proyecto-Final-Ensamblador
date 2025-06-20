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

int menu();

int main(){
    // M es 77 ASCII
    // . es 46 ASCII
    // # es 35 ASCII
    int respuesta;
    
    do{
        respuesta = menu();
        switch (respuesta)
        {
        case 1:
            system("cls");
            PrintMaze(&laberinto[0][0], 10, 10);
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