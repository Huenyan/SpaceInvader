#include <GL/glut.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"
#include "player.h"
#include "tiro.h"

#define MAXLADO 40
#define COLINIMIGOS 10
#define LINEINIMIGOS 5
#define MAXIMOTIROS 3
#define MAXIMOTIROSINIMIGOS 5
#define VIDAS 5

#define VERMELHO 1
#define VERDE 2
#define AZUL 3
#define AMARELO 4
#define LARANJA 5

void inicializaParametros();
void inicializaPrograma();
void desenha();
void botoesTeclas(unsigned char tecla);
void desenhaFleat();
void criaFleat();
void timer(int value);
void ativaNovoTiro();
void desenhaTiros();
void detectaColisaoEnemy();
void detectaColisaoPlayer();
void criaTiroEnemy();
void desenhaTirosEnemy();
void criaPlayer();
int ultimoY();
void desenhaLimite();
void desenhaPontos();
void desenhaVitoria();
void desenhaDerrota();
void desenhaInicio();

PLAYER p;
ENEMY fleat [LINEINIMIGOS][COLINIMIGOS];
TIRO tiros [MAXIMOTIROS];
TIRO tirosEnemy [MAXIMOTIROSINIMIGOS];

int movimentoX = 0;
int movimentoY = 0;
int qtdeLoops = 0;
int incrementar = 1;
int inimigosAtivos = LINEINIMIGOS * COLINIMIGOS;
int gameover = 0;
int space = 0;

void botoesTeclas(unsigned char tecla)
{
    if (gameover == 0)
    {
        if (space == 1)
        {
            if (inimigosAtivos > 0)
            {
                tecla = tolower(tecla);

                switch(tecla)
                {
                case 'a':
                    if (getPosicao(&p) > -MAXLADO)
                    {
                        setPosicao(&p, -3);
                    }
                    break;
                case 'd':
                    if (getPosicao(&p) < MAXLADO)
                    {
                        setPosicao(&p, 3);
                    }
                    break;
                case 'w':
                    ativaNovoTiro();
                    break;
                }

                glutPostRedisplay();
            }
        }
        else
        {
            if (tecla == ' ')
            {
                space = 1;
            }
        }
    }
}

void desenha()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);

    if (space)
    {
        if (gameover == 0)
        {
            if (inimigosAtivos > 0)
            {
                desenhaVidas(&p);
                desenhaPlayer(&p);
                desenhaPontos();
                desenhaLimite();
                desenhaTiros();
                desenhaTirosEnemy();
                desenhaFleat();
            }
            else
            {
                desenhaVitoria();
            }
        }
        else
        {
            desenhaDerrota();
        }

    }
    else
    {
        desenhaInicio();
    }

    glutSwapBuffers();
}

void timer(int value)
{
    if ((gameover == 0)&&(space == 1))
    {
        if (inimigosAtivos > 0)
        {
            qtdeLoops++;

            if (qtdeLoops > 20)
            {
                qtdeLoops = 0;

                if (incrementar > 0)
                {
                    if (movimentoX >= 4)
                    {
                        incrementar = 0;
                        movimentoX--;
                        movimentoY--;
                    }
                    else
                    {
                        movimentoX++;
                    }
                }
                else
                {
                    if (movimentoX <= -4)
                    {
                        incrementar = 1;
                        movimentoX++;
                        movimentoY--;
                    }
                    else
                    {
                        movimentoX--;
                    }
                }

                if (inimigosAtivos > 0)
                {
                    criaTiroEnemy();
                }
            }

            detectaColisaoEnemy();
            detectaColisaoPlayer();

            int i;
            for(i=0; i<MAXIMOTIROS; i++)
            {
                if (getAtivoTiro(&tiros[i]) == 1)
                {
                    if (getYTiro(&tiros[i]) >= 50)
                    {
                        setAtivoTiro(&tiros[i], 0);
                    }
                    else
                    {
                        int novaPosicaoTiro = getYTiro(&tiros[i]) + 1;
                        setYTiro(&tiros[i], novaPosicaoTiro);
                    }
                }
            }

            for(i=0; i<MAXIMOTIROSINIMIGOS; i++)
            {
                if (getAtivoTiro(&tirosEnemy[i]) == 1)
                {
                    if (getYTiro(&tirosEnemy[i]) <= -50)
                    {
                        setAtivoTiro(&tirosEnemy[i], 0);
                    }
                    else
                    {
                        int novaPosicaoTiro = getYTiro(&tirosEnemy[i]) - 1;
                        setYTiro(&tirosEnemy[i], novaPosicaoTiro);
                    }
                }
            }

            if (ultimoY() <= -20){
                gameover = 1;
            }

            glutPostRedisplay();
            glutTimerFunc(30,timer, 1);
        }
    }
    else
    {
        glutPostRedisplay();
        glutTimerFunc(30,timer, 1);
    }
}

void inicializaParametros()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void inicializaPrograma()
{
    criaPlayer();
    criaFleat();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300,0);
    glutInitWindowSize(700, 695);
    glutCreateWindow("Space Invaders");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(botoesTeclas);
    glutTimerFunc(30, timer, 1);
    inicializaParametros();
    glutMainLoop();
}
void criaFleat()
{
    int i, j;

    for (i=0; i < LINEINIMIGOS; i++)
    {
        for(j=0; j < COLINIMIGOS; j++)
        {
            setVidaEnemy(&fleat[i][j], 1);
        }
    }
}

void criaTiroEnemy()
{
    while(1)
    {
        int linha = rand() % 5;
        int coluna = rand() % 10;

        if (getVidaEnemy(&fleat[linha][coluna]) > 0)
        {
            int i = 0;
            for(i=0; i<MAXIMOTIROSINIMIGOS; i++)
            {
                if (getAtivoTiro(&tirosEnemy[i]) == 0)
                {

                    int x = getXEnemy(&fleat[linha][coluna]);
                    int y = getYEnemy(&fleat[linha][coluna]);

                    setAtivoTiro(&tirosEnemy[i], 1);
                    setXTiro(&tirosEnemy[i], x);
                    setYTiro(&tirosEnemy[i], y);
                    return;
                }
            }

        }
    }

}

void ativaNovoTiro()
{
    int i;
    for(i=0; i<MAXIMOTIROS; i++)
    {
        if (getAtivoTiro(&tiros[i]) == 0)
        {
            setAtivoTiro(&tiros[i], 1);
            setXTiro(&tiros[i],getPosicao(&p));
            setYTiro(&tiros[i], -35);
            break;
        }
    }
}

void desenhaFleat()
{
    int i, j;

    for(i=0; i < LINEINIMIGOS; i++)
    {
        for (j=0; j < COLINIMIGOS; j++)
        {
            if (getVidaEnemy(&fleat[i][j]) == 1)
            {
                setCorEnemy(&fleat[i][j], i+1);
                setXEnemy(&fleat[i][j], -40 + j*9.5 + movimentoX);
                setYEnemy(&fleat[i][j],15 + i*7 + movimentoY);
                desenhaEnemy(fleat[i][j]);
            }
        }
    }
}

void desenhaTiros()
{
    int i;

    for(i=0; i<MAXIMOTIROS; i++)
    {
        if (getAtivoTiro(&tiros[i]) == 1)
        {
            glLoadIdentity();
            glColor3f(0,0,0);
            glTranslatef(tiros[i].x,0,0);
            glBegin(GL_LINES);
            glVertex2f(0, tiros[i].y );
            glVertex2f(0, tiros[i].y + 2);
            glEnd();
        }
    }
}

void desenhaTirosEnemy()
{
    int i;

    for(i=0; i<MAXIMOTIROSINIMIGOS; i++)
    {
        if (getAtivoTiro(&tirosEnemy[i]) == 1)
        {
            glLoadIdentity();
            glColor3f(0,0,0);
            glTranslatef(tirosEnemy[i].x,0,0);
            glBegin(GL_LINES);
            glVertex2f(0, tirosEnemy[i].y );
            glVertex2f(0, tirosEnemy[i].y + 2);
            glEnd();
        }
    }
}


void detectaColisaoEnemy()
{
    int i, j, iTiro;

    for(iTiro = 0; iTiro<MAXIMOTIROS; iTiro++)
    {
        if (getAtivoTiro(&tiros[iTiro]) == 1)
        {
            for (i=0; i < LINEINIMIGOS; i++)
            {
                for(j=0; j < COLINIMIGOS; j++)
                {
                    if (getVidaEnemy(&fleat[i][j]) > 0)
                    {
                        int xNave = getXEnemy(&fleat[i][j]);
                        int yNave = getYEnemy(&fleat[i][j]);

                        int validaY = (getYTiro(&tiros[iTiro]) + 2) >= (yNave - 6);
                        int validaX = ((getXTiro(&tiros[iTiro]) >= (xNave - 5)) && (getXTiro(&tiros[iTiro]) <= (xNave)));

                        if (validaY && validaX)
                        {
                            setVidaEnemy(&fleat[i][j], 0);
                            setAtivoTiro(&tiros[iTiro], 0);
                            inimigosAtivos--;

                            int z = getPontos(&p);
                            z =  z +(getCorEnemy(&fleat[i][j])) * 10;

                            setPontos(&p,z);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void detectaColisaoPlayer()
{

    int iTiro;

    for(iTiro = 0; iTiro<MAXIMOTIROSINIMIGOS; iTiro++)
    {
        if (getAtivoTiro(&tirosEnemy[iTiro]) == 1)
        {
            if (getVida(&p) > 0)
            {
                int xNave = getPosicao(&p);
                int validaX = (getXTiro(&tirosEnemy[iTiro]) >= xNave - 5) && (getXTiro(&tirosEnemy[iTiro]) <= xNave + 5);

                int validaY = (getYTiro(&tirosEnemy[iTiro]) >= -40) && (getYTiro(&tirosEnemy[iTiro]) <= -37);

                if (validaX && validaY)
                {
                    setAtivoTiro(&tirosEnemy[iTiro], 0);
                    setVida(&p, getVida(&p) - 1);
                    //resetPosicao(&p);

                    if (getVida(&p) == 0)
                    {
                        gameover = 1;
                    }
                }
            }
        }
    }
}

void criaPlayer()
{
    setVida(&p, VIDAS);
    setPontos(&p, 0);
}

int ultimoY()
{
    int i, j;

    for (i=0; i < LINEINIMIGOS; i++)
    {
        for(j=0; j < COLINIMIGOS; j++)
        {
            if (getVidaEnemy(&fleat[i][j]) > 0){
                return getYEnemy(&fleat[i][j]);
            }
        }
    }

    return 100;
}

void desenhaLimite(){

    glColor3f(0.5f,0.5f,0.5f);
    glBegin(GL_LINES);
        glVertex2f(-50, -20);
        glVertex2f(50, -20);
    glEnd();
}

void desenhaPontos()
{
    char *string = malloc(sizeof(char) * 100);;

    int x = getPontos(&p);
    char *strPontos = malloc(sizeof(char) * 100);
    sprintf(strPontos, "%d", x);

    strcpy(string, "Pontos: ");
    strcat(string, strPontos);

    int j = strlen( string );
    int i;

    glColor3f(0.0f,0.0f,0.0f);
    glLoadIdentity();
    glRasterPos2i(20, -45);

    for( i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

void desenhaVitoria()
{

    char *string = "Parabens, voce venceu!";
    int j = strlen( string );

    int i;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0f,0.0f,0.0f);
    glLoadIdentity();
    glRasterPos2i(-20,0);

    for( i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void desenhaDerrota()
{
    char *string = "Game Over";
    int j = strlen( string );
    int i;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0f,0.0f,0.0f);
    glLoadIdentity();
    glRasterPos2i(-10,0);

    for( i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void desenhaInicio()
{
    char *string = "Pressione SPACE para iniciar!";
    int j = strlen( string );
    int i;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0f,0.0f,0.0f);
    glLoadIdentity();
    glRasterPos2i(-20,0);

    for( i = 0; i < j; i++ )
    {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

int main()
{
    inicializaPrograma();

    return 0;
}
