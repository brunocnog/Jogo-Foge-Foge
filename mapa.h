//Constantes
#define HEROI '@'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'

struct mapa{
    char **matriz;
    int linhas, colunas;
};

//typedef permite chamar a struct somente pelo nome "MAPA" ou invés de struct MAPA, toda vez que precisar usar
typedef struct mapa MAPA;

//assinatura das funções
void alocaMapa(MAPA *m);
void leMapa(MAPA *m);
void liberaMapa(MAPA *m);
void imprimeMapa(MAPA *m);
int ehValida(MAPA *m, int x, int y);
int ehVazia(MAPA *m, int x, int y);
void andaNoMapa(MAPA *m, int xOrigem, int yOringem, int xDestino, int yDestino);

struct posicao {
    int x, y;
};

typedef struct posicao POSICAO;

void encontraMapa(MAPA *m, POSICAO *p, char c);


