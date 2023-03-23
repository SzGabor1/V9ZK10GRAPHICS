#include "scene.h"
#include "glutcallbacks.h"
#include "camera.h"
#define MAX_VIRUS 20
#define VIRUS_LIFE 0 
#define VIRUS_SPEED 1.0f

struct particle virus[MAX_VIRUS];
GLfloat material1[] = { 0.4f, 0.6f, 0.4f, 0.6f };
GLfloat material2[] = { 0.4f, 0.4f, 0.8f, 0.3f };
GLfloat full_mat[] = { 1, 1, 1, 1 };
GLfloat no_mat[] = { 0, 0, 0, 0 };
GLfloat material_shininess[] = { 16.0 };

float currentLightStrength = 0.6f;
void set_lightings(float value)
{
	if (value == -1) currentLightStrength = 0.6f;
	else {
		if (((currentLightStrength + value) <= 1) && ((currentLightStrength + value) >= 0)) 
		currentLightStrength += value;
	}
	GLfloat light_position[] = { 0.0, 0.4f, 2, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat light_ambient[] = { currentLightStrength, currentLightStrength, currentLightStrength, 0 };
	GLfloat light_diffuse[] = { 0.7f, 0.3f, 0.2f, 0 };
	GLfloat light_specular[] = { currentLightStrength, currentLightStrength, currentLightStrength, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glClearColor(currentLightStrength, currentLightStrength, currentLightStrength + 0.2f, 1.0);
}

void initialize()
{
	toggleHelp = FALSE;
	toggleAttack = FALSE;
	attackTimer = 0;
	int i;
	srand(time(NULL));
	/*virus objektumok véletlenszerû koordinátáinak elõállítása*/
	float startZ = 10;
	for (i = 0; i < MAX_VIRUS; i++) {
		virus[i].x = (rand() % 10 - 1)-6;
		virus[i].y = (rand() % 12 - 1)-4;
		virus[i].z = rand() % 15 + startZ;
	}

	action.move_forward = FALSE;
	action.move_backward = FALSE;
	action.step_left = FALSE;
	action.step_right = FALSE;

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glClearColor(1, 1, 1, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearDepth(1.0);
	glEnable(GL_TEXTURE_2D);
	initialize_texture();
	gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 1000.0);
	glMatrixMode(GL_PROJECTION);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	set_lightings(-1);
}

void showHelp() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, modelData[4].texID);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(0, SCREEN_HEIGHT, 0);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(SCREEN_WIDTH, 0, 0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void drawObjectAbsolute(int modelNumber, float x, float y, float z, float scale) 
{
	glBindTexture(GL_TEXTURE_2D, modelData[modelNumber].texID);
	glPushMatrix();
	glScalef(scale, scale, scale);
	glTranslatef(x, y, z);
	glRotatef(90, 1, 0, 0);
	draw_model(&model[modelNumber]);
	glTranslatef(-x, -y, -z);
	glPopMatrix();
}

//Thor kalapács animáció
void drawAnimatedHammer(double elapsed_time) {
	glBindTexture(GL_TEXTURE_2D, modelData[3].texID);
	glPushMatrix();
	glTranslatef(camera.position.x, camera.position.y, camera.position.z);
	glRotatef(90, 1, 0, 0);
	glRotatef(camera.pose.z + 105, 0, 1, 0);
	glRotatef(-camera.pose.x, 1, 0, 0);
	glTranslatef(0.05, -.5f, -0.05);
	if (toggleAttack == TRUE) {
		attackTimer += 4 * elapsed_time;
		if (attackTimer > 1) {
			toggleAttack = FALSE;
		}
	}
	else {
		if (attackTimer > 0) attackTimer -= 4 * elapsed_time;
	}
	glRotatef(attackTimer * 45, 1, 0.2, 0);
	draw_model(&model[3]);
	glPopMatrix();
}

void draw_scene(double elapsed_time)
{
	/*help text*/
	if (toggleHelp == TRUE)
	{
		showHelp();
		return;
	}
	
	/*szoba*/
	drawObjectAbsolute(2, 0, 0, 0, 1);

	/*Pingvin obj elhelyezése*/
	drawObjectAbsolute(1, -1, 1, 0, 1); //x,y,z -2,2,0
	
	/*Thor kalapácsa*/
	drawAnimatedHammer(elapsed_time);

	/*virus sejtek kirajzolása*/
	int i;
	/*minden második vírus sejt más szín*/ 
	for (i = 0; i < MAX_VIRUS; i++) {
		if (i % 2 == 0) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material1);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material1);
		}
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material2);
		}
		virus[i].z -= VIRUS_SPEED * elapsed_time; 
		if (virus[i].z<VIRUS_LIFE) { virus[i].z = rand() % 15 + 5; }
		drawObjectAbsolute(0, virus[i].x, virus[i].y, virus[i].z, 0.35f);
	}
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, full_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, full_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, full_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

}
