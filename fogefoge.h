#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

//Constantes
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

//assinatura das funções
int acabou();
void move(char direcao);
int ehDirecao(char direcao);
void fantasma();
int praOndeFantasmaVai(int xAtual, int yAtual, int *xDestino, int *yDestino);

#endif