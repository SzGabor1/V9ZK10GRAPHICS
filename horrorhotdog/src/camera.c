#include "camera.h"
#include "callbacks.h"

#include <GL/glut.h>

#include <math.h>


void init_camera(Camera* camera)
{
    camera->worldPosition.x = 0.0;
    camera->worldPosition.y = 0.0;
    camera->worldPosition.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
	
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
	
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
//	int headBobYDirection;
	
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

	vec3 newPosition;
	newPosition.x = camera->worldPosition.x + cos(angle) * camera->speed.y * time;
	newPosition.y = camera->worldPosition.y + sin(angle) * camera->speed.y * time;
	newPosition.x += cos(side_angle) * camera->speed.x * time;
	newPosition.y += sin(side_angle) * camera->speed.x * time;
	
	if (check_collisions(newPosition) == 0)
	{	
		camera->worldPosition.x = newPosition.x;
		camera->worldPosition.y = newPosition.y;
	}
/*	
	if ((camera->position.z) > (camera->worldPosition.z + 1))
	{
		headBobYDirection = -1;
	}
	else if ((camera->position.z) < (camera->worldPosition.z -1))
	{
		headBobYDirection = 1;
	}
	*/
    camera->position.x = (camera->worldPosition.x);
    camera->position.y = (camera->worldPosition.y);
	camera->position.z = (camera->worldPosition.z);
//	camera->position.z = (camera->worldPosition.z) + ((camera->position.z+sin(camera->position.z))*(camera->speed.y));
//  camera->position.z = (camera->worldPosition.z) + (camera->speed.y*sin(camera->position.z));
	
//	printf("%f - %f\n", camera->position.z, camera->speed.y);

//	printf("x: %f, y: %f\n", camera->position.x, camera->position.y);

}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
	vertical *= 0.4;
	horizontal *= 0.4;
	
    camera->rotation.z += horizontal;
    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }
	if ((camera->rotation.x + vertical < 80) || (camera->rotation.x + vertical > 280))
	{
		camera->rotation.x += vertical;
		if (camera->rotation.x < 0) {
			camera->rotation.x += 360.0;
		}

		if (camera->rotation.x > 360.0) {
			camera->rotation.x -= 360.0;
		}
	}
}

void set_camera_speed(Camera* camera, double speed)
{
		camera->speed.y = speed;
}	

void set_camera_side_speed(Camera* camera, double speed)
{
		camera->speed.x = speed;
}

int check_collisions(vec3 newPosition)
{
//	printf("x: %f, y: %f, z: %f\n", newPosition.x, newPosition.y, newPosition.z);
	
	/* map Y edges */	
	if ((newPosition.y < -49) || (newPosition.y > 49))
		return 1;
	
	/* map X edges */
	if ((newPosition.x < -49) || (newPosition.x > 49))
		return 1;	
	
	/* fattree1
		posX: 17
		posY: -12.5
		boxSizeX: 3
		boxSizeY: 3
	*/
	if (calc_collision(newPosition, 17, -12.5, 3, 3) == 1)
		return 1;
	
	/* fattree2
		posX: -3.16
		posY: -1.3
		boxSizeX: 0.5
		boxSizeY: 0.5
	*/	
	if (calc_collision(newPosition, -3.16f, -1.3f, 0.5f, 0.5f) == 1)
		return 1;
	
	/* hotdog - win condition
		posX: 38.05
		posY: -27.9
		boxSizeX: 0.2
		boxSizeY: 0.2	
	*/
	if (calc_collision(newPosition, 38.05f, -27.9f, 0.2f, 0.2f) == 1)
	{
		glutMouseFunc(NULL);
		glutMotionFunc(NULL);
		glutKeyboardUpFunc(NULL);
		glutSpecialFunc(NULL);				
	
		UpdateDrawFinalVariable();
		
		return 1;
	}
	
	// No collision found
	return 0;
}

int calc_collision(vec3 newPosition, float posX, float posY, float boxSizeX, float boxSizeY)
{
	
	if ((newPosition.x > posX - boxSizeX) && (newPosition.x < posX + boxSizeX))
		if ((newPosition.y > posY - boxSizeY) && (newPosition.y < posY + boxSizeY))
			return 1;
	return 0;
	
}
