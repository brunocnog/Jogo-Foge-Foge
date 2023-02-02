#include <stdio.h>
#include <stdlib.h>
#include "foge-foge.h"
#include "mapa.h"

//struct mapa MAPA
MAPA m;
POSICAO heroi;

//variáveis que guardam a posição inicial do jogador
int x, y;

int main(){

    leMapa(&m);

    encontraMapa(&m, &heroi, '@');

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

    m.matriz[heroi.x][heroi.y] = '.';

    switch (direcao){
        case 'a':
            m.matriz[heroi.x][heroi.y-1] = '@';
            y--;
            break;
        case 'd':
            m.matriz[heroi.x][heroi.y+1] = '@';
            y++;
            break;
        case 's':
            m.matriz[heroi.x+1][heroi.y] = '@';
            x++;
            break;
        case 'w':
            m.matriz[heroi.x-1][heroi.y] = '@';
            x--;
            break;
    }
}