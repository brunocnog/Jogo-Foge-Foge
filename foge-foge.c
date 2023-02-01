#include <stdio.h>
#include <stdlib.h>
#include "foge-foge.h"

MAPA m;

int main(){

    leMapa();

    do {

        imprimeMapa();

        char comando; // A S D W
        scanf(" %c", &comando);
        move(comando);

    }while (!acabou());

    void liberaMapa();

}

void leMapa(){

    FILE *f;

    f = fopen("mapa.txt", "r");
    if(f == 0) {
        printf("Erro na leitura do Mapa");
        exit(1);
    }

    fscanf(f, "%d %d", &(m.linhas), &(m.colunas));
    alocaMapa();

    //cria o array de linhas do detanho determinado pelo arquivo mapa.txt
    for(int i = 0; i < 5; i++){
        fscanf(f, "%s\n", m.matriz[i]);
    }

    fclose(f);
} 

void alocaMapa(){

    //cria uma alocação dinâmica de memória de acordo com a quantidade de linhas no arquivo mapa.txt
    m.matriz = malloc(sizeof(char*) * m.linhas);

    //cria um array para alocar de forma dinâmica a quantidade de memória necessária para todas as colunas em cada linha.
    //mapa[0] = qtd de mem da linha[0] * qtd de mem da coluna [0] mais um espaço para o enter.
    for(int i = 0; i < m.linhas; i++){
        m.matriz[i] = malloc(sizeof(char) * m.colunas +1);
    }
}

void liberaMapa(){

    for(int i = 0; i < m.linhas; i++){
        free(m.matriz[i]);
    }
    free(m.matriz);
}

int acabou(){
    
    return 0;
}

void imprimeMapa(){

    for(int i = 0; i < m.linhas; i++){
        printf("%s\n", m.matriz[i]);
    }
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