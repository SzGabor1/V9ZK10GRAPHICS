#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct
{
    float x, y, z; // csepp pozíciója
    float speed;   // csepp sebessége
} Drop;

typedef struct Scene
{

    Material material;

    Model gorund;
    GLuint ground_texture_id;

    Model skybox;
    GLuint skybox_texture_id;

    Model sword;
    GLuint sword_texture_id;

    Model penguin;
    GLuint penguin_texture_id;

    float sword_y;
    float light;

    GLuint help_texture_id;

    int showHelp;

    int stab_count;
    int sword_pulled_out;
    GLuint end_textrue_id;

} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float x);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void help(GLuint texture);

#endif /* SCENE_H */
