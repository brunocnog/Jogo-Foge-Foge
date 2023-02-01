void alocaMapa();
void leMapa();
void liberaMapa();
int acabou();
void imprimeMapa();
void move(char direcao);

struct mapa{
    char **matriz;
    int linhas, colunas;
};

//typedef permite chamar a struct somente pelo nome "MAPA" ou invés de struct MAPA, toda vez que precisar usar
typedef struct mapa MAPA;
