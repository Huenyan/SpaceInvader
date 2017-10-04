#ifndef __plano_cartesiano_h__
#define __plano_cartesiano_h__

#include <GL/glut.h>

void planoCartesiano(GLfloat esquerda, GLfloat direita, GLfloat baixo, GLfloat cima) {
	glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(0,cima);
		glVertex2f(0,baixo);

		glVertex2f(esquerda,0);
		glVertex2f(direita,0);
	glEnd();
	glPointSize(3);
	glBegin(GL_POINTS);
		int i;
		for(i=baixo;i<cima;i++) {
			glVertex2i(0,i);
		}
		for(i=esquerda;i<direita;i++) {
			glVertex2i(i,0);
		}
	glEnd();
	glFlush();
}

#endif
