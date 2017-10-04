typedef struct tiro {
    int ativo;
	int x;
	int y;
} TIRO;

int getAtivoTiro(TIRO* tiro);
void setAtivoTiro(TIRO* tiro, int ativo);
int getXTiro(TIRO* tiro);
void setXTiro(TIRO* tiro, int x);
int getYTiro(TIRO* tiro);
void setYTiro(TIRO* tiro, int y);
