#include <stdio.h>
#include <stdlib.h>
#include "foge-foge.h"

char **mapa;
int linhas;
int colunas;


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

    fscanf(f, "%d %d", &linhas, &colunas);
    alocaMapa();

    //cria o array de linhas do detanho determinado pelo arquivo mapa.txt
    for(int i = 0; i < 5; i++){
        fscanf(f, "%s\n", mapa[i]);
    }

    fclose(f);
} 

void alocaMapa(){

    //cria uma alocação dinâmica de memória de acordo com a quantidade de linhas no arquivo mapa.txt
    mapa = malloc(sizeof(char*) * linhas);

    //cria um array para alocar de forma dinâmica a quantidade de memória necessária para todas as colunas em cada linha.
    //mapa[0] = qtd de mem da linha[0] * qtd de mem da coluna [0] mais um espaço para o enter.
    for(int i = 0; i < linhas; i++){
        mapa[i] = malloc(sizeof(char) * colunas +1);
    }
}

void liberaMapa(){

    for(int i = 0; i < linhas; i++){
        free(mapa[i]);
    }
    free(mapa);
}

int acabou(){
    
    return 0;
}

void imprimeMapa(){

    for(int i = 0; i < linhas; i++){
        printf("%s\n", mapa[i]);
    }
}

void move(char direcao){

    int x, y;

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(mapa[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao){
        case 'a':
            mapa[x][y-1] = '@';
            break;
        case 'd':
            mapa[x][y+1] = '@';
            break;
        case 's':
            mapa[x+1][y] = '@';
            break;
        case 'w':
            mapa[x-1][y] = '@';
            break;
    }
    
    mapa[x][y] = '.';
}