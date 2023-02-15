#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "foge-foge.h"
#include "mapa.h"

//struct mapa MAPA
MAPA m;
POSICAO heroi;

/* variáveis globais */
//guardam a posição inicial do jogador
int x, y;
int temPilula = 0;

int main(){

    leMapa(&m);
    encontraMapa(&m, &heroi, HEROI);

    do {
        printf("\n");
        printf("Pilula: %s\n", (temPilula ? "SIM" : "NAO"));
        imprimeMapa(&m);

        char comando; // A S D W
        scanf(" %c", &comando);
       
       if(ehDirecao(comando)) move(comando);
       //3 é a quantidade de casas que temos que explodir
       if(comando == BOMBA) explodePilula(heroi.x, heroi.y, 3);
       fantasma();

    }while (!acabou());

    liberaMapa(&m);
}

int acabou(){   
    POSICAO pos;

    int perdeu = !encontraMapa(&m, &pos, HEROI);
    int ganhou = !encontraMapa(&m, &pos, FANTASMA);

    return ganhou || perdeu;
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
    if(ehPersonagem(&m, PILULA, proximoX, proximoY)){
        temPilula = 1;
    }

    //atualizando a posição do herói e marcar a posição antiga como vazia
    andaNoMapa(&m, heroi.x, heroi.y, proximoX, proximoY);
    heroi.x = proximoX;
    heroi.y = proximoY;
}

int praOndeFantasmaVai(int xAtual, int yAtual, int *xDestino, int *yDestino){

    int opcoes[4][2] = {
        {xAtual     ,   yAtual+1   },
        {xAtual+1   ,   yAtual     },
        {xAtual     ,   yAtual-1   },
        {xAtual-1   ,   yAtual     }
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

//destroi fantasmas à direita por 3 casas, parando o efeito da bomba 
//caso tenha uma parede
void explodePilula(int x, int y, int qtd){
    
    //retorna zero, se o jogador não tiver pílula
    if(!temPilula) return;

    explodePilula2(heroi.x, heroi.y, 0, 1, 3);
    explodePilula2(heroi.x, heroi.y, 0, -1, 3);
    explodePilula2(heroi.x, heroi.y, 1, 0, 3);
    explodePilula2(heroi.x, heroi.y, -1, 0, 3);

    //tira a pílula que acabou de usar
    temPilula = 0;
}

void explodePilula2(int x, int y, int somaX, int somaY, int qtd){
    
    if(qtd == 0) return;
    int novoX = x + somaX;
    int novoY = y + somaY;

    if(!ehValida(&m, novoX, novoY)) return;
    if(ehParede(&m, novoX, novoY)) return;

     m.matriz[novoX][novoY] = VAZIO;
     explodePilula2(novoX, novoY, somaX, somaY, qtd-1);
}
