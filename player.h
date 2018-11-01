#pragma once
#include <SDL.h>
struct player
{
	player();
	SDL_Rect pos;// visible position 
	SDL_Rect top, mid, bottom;//the actual colliders for the ball
	int score, speed, mass;
};
