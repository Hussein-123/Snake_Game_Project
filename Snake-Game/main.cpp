#include <Gl/gl.h>
#include <GL/glut.h>
#include "game.h"
#include<stdlib.h>
#define COLUMNS 40
#define ROWS 40
#define FPS 8

extern short sDirection;
bool gameOver = false;
int score = 0;

void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	glColor3f(1.0,0.0,0.0);
	glutSwapBuffers();
	if(gameOver){
        char _score[5];
        itoa(score,_score,5);
        char text[50] = "Your Score: ";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER",0);
        exit(0);
	}
}
void initialize() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	initGrid(COLUMNS,ROWS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
void reshape_callback(int w,int h) {
	glViewport(0,0,(GLsizei)w, (GLsizei)h);

}
void timer_callback(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}
void key_callback(int key,int,int){
    switch(key){
        case GLUT_KEY_UP:
            if(sDirection != DOWN)
                sDirection = UP;
            break;
        case GLUT_KEY_DOWN:
            if(sDirection != UP)
                sDirection = DOWN;
            break;
        case GLUT_KEY_RIGHT:
            if(sDirection != LEFT)
                sDirection = RIGHT;
            break;
        case GLUT_KEY_LEFT:
            if(sDirection != RIGHT)
                sDirection = LEFT;
            break;
    }
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutCreateWindow("SNAKE");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(key_callback);
	initialize();
	glutMainLoop();
	return 0;
}
