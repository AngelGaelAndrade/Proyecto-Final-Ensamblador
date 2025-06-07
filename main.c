#include <stdlib.h>
#include <stdio.h>
//proyecto final laberinto Angel Gael Andrade Ovalle

int main(){
    // M es 77 ASCII
    // . es 46 ASCII
    // # es 35 ASCII
    
    char laberinto[10][10] = {
        {'#','#','#','#','#','#','#','#','#','#'},
        {'P','.','#','.','.','.','.','.','.','#'},
        {'#','.','#','.','#','.','#','#','.','#'},
        {'#','.','.','.','#','.','#','.','.','#'},
        {'#','#','#','#','#','.','#','.','#','#'},
        {'#','.','.','.','.','.','#','.','.','#'},
        {'#','.','#','#','#','.','.','#','.','#'},
        {'#','.','#','.','#','.','#','#','.','#'},
        {'#','.','.','.','#','.','.','.','.','M'},
        {'#','#','#','#','#','#','#','#','#','#'},
    };


    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (laberinto[i][j] == '-') {
                printf("[.]");  // Mostrar camino como punto
            } else {
                printf("[%c] ", laberinto[i][j]);  // Mostrar tal cual
            }
        }
        printf("\n");
    }

    system("pause");
    return 0;
}
