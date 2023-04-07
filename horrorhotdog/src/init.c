#include "init.h"

#include <GL/glut.h>

float fogDensity = 0.08f;
static float fog_color[] = {0.0, 0.0, 0.0, 1.0};

void init_opengl()
{
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glClearDepth(1.0);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, fogDensity);
	glFogfv(GL_FOG_COLOR, fog_color);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
