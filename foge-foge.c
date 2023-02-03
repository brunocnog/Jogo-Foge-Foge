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

    if(!ehdirecao(direcao))
        return;

    //variável auxiliar que guarda a próxima posição do herói para validação
    int proximoX = heroi.x;
    int proximoY = heroi.y;

    //caso as teclas corretas tenha sido usadas, atualiza a próxima posição do herói
    switch (direcao){
        case 'a':
            proximoY--;
            break;
        case 'd':
            proximoY++;
            break;
        case 's':
            proximoX--;
            break;
        case 'w':
            proximoX++;
            break;
    }

    //valida a posição futura
    if(proximoX >= m.linhas)
        return;
    if(proximoY >= m.linhas)
        return;

    //garante que a nova posição é vazia
    if(m.matriz[proximoX][proximoY] != '.')
        return;

    //atualizando a posição do herói e marcar a posição antiga como vazia
    m.matriz[proximoX][proximoY] = '@';
    m.matriz[heroi.x][heroi.y] = '.';
    heroi.x = proximoX;
    heroi.y = proximoY;

}

int ehdirecao(char direcao){
    return
        direcao !='a'||
        direcao !='d'||
        direcao !='s'||
        direcao !='w';
}