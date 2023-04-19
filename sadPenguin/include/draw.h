#ifndef DRAW_H
#define DRAW_H
#include "model.h"
#include <GL/glut.h>

#include <stdio.h>
/**
 * Draw the model.
 */
void draw_model(const struct Model *model);

/**
 * Draw the triangles of the model.
 */
void draw_triangles(const struct Model *model);

/**
 * Draw the quads of the model.
 */
void draw_quads(const struct Model *model);

void drawEnd();

#endif // DRAW_H
