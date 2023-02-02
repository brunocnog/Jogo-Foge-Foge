#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

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