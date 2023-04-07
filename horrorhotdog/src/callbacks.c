#include "callbacks.h"

#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

#pragma GCC diagnostic ignored "-Wunused-parameter"


struct {
    int x;
    int y;
} mouse_position;

int fogEnabled = 1;

int drawHelp = 0;
unsigned char helpText[] = "Goal: Find the hot-dog!\n\nControls\n-----\nUse the WASD keys to move.\nHold down LMB then use the mouse to look around.\n\n+: Increase lighting intensity\n-: Decrease lighting intensity\nF1: Toggle help\nEsc: Exit game";

int drawInitial = 1;
unsigned char initialText[] = "Find the hot-dog!";

int drawFinal = 0;
unsigned char finalText[] = "      You Win!\n Press Esc to quit.";

void UpdateDrawFinalVariable()
{
	drawFinal = 1;
}

void display()
{
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();
	
	if (drawInitial)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_FOG);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();		
		glRasterPos2f(-0.1f, 0.7f);	
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, initialText);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		if (fogEnabled)
			glEnable(GL_FOG);		
	}	
	
	if (drawFinal)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_FOG);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();		
		glRasterPos2f(-0.1f, 0.7f);	
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, finalText);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		if (fogEnabled)
			glEnable(GL_FOG);		
	}
	
	if (drawHelp)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_FOG);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();		
		glRasterPos2f(-0.99f, 0.9f);		
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, helpText);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		if (fogEnabled)
			glEnable(GL_FOG);
	}	
	
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

int lmbDown = 0;
void mouse(int button, int state, int x, int y)
{
	
	if (button == 0) 
	{
		lmbDown = !lmbDown;
	}
	mouse_position.x = x;
	mouse_position.y = y;
}

void motion(int x, int y)
{	
	if (lmbDown)
	{
		rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
		mouse_position.x = x;
		mouse_position.y = y;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	drawInitial = 0;
    switch (key) {
    case 'w':
		if(!drawFinal)
        set_camera_speed(&camera, 4);
        break;
    case 's':
		if(!drawFinal)
        set_camera_speed(&camera, -4);
        break;
    case 'a':
		if(!drawFinal)
        set_camera_side_speed(&camera, 4);
        break;
    case 'd':
		if(!drawFinal)
        set_camera_side_speed(&camera, -4);
        break;
	case '+':
		set_lighting(0.2f,0.2f,0.2f,0.0f);
		break;
	case '-':
		set_lighting(-0.2f,-0.2f,-0.2f,0.0f);
		break;
	case 27: // Escape
		exit(0);
		break;
    }
    glutPostRedisplay();
}

void keyboard_special(int key, int x, int y)
{
	drawInitial = 0;
	switch(key){
	case GLUT_KEY_F1:
		drawHelp = !drawHelp;
		break;
	}
	glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);
	
    glutPostRedisplay();
}
