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

