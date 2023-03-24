#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
	vec3 rotationSpeed;
} Camera;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, double time);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera* camera, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_camera_side_speed(Camera* camera, double speed);

void set_camera_vert_speed(Camera* camera, double speed);

void set_camera_rotation_speed_x(Camera* camera, double speed);

void set_camera_rotation_speed_y(Camera* camera, double speed);

void set_camera_rotation_speed_z(Camera* camera, double speed);

#endif /* CAMERA_H */

