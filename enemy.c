#include <GL/glut.h>
#include "enemy.h"

void desenhaEnemy(ENEMY e){

    glLoadIdentity();

    switch(getCorEnemy(&e)){
        case 1:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 2:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 3:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case 4:
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        case 5:
            glColor3f(1.0f, 0.65f, 0.0f);
        break;
    }

    glBegin(GL_QUADS);
        glVertex2f(getXEnemy(&e), getYEnemy(&e));
        glVertex2f(getXEnemy(&e) - 5, getYEnemy(&e));
        glVertex2f(getXEnemy(&e) - 5, getYEnemy(&e) - 3);
        glVertex2f(getXEnemy(&e), getYEnemy(&e) - 3);
    glEnd();

    //desenha canhão
    glBegin(GL_TRIANGLES);
        glVertex2f(getXEnemy(&e) - 2, getYEnemy(&e) - 3);
        glVertex2f(getXEnemy(&e) - 2.5, getYEnemy(&e) - 4);
        glVertex2f(getXEnemy(&e) - 3, getYEnemy(&e) - 3);
    glEnd();
}

int getXEnemy(ENEMY* e){
    return e->x;
}

void setXEnemy(ENEMY* e, int x){
    e->x = x;
}

int getYEnemy(ENEMY* e){
    return e->y;
}

void setYEnemy(ENEMY* e, int y){
    e->y = y;
}

int getVidaEnemy(ENEMY* e){
    return e->vida;
}

void setVidaEnemy(ENEMY* e, int vida){
    e->vida = vida;
}

int getCorEnemy(ENEMY* e){
    return e->cor;
}

void setCorEnemy(ENEMY* e, int cor){
    e->cor = cor;
}
