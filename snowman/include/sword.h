#ifndef SWORD_H

#define SWORD_H

#include "camera.h"
#include "texture.h"
#include <math.h>
#include <obj/model.h>

typedef struct Sword
{

    Model sword;
    GLuint sword_texture_id;
    GLuint health_texture_id;
    float sword_y;
    int stab_count;
    int sword_pulled_out;

} Sword;

void init_sword(Sword *sword);

void health(Sword *sword);

#endif