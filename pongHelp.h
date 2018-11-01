#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "enum.h"
#include "player.h"
#include "ai.h"

//ball keeps track of its velocity placement and rally number
struct ball 
{ 
	SDL_Rect bpos;
	float x;
	float y;
	float xv;
	float yv;
	float speed;
	int rallyDig1 = 0;
	int rallyDig2 = 0;
};

struct Pong_Help
{
public:
	Pong_Help();
	Pong_Help(SDL_Renderer* r);
	~Pong_Help();

	// all of the necessary rectangles
	SDL_Rect p1scoreRect, bot1scoreRect, rallyRect, rallyDigit1, rallyDigit2, nameplace1, nameplace2, divRect;
	
	//ball constants
	const float MAX_ANGLE = 3.142 / 5.0; // 72 degrees
	const float BALL_MAXSPEED = 1.0f;
	const float BALL_ACCELERATE = 0.905f;
	const float BALL_INIT_SPEED = 6.5f;

	//most widely used functions
	void backgroundDraw(SDL_Renderer* r);
	void dividerAndNameDraw(SDL_Renderer* r);
	void mainEntitiesDraw(SDL_Renderer* r);
	void scoreDraw(SDL_Renderer* r);
	void scoreManage();
	void drawWholeBoard(SDL_Renderer* r);
	void ballVeloManage();
	float calc_angle(float y1, float y2, int height);
	void boundary();

	//objects needed for a game
	diffHelp a;
	player p1;
	player bot1;
	ball b;

private:
	//init functions
	void clean_up();
	void scoreRectInit();
	void playersRectInit();
	void ballRectInit();
	void dividerInit(SDL_Renderer* r);

	//textures
	SDL_Texture* div_tx;
	SDL_Texture* p1_namet;
	SDL_Texture* rally_tx;
	SDL_Texture* p2_namet;
};

