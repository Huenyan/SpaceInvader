#include <GL/glut.h>
#include "player.h"

void desenhaNave(){

    glBegin(GL_QUADS);
        glVertex2f(-5, -40);
        glVertex2f(5, -40);
        glVertex2f(5, -37);
        glVertex2f(-5, -37);
    glEnd();

    //desenha canhão
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.5f, -37);
        glVertex2f(1.5f, -37);
        glVertex2f(0, -35);
    glEnd();
}

void desenhaPlayer(PLAYER* p){
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.8f);
    glTranslatef(p->posicaoNave, 0, 0);
    desenhaNave();
}

void desenhaVidas(PLAYER* p){
    int i;

    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.95f);
    glScalef(.5,.5,0);
    glTranslatef(-100, -50, 0);

    for (i = 0; i < p->vida; i++){
        glTranslatef(12, 0, 0);
        desenhaNave();
    }
}

void resetPosicao(PLAYER* p){
    p->posicaoNave = 0;
}

void setPosicao(PLAYER* p, int mov){
    p->posicaoNave = p->posicaoNave + mov;
}

int getPosicao(PLAYER* p){
    return p->posicaoNave;
}

int getVida(PLAYER* p){
    return p->vida;
}

void setVida(PLAYER* p, int vida){
    p->vida = vida;
}

int getPontos(PLAYER* p){
    return p->pontos;
}

void setPontos(PLAYER* p, int pontos){
    p->pontos = pontos;
}
