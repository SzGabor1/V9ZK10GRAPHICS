#ifndef UTILS_H
#define UTILS_H
#include "scene.h"
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * Calculates radian from degree.
 */
double degree_to_radian(double degree);

/*
Calculates elapsed time between frames
*/
int timer;
double calc_elapsed_time();

#endif /* UTILS_H */
