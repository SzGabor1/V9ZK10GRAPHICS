#include "ball.h"

void move_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void start_ball(Ball* ball, float x, float y)
{
    ball->radius = 50;
	ball->currentRotation = 0;
    move_ball(ball, x, y);
    ball->speed_x = 150;
    ball->speed_y = 150;
}

void update_ball(Ball* ball, double time)
{	
	int rotationSpeed = round(ball->speed_x);
	ball->currentRotation += rotationSpeed*time;
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
}

