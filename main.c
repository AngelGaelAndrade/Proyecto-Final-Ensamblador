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

//funciones de ensamblador hibrido que reciben una matriz dinamica
//y un caracter para capturar movimiento.
extern void PrintMaze(char *matriz, int filas, int cols);
extern int GameTime(char *matriz, int filas, int cols, char movimiento);

//funciones de C para mas visualidad.
int menu();
void Mensaje_victoria();

int main(){
    int respuesta;
    
    do{
        //llamamos la funcion del menu para tomar la respuesta del juego
        respuesta = menu();

        switch (respuesta)
        {
        case 1:
            //referescamos pantalla y imprimimos el laberinto
            system("cls");
            PrintMaze(&laberinto[0][0], 10, 10);
            char movimiento;

        while (1) {
            //interfaz de juego, con tecla de salida y movimiento
            printf("PARA SALIR PRESIONE [U]\n");
            printf("________________\n");
            printf("|     [W]      |\n");
            printf("| [A] [S] [D]  |\n");
            printf("|______________|\n");
            printf("INGRESE MOVIMIENTO:");

            scanf(" %c", &movimiento);
            //la funcion manda el movimiento para la operacion dinamicamente.
            int resultado = GameTime(&laberinto[0][0], 10, 10, movimiento);

        if (resultado == -1) {
                // -1 = muros
                printf("Movimiento inválido, hay muro.\n");
        } else if (resultado == 1) {
                // 1 = se encontro la salida
                system("cls");
                Mensaje_victoria();
                break;
        } else if (resultado == 2) {
                // 2 = se presiono la tecla de salida del juego
                printf("Gracias por jugar!!!!!\n");
                break;  // Salir del juego
        }

            // Limpiar pantalla y volver a imprimir el laberinto
                system("cls");
                PrintMaze(&laberinto[0][0], 10, 10);
        }
        break;
        case 2:
            //si se aprieta la salida antes de iniciar el juego
            printf("Saliendo del programa....\n");
            break;
        default:
            //defautl salta si no se elegio una opcion aceptable
            printf("\n[ERROR INESPERADO, SELECCIONE UNA RESPUESTA UTIL]\n\n");
            system("pause");
            system("cls");
        }

    }while(respuesta<1 || respuesta>2);

    system("pause");
    return 0;
}

//menu de el juego con titulo y opciones.
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

//mensaje especial al completar el laberinto
void Mensaje_victoria(){
    printf("                                                                                                                 \n");
    printf(" _____ _____ __    _____ _____ _____ ____  _____ ____  _____ _____    _____ _____ _____ _____ _____ _____ _____ \n");
    printf("|   __|   __|  |  |     |     |     |    \\|  _  |    \\|   __|   __|  |   __|  _  |   | |  _  |   __|_   _|   __|\n");
    printf("|   __|   __|  |__|-   -|   --|-   -|  |  |     |  |  |   __|__   |  |  |  |     | | | |     |__   | | | |   __|\n");
    printf("|__|  |_____|_____|_____|_____|_____|____/|__|__|____/|_____|_____|  |_____|__|__|_|___|__|__|_____| |_| |_____|\n");
    printf("                                                                                                                 \n");
    

}
