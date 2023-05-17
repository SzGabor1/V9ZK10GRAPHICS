#ifndef SCENE_H
#define SCENE_H
#include "sword.h"

#include "camera.h"
#include "texture.h"
#include <obj/model.h>
#include <math.h>

typedef struct Scene
{

    Material material;

    Model gorund;
    GLuint ground_texture_id;

    Model skybox;
    GLuint skybox_texture_id;

    Model penguin;
    GLuint penguin_texture_id;

    GLuint help_texture_id;
    int showHelp;

    float light;
    GLuint end_textrue_id;
    GLuint hp_1_texture_id;
    GLuint hp_2_texture_id;
    GLuint hp_3_texture_id;

    Sword sword;

    float fogstrength;
    float fogposition;
    float fogdirection;

} Scene;

void init_scene(Scene *scene);

void set_lighting(float x);

void set_material(const Material *material);

void update_scene(Scene *scene);

void render_scene(const Scene *scene);

void draw_origin();

void help(GLuint texture);

#endif
