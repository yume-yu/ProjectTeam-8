#include "glut.h"
#include <stdio.h>
#include <stdlib.h>

#define SCR_W 100
#define SCR_H 150

#define RATIO 2
#define OFFSET 8

#define SCREEN_W (SCR_W * 8 * RATIO)
#define SCREEN_H (SCR_H * 8 * RATIO)

#define SCREEN_W2 (SCREEN_W + OFFSET * 2)
#define SCREEN_H2 (SCREEN_H + OFFSET * 2)

void setPixel(int x, int y, int white) {
	if (white) {
		glColor3d(0.5, 1.0, 0.7);
	} else {
		glColor3d(0.0, 0.0, 0.0);
	}
	double dx = (double)(x * RATIO + OFFSET) / SCREEN_W2 * 2.0 - 1.0;
	double dy = -(double)(y * RATIO + OFFSET) / SCREEN_H2 * 2.0 + 1.0;
	double dx2 = (double)((x + 1) * RATIO + OFFSET) / SCREEN_W2 * 2.0 - 1.0;
	double dy2 = -(double)((y + 1) * RATIO + OFFSET) / SCREEN_H2 * 2.0 + 1.0;
	glBegin(GL_POLYGON);
	glVertex2d(dx, dy);
	glVertex2d(dx2, dy);
	glVertex2d(dx2, dy2);
	glVertex2d(dx, dy2);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	setPixel(0, 0, 1);
	setPixel(32 * 8 - 1, 0, 1);
	setPixel(32 * 8 - 1, 24 * 8 - 1, 1);
	setPixel(0, 24 * 8 - 1, 1);

	for (int i = 0; i < 100; i++) {
		int x = rand() % SCREEN_W;
		int y = rand() % SCREEN_H;
		setPixel(x, y, 1);
	}

	glFlush();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}
void keyboard(unsigned char key, int x, int y) {
	printf("key: %d\n", (int)key);
	switch (key) {
		case 'q':
		case 'Q':
		case '\033':  // esc
			exit(0);
			break;
		case ' ':
			glutPostRedisplay();
			break;
		case 's':
			glutIdleFunc(glutPostRedisplay);
			break;
		case 'e':
			glutIdleFunc(0);
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {
	glutInitWindowSize(SCREEN_W2, SCREEN_H2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}
