#include "sword.h"

void init_sword(Sword *sword)
{
    load_model(&(sword->sword), "assets/models/sword.obj");
    sword->sword_texture_id = load_texture("assets/textures/sword.jpg");
    sword->hp_3_texture_id = load_texture("assets/textures/h3.jpg");
    sword->hp_2_texture_id = load_texture("assets/textures/h2.jpg");
    sword->hp_1_texture_id = load_texture("assets/textures/h1.jpg");
    sword->hp_0_texture_id = load_texture("assets/textures/h0.jpg");
    sword->sword_y = -2.5f;
    sword->stab_count = 0;
    sword->speed.y = 0;
    sword->sword_pulled_out = 1;
}

void health(Sword *sword)
{
    GLuint health = sword->hp_3_texture_id;
    if (sword->stab_count == 1)
    {
        health = sword->hp_2_texture_id;
    }
    else if (sword->stab_count == 2)
    {
        health = sword->hp_1_texture_id;
    }
    else if (sword->stab_count > 3)
    {
        health = sword->hp_0_texture_id;
    }

    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, health);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(1.2, 1.375, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2.2, 1.375, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2.2, 0.625, -3);
    glTexCoord2f(0, 1);
    glVertex3d(1.2, 0.625, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}