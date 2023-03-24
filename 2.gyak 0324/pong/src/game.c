#include "game.h"

void resize_game(Game* game, int width, int height)
{
    game->width = width;
    game->height = height;
    game->left_pad.size = 200;
    game->right_pad.size = 200;
	game->leftPoints = 0;
	game->rightPoints = 0;
    restart_game(game);
}

void restart_game(Game* game)
{
    float center_x;
    float center_y;

    center_x = game->width / 2;
    center_y = game->height / 2;

    move_pad(&(game->left_pad), center_y, game->height);
    move_pad(&(game->right_pad), center_y, game->height);
    start_ball(&(game->ball), center_x, center_y);
}

void update_game(Game* game, double time)
{

    update_ball(&(game->ball), time);
    if (game->ball.x - game->ball.radius < 50) {	
	
		int lowerBound = game->left_pad.position + (game->left_pad.size);
		int upperBound = game->left_pad.position;
		int ballWithSize = game->ball.y - game->ball.radius;
		
		if (((ballWithSize) > upperBound) && (ballWithSize < lowerBound)) 
		{

			game->ball.x = game->ball.radius + 50;
			game->ball.speed_x *= -1;
		}
		else
		{
			game->rightPoints += 1;
			restart_game(game);			
		}
				
    }

    if (game->ball.x + game->ball.radius > game->width - 50) {
		
		int lowerBound = game->right_pad.position + (game->right_pad.size);
		int upperBound = game->right_pad.position;
		int ballWithSize = game->ball.y - game->ball.radius;
		
		if (((ballWithSize) > upperBound) && (ballWithSize < lowerBound)) 
		{

			game->ball.x = game->width - game->ball.radius - 50;
			game->ball.speed_x *= -1;
		}
		else
		{
			game->leftPoints += 1;
			restart_game(game);	
		}
		
    }
    if (game->ball.y - game->ball.radius < 0) {
        game->ball.y = game->ball.radius;
        game->ball.speed_y *= -1;
    }
    if (game->ball.y + game->ball.radius > game->height) {
        game->ball.y = game->height - game->ball.radius;
        game->ball.speed_y *= -1;
    }
}

void move_left_pad(Game* game, float position)
{
    move_pad(&(game->left_pad), position, game->height);
}

void move_right_pad(Game* game, float position)
{
    move_pad(&(game->right_pad), position, game->height);
}

