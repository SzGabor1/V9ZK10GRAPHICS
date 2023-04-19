#ifndef SCENE_H
#define SCENE_H
#define NUMBER_OF_MODELS 5
#include "camera.h"
#include <GL/glut.h>
#include <time.h>
#include "utils.h"
#include <math.h>
#include "glutcallbacks.h"
#include "camera.h"
#include "modelloader.h"
#define MAX_SNOW 20
#define SNOW_LIFE 0
#define SNOW_SPEED 1.0f

float attackTimer;
int toggleAttack;
int toggleHelp;
int GameEnd;

#define MAX_SNOW 20
#define SNOW_LIFE 0
#define SNOW_SPEED 1.0f

struct Model model[NUMBER_OF_MODELS];

struct ModelData
{
	char *textureFileName;
	char *objFileName;
	int texID;
} modelData[NUMBER_OF_MODELS];

struct particle
{
	GLfloat x, y, z;
};

/* Initializes key actions, camera and light setup */
void init_scene();

/* Shows menu texture */
void showHelp();

/* Sets the power of light by the given value */
void set_lightings(float lightPower);

/* Draws the scene */
void draw_scene(double elapsed_time);

/* Draws an object to absolute coordinates */
void drawObjectAbsolute(int modelNumber, float x, float y, float z, float scale);

/*Handles thor's animation and draws it*/
void drawAnimatedHammer();

void initialize();

#endif /* SCENE_H */
