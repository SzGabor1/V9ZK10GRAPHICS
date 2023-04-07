#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

#include <math.h>


struct 
{
	float oldR;
	float oldG;
	float oldB;
	float oldA;
} diffuseLight;

/* variables for water */
float waterPoints[45][45][3];
int wiggleCount = 0;
float hold;

void init_scene(Scene* scene)
{	

	load_model(&(scene->hotdog), "data/hotdog.obj");  
	load_model(&(scene->fattree), "data/fattree.obj");
	
    scene->texture_id_ground = load_texture("data/grass.jpg"); 
	scene->texture_id_fattree = load_texture("data/fattree.png");
	scene->texture_id_wall = load_texture("data/wall.jpg");
	scene->texture_id_water = load_texture("data/water.jpg");
	
	scene->texture_id_hotdog = load_texture("data/hotdog.png");



	diffuseLight.oldR = 0.8f;
	diffuseLight.oldG = 0.8f;
	diffuseLight.oldB = 0.8f;
	diffuseLight.oldA = 1.0f;
	
	// init water points
	int x, y;
	for (x=0; x<45; x++)
	{
		for (y=0; y<45; y++)
		{
			waterPoints[x][y][0]= (x/5.0f)-4.5f;
			waterPoints[x][y][1]= (y/5.0f)-4.5f;
			waterPoints[x][y][2]= sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f);
		}
		
	}
}

float ConstrainValue(float val)
{
	if (val > 10.0f)
	{
		val = 10.0f;
	}
	else if (val < 0.0f)
	{
		val = 0.0f;
	}
	return val;	
}

void set_lighting(float r, float g, float b, float a)
{
 	diffuseLight.oldR = ConstrainValue(diffuseLight.oldR + r);
	diffuseLight.oldG = ConstrainValue(diffuseLight.oldG + g);
	diffuseLight.oldB = ConstrainValue(diffuseLight.oldB + b);
	diffuseLight.oldA = ConstrainValue(diffuseLight.oldA + a);		
	
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { diffuseLight.oldR, diffuseLight.oldG, diffuseLight.oldB, diffuseLight.oldA};
    float specular_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float position[] = { 0.0f, 0.0f, 50.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void draw_scene(const Scene* scene)
{	
	// Set lighting
    set_lighting(0.0f, 0.0f, 0.0f, 0.0f);
	
	// Draw ground
	draw_ground(scene);
	
	// Draw walls
	draw_walls(scene);
	
	// Draw model: fattree1
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_fattree);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	glTranslatef(35, 0, 25);
    draw_model(&(scene->fattree));
	glPopMatrix();	
	
	// Draw model: fattree2
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_fattree);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.1f);
	glTranslatef(-32, 0, 14);
    draw_model(&(scene->fattree));
	glPopMatrix();	
	
	// Draw model: Hotdog
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_hotdog);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(38,0,28);
	glScalef(0.3f, 0.3f, 0.3f);
    draw_model(&(scene->hotdog));
	glPopMatrix();	
	
	// Draw water
	draw_water(scene);
}

void draw_ground(const Scene* scene)
{
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_ground);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 50.0f);                   
		glVertex2i(-50.0f, 50.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(-50.0f, -50.0f);

		glTexCoord2f(50.0f, 0.0f);
		glVertex2i(50.0f, -50.0f);

		glTexCoord2f(50.0f, 50.0f);
		glVertex2i(50.0f, 50.0f);
	glEnd();	
}
void draw_walls(const Scene* scene)
{
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_wall);

	glPushMatrix();
	glRotatef(270, 1, 0, 0);
	glTranslatef(0, 0, -50);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 50.0f);                   
		glVertex2i(-50.0f, 50.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(-50.0f, -50.0f);

		glTexCoord2f(50.0f, 0.0f);
		glVertex2i(50.0f, -50.0f);

		glTexCoord2f(50.0f, 50.0f);
		glVertex2i(50.0f, 50.0f);
	glEnd();	
	glPopMatrix();	
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -50);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 50.0f);                   
		glVertex2i(-50.0f, 50.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(-50.0f, -50.0f);

		glTexCoord2f(50.0f, 0.0f);
		glVertex2i(50.0f, -50.0f);

		glTexCoord2f(50.0f, 50.0f);
		glVertex2i(50.0f, 50.0f);
	glEnd();	
	glPopMatrix();		
	
}

void draw_water(const Scene* scene)
{
    int x, y;         
    float float_x, float_y, float_xb, float_yb; 
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id_water);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0.0f,0.0f,-0.5f); 
	glScalef(50.0f, 50.0f, 0.5f);
	
	glBegin(GL_QUADS);          
	{
		for( x = 0; x < 44; x++ )        
		{
			for( y = 0; y < 44; y++ )      
			{	
				float_x = (x)/44.0f;  
				float_y = (y)/44.0f;  
				float_xb = (x+1)/44.0f;    
				float_yb = (y+1)/44.0f;   
				
				glTexCoord2f( float_x, float_y);   
				glVertex3f( waterPoints[x][y][0], waterPoints[x][y][1], waterPoints[x][y][2] );
				 
				glTexCoord2f( float_x, float_yb );  
				glVertex3f( waterPoints[x][y+1][0], waterPoints[x][y+1][1], waterPoints[x][y+1][2] );
				 
				glTexCoord2f( float_xb, float_yb ); 
				glVertex3f( waterPoints[x+1][y+1][0], waterPoints[x+1][y+1][1], waterPoints[x+1][y+1][2] );
				 
				glTexCoord2f( float_xb, float_y );  
				glVertex3f( waterPoints[x+1][y][0], waterPoints[x+1][y][1], waterPoints[x+1][y][2] );
			}
		}
	}
	glEnd();     
	
	if( wiggleCount == 10 )
	{
		for( y = 0; y < 45; y++ )
		{
			hold=waterPoints[0][y][2]; 
			for( x = 0; x < 44; x++) 
			{
				waterPoints[x][y][2] = waterPoints[x+1][y][2];
			}
			waterPoints[44][y][2]=hold;
		}
		wiggleCount = 0;
	}
	wiggleCount++;  
	
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

