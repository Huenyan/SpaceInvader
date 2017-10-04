#ifndef __enemy_h__
#define	__enemy_h__

typedef struct enemy {
	int x;
	int y;
	int cor;
	int vida;
} ENEMY;

void desenhaEnemy(ENEMY e);
int getXEnemy(ENEMY* e);
void setXEnemy(ENEMY* e, int x);
int getYEnemy(ENEMY* e);
void setYEnemy(ENEMY* e, int y);
int getEnemy(ENEMY* e);
void setVidaEnemy(ENEMY* e, int vida);
int getCorEnemy(ENEMY* e);
void setCorEnemy(ENEMY* e, int cor);
int getVidaEnemy(ENEMY* e);

#endif
