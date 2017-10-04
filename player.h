typedef struct player {
	int vida;
	int pontos;
	int posicaoNave;
} PLAYER;

void desenhaNave();
void desenhaPlayer(PLAYER* p);
void desenhaVidas(PLAYER* p);

void resetPosicao(PLAYER* p);
int getPosicao(PLAYER* p);
void setPosicao(PLAYER* p, int mov);
int getVida(PLAYER* p);
void setVida(PLAYER* p, int vida);
int getPontos(PLAYER* p);
void setPontos(PLAYER* p, int pontos);
