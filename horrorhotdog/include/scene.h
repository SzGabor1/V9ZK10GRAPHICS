#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model fattree;
	Model hotdog;
	
    GLuint texture_id_ground;
	GLuint texture_id_fattree;
	GLuint texture_id_hotdog;
	GLuint texture_id_wall;
	GLuint texture_id_water;
	
} Scene;

/* Scene initialization */
void init_scene(Scene* scene);

/* Set scene lighting */
void set_lighting(float r, float g, float b, float a);

/* Draw scene objects */
void draw_scene(const Scene* scene);

/* Draw ground */
void draw_ground(const Scene* scene);

/* Draw walls */
void draw_walls(const Scene* scene);

/* Draw water */
void draw_water(const Scene* scene);

#endif /* SCENE_H */
