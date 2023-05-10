
#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{

    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.25);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    load_model(&(scene->gorund), "assets/models/ground.obj");
    scene->ground_texture_id = load_texture("assets/textures/ground.jpg");

    load_model(&(scene->penguin), "assets/models/snowman.obj");
    scene->penguin_texture_id = load_texture("assets/textures/snow.jfif");

    load_model(&(scene->skybox), "assets/models/skybox.obj");
    scene->skybox_texture_id = load_texture("assets/textures/sky.jfif");

    scene->help_texture_id = load_texture("assets/textures/help_texture.jpg");
    scene->end_textrue_id = load_texture("assets/textures/gameover.jpg");

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->light = 1.0f;

    scene->showHelp = 1;

    init_sword(&(scene->sword));
}

void set_lighting(float x)
{
    float ambient_light[] = {x, x, x, 1.0f};
    float diffuse_light[] = {x, x, x, 1.0f};
    float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float position[] = {0.0f, 0.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    set_lighting(scene->light);
}

void render_scene(const Scene *scene)
{

    // ground
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->gorund));
    glPopMatrix();

    // skybox
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture_id);
    glRotated(90, 1, 0, 0);
    draw_model(&(scene->skybox));
    glPopMatrix();

    // snowman
    glColor3f(1, 1, 1);
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    // set_material(&(scene->sword.sword_material));
    glBindTexture(GL_TEXTURE_2D, scene->penguin_texture_id);
    glRotated(90, 1, 0, 0);
    glTranslatef(1, 0, 1);
    draw_model(&(scene->penguin));
    glPopMatrix();

    // sword

    glPushMatrix();
    glVertex3f(0.5, -2.5, 1);
    glTranslatef(0.5, scene->sword.sword_y, 1);
    glScalef(0.5, 0.5, 0.5);
    set_material(&(scene->sword.sword_material));
    // glBindTexture(GL_TEXTURE_2D, scene->sword.sword_texture_id);
    glRotated(0, 1, 0, 0);
    draw_model(&(scene->sword.sword));
    glPopMatrix();

    health(&(scene->sword));

    if (scene->sword.stab_count > 2)
    {
        help(scene->end_textrue_id);
    }
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void help(GLuint texture)
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}
