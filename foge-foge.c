#include <stdio.h>
#include <stdlib.h>
#include "foge-foge.h"
#include "mapa.h"

//struct mapa MAPA
MAPA m;

int main(){

    leMapa(&m);

    do {

        imprimeMapa(&m);

        char comando; // A S D W
        scanf(" %c", &comando);
        move(comando);

    }while (!acabou());

        liberaMapa(&m);

}

int acabou(){
    
    return 0;
}

void move(char direcao){

    int x, y;

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            if(m.matriz[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao){
        case 'a':
            m.matriz[x][y-1] = '@';
            break;
        case 'd':
            m.matriz[x][y+1] = '@';
            break;
        case 's':
            m.matriz[x+1][y] = '@';
            break;
        case 'w':
            m.matriz[x-1][y] = '@';
            break;
    }

    m.matriz[x][y] = '.';
}