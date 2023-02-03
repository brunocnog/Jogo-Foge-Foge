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

    encontraMapa(&m, &heroi, HEROI);

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

    if(!ehDirecao(direcao))
        return;

    //variável auxiliar que guarda a próxima posição do herói para validação
    int proximoX = heroi.x;
    int proximoY = heroi.y;

    //caso as teclas corretas tenha sido usadas, atualiza a próxima posição do herói
    switch (direcao){
        case ESQUERDA:
            proximoY--;
            break;
        case DIREITA:
            proximoY++;
            break;
        case BAIXO:
            proximoX--;
            break;
        case CIMA:
            proximoX++;
            break;
    }

    if(!ehValida(&m, proximoX, proximoY))
       return;
    if(!ehVazia(&m, proximoX, proximoY))
        return;

    //atualizando a posição do herói e marcar a posição antiga como vazia
    andaNoMapa(&m, heroi.x, heroi.y, proximoX, proximoY);
    heroi.x = proximoX;
    heroi.y = proximoY;

}

int ehDirecao(char direcao){
    return
        direcao !=ESQUERDA||
        direcao !=DIREITA||
        direcao !=BAIXO||
        direcao !=CIMA;
}