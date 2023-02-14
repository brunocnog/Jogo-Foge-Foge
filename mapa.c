#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
//#include "foge-foge.h"

void leMapa(MAPA *m){

    FILE *f;

    f = fopen("mapa.txt", "r");
    if(f == 0) {
        printf("Erro na leitura do Mapa");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
    alocaMapa(m);

    for(int i = 0; i < 5; i++){
        fscanf(f, "%s\n", m->matriz[i]);
    }

    fclose(f);
} 

void alocaMapa(MAPA *m){

    //cria uma alocação dinâmica de memória de acordo com a quantidade de linhas no arquivo mapa.txt
    m->matriz = malloc(sizeof(char*) * m->linhas);

    //cria um array para alocar de forma dinâmica a quantidade de memória necessária para todas as colunas em cada linha.
    //mapa[0] = qtd de mem da linha[0] * qtd de mem da coluna [0] mais um espaço para o enter.
    for(int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * m->colunas +1);
    }
}

void liberaMapa(MAPA *m){

    for(int i = 0; i < m->linhas; i++){
        free(m->matriz[i]);
    }
    free(m->matriz);
}

void imprimeMapa(MAPA *m){

    for(int i = 0; i < m->linhas; i++){
        printf("%s\n", m->matriz[i]);
    }
}

//função alterada de void para int, a fim de devolver um inteiro para ser tratado
//como booleano (verdadeiro/falso)
int encontraMapa(MAPA *m, POSICAO *p, char c){
    for(int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            if(m->matriz[i][j] == c){
                p->x = i;
                p->y = j;
                return;
            }
        }
    }
    //herói não encontrado
    return 0;
}

//função que valida a posição futura
int ehValida(MAPA *m, int x, int y){
    if(x >= m->linhas)
        return 0;
    if(y >= m->colunas)
        return 0;

    return 1;
}

//garante que a nova posição é vazia
int ehVazia(MAPA *m, int x, int y){
    return m->matriz[x][y] == VAZIO;
}

int podeAndar(MAPA *m, int x, int y){
    return
        ehValida(m, x, y) && ehVazia(m, x, y);
}

//move algo que está em uma posição para a nova posição
void andaNoMapa(MAPA *m, int xOrigem, int yOringem, int xDestino, int yDestino) {

    char personagem = m->matriz[xOrigem][yOringem]; //variável auxiliar
    m->matriz[xDestino][yDestino] = personagem;
    m->matriz[xOrigem][yOringem] = VAZIO;
}

//copia o mapa para comparar se os fantasmas andaram
void copiaMapa(MAPA *destino, MAPA *origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;
    alocaMapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}