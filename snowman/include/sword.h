#ifndef SWORD_H

#define SWORD_H

#include "utils.h"
#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

#include <obj/load.h>
#include <obj/draw.h>

typedef struct Sword
{

    vec3 speed;
    Model sword;
    GLuint sword_texture_id;
    GLuint hp_0_texture_id;
    GLuint hp_1_texture_id;
    GLuint hp_2_texture_id;
    GLuint hp_3_texture_id;
    float sword_y;
    int stab_count;
    int sword_pulled_out;

} Sword;

void init_sword(Sword *sword);

void health(Sword *sword);

#endif