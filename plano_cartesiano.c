#include <GL/glut.h>
#include "plano_cartesiano.h"

#define ESQUERDA	-10
#define	DIREITA		10
#define	BAIXO		-10
#define	CIMA		10

void display();

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("plano_cartesiano.h");
	
	glutDisplayFunc(display);
	
	glClearColor(1,1,1,0);
	glutMainLoop();
	return 0;
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(ESQUERDA,DIREITA,BAIXO,CIMA);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	planoCartesiano(ESQUERDA,DIREITA,BAIXO,CIMA);	
	glFlush();
}
