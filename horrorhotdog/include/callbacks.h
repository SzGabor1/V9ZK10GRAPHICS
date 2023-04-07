#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"

#include <GL/glut.h>

Scene scene;
Camera camera;

void display();
void reshape(GLsizei width, GLsizei height);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void idle();

void UpdateDrawFinalVariable();

#endif /* CALLBACKS_H */
