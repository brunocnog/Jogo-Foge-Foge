#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
        fantasma();

    }while (!acabou());

    liberaMapa(&m);
}

int acabou(){   
    POSICAO pos; 
    return !encontraMapa(&m, &pos, HEROI);
}

int ehDirecao(char direcao){
    return
            direcao == CIMA||
            direcao == BAIXO||
            direcao == DIREITA||
            direcao == ESQUERDA;
}

void move(char direcao){

    if(!ehDirecao(direcao))
        return;

    //variável auxiliar que guarda a próxima posição do herói para validação
    int proximoX = heroi.x;
    int proximoY = heroi.y;

    //caso as teclas corretas tenha sido usadas, atualiza a próxima posição do herói
    switch(direcao){
        case ESQUERDA:
            proximoY--;
            break;
        case DIREITA:
            proximoY++;
            break;
        case CIMA:
            proximoX--;
            break;
        case BAIXO:
            proximoX++;
            break;
    }

    if(!podeAndar(&m, HEROI, proximoX, proximoY)){
        return;
    }

    //atualizando a posição do herói e marcar a posição antiga como vazia
    andaNoMapa(&m, heroi.x, heroi.y, proximoX, proximoY);
    heroi.x = proximoX;
    heroi.y = proximoY;
}

int praOndeFantasmaVai(int xAtual, int yAtual, int *xDestino, int *yDestino){

    int opcoes[4][2] = {
        {xAtual     ,   yAtual +1   },
        {xAtual + 1 ,   yAtual      },
        {xAtual     ,   yAtual-1    },
        {xAtual-1   ,   yAtual      }
    };

    srand(time(0));
    for(int i = 0; i < 10; i++){
        int posicao = rand() % 4;

        if(podeAndar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
            *xDestino = opcoes[posicao][0];
            *yDestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}

void fantasma(){
    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < copia.linhas; i++){
        for(int j = 0; j < copia.colunas; j++){
            if(copia.matriz[i][j] == FANTASMA){
                
                int xDestino;
                int yDestino;
                int encontrou = praOndeFantasmaVai(i, j, &xDestino, &yDestino);

                if(encontrou){
                    andaNoMapa(&m, i, j, xDestino, yDestino);
                }
            }
        }
    }
    liberaMapa(&copia);
}