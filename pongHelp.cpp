#include "pongHelp.h"
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
//The way menu handles the texture loading and destruction is more effiecient
//But thers a SDL problem preventing me from using that stucture
//you can have the compartmentalized textures load/destroy in separate functions and then call them
//with a "draw_all function"

//The msuic will load from here
Mix_Chunk *gScratch = NULL;

void Pong_Help::scoreRectInit()
{
	//Initialzie the rectangles for the digits and the scores 
	p1scoreRect = bot1scoreRect = rallyDigit1 = rallyDigit2 = SDL_Rect();

	//we want the scores to be square 
	p1scoreRect.h = bot1scoreRect.w = p1scoreRect.w = bot1scoreRect.h = 
	rallyDigit1.w = rallyDigit2.w = rallyDigit1.h = rallyDigit2.h = screenHeight / 25;

	p1scoreRect.y = bot1scoreRect.y = 20;
	p1scoreRect.x = screenWidth * 0.75;
	
	bot1scoreRect.x = screenWidth/4;
	p1.score = bot1.score = 0 ;

	rallyDigit1.y = rallyDigit2.y = screenHeight- rallyDigit1.h -20; 
	rallyDigit2.x = screenWidth / 4 ;
	rallyDigit1.x = rallyDigit2.x + rallyDigit2.w;
}
void Pong_Help::scoreDraw(SDL_Renderer * r)//this will make a string to get the path of the score png to load
{ //a for each loop would clean this up
	//
	std::string imgPath = "assets/";
	std::string a = std::to_string(p1.score); //turns score int into a string and sandwiches between path and extension
	const char* extension = "txt.png";

	std::string c = imgPath + a + extension;
	const char *C = c.c_str();

	std::string aa = std::to_string(bot1.score);

	std::string d = imgPath + aa + extension;
	const char *CC = d.c_str();

	std::string rallyS2 = std::to_string(b.rallyDig2);
	std::string rallyS1 = std::to_string(b.rallyDig1);

	std::string r2path = imgPath + rallyS2 + extension;
	const char *CCC = r2path.c_str();
	std::string r1path = imgPath + rallyS1 + extension;
	const char *CCCC = r1path.c_str();

	SDL_Texture *score2tx = IMG_LoadTexture(r, CC);
	SDL_Texture *score1tx = IMG_LoadTexture(r, C);
	SDL_Texture *r2tx = IMG_LoadTexture(r, CCC);
	SDL_Texture *r1tx = IMG_LoadTexture(r, CCCC);

	//std::cout << CCC << "/" << CCCC << std::endl;

	SDL_RenderCopy(r, score1tx, NULL, &p1scoreRect);
	SDL_RenderCopy(r, score2tx, NULL, &bot1scoreRect);
	SDL_RenderCopy(r, r2tx, NULL, &rallyDigit2);
	SDL_RenderCopy(r, r1tx, NULL, &rallyDigit1);

	SDL_DestroyTexture(score2tx);
	SDL_DestroyTexture(score1tx);
	SDL_DestroyTexture(r2tx);
	SDL_DestroyTexture(r1tx);
}
void Pong_Help::scoreManage()//puts ball back in the middle, in regular pong it serves from the player that lost
{

	if (b.x < p1.pos.x - 5)//moves the ball abck to the middle & ups score
	{
		b.x = p1.pos.x+p1.pos.w+2;
		b.y = p1.pos.y;
		b.speed = BALL_INIT_SPEED;
		b.xv = BALL_INIT_SPEED ;
		b.yv = (rand() % 2 == 0) ? BALL_INIT_SPEED : -1 * BALL_INIT_SPEED;
		b.rallyDig1 = b.rallyDig2 = 0;
		p1.score += 1;
		
	}
	if (b.x > bot1.pos.x + 5)
	{
		b.x = bot1.pos.x - b.bpos.w-2;
		b.y = bot1.pos.y;
		b.speed = BALL_INIT_SPEED;
		b.xv = -1 * BALL_INIT_SPEED;
		b.yv = (rand() % 2 == 0) ? BALL_INIT_SPEED : -1 * BALL_INIT_SPEED;
		b.rallyDig1 = b.rallyDig2 = 0;
		bot1.score += 1;
	}
	if (p1.score > 9 || bot1.score > 9)
	{
		p1.score = bot1.score = 0;
	}
	if (b.rallyDig2 >9)
	{
		b.rallyDig1 = b.rallyDig2 = 0;
	}
}


void Pong_Help::playersRectInit()
{
	p1.pos.h = screenHeight / 10;
	p1.pos.w = screenWidth / 100;
	p1.pos.x = 10;
	p1.pos.y = screenHeight / 2;
	p1.speed = screenHeight / 50;

	//p2 rect
	bot1.pos.h = screenHeight / 10;
	bot1.pos.w = screenWidth / 100;
	bot1.pos.x = screenWidth  - bot1.pos.w -10;
	bot1.pos.y = screenHeight / 2;
	bot1.speed = (screenHeight / 50 )- 3;
}
void Pong_Help::ballRectInit()
{
	//balls rect
	b.bpos.h = 10;
	b.bpos.w = 10;
	b.bpos.x =b.x = screenWidth / 2;
	b.bpos.y = b.y= screenHeight / 2;
	b.speed = BALL_INIT_SPEED;
	b.xv = (rand() % 2 == 0) ? BALL_INIT_SPEED : -1 * BALL_INIT_SPEED;
	b.yv = -0.5f;
}
void Pong_Help::backgroundDraw(SDL_Renderer * r)
{
	SDL_Texture * backtx = IMG_LoadTexture(r, "assets/pongback.png");
	SDL_RenderCopy(r, backtx, NULL, NULL);
	SDL_DestroyTexture(backtx);
}

void Pong_Help::mainEntitiesDraw(SDL_Renderer * r)
{
	SDL_Texture* sqtx = IMG_LoadTexture(r, "assets/pongpaddle.png");
	SDL_Texture* balltx = IMG_LoadTexture(r, "assets/pongball.png");
	div_tx = IMG_LoadTexture(r, "assets/squareWall.png");
	p1_namet = IMG_LoadTexture(r, "assets/p1txt.png");

	p2_namet = IMG_LoadTexture(r, "assets/p2txt.png");
	SDL_RenderCopy(r, sqtx, NULL, &p1.pos);
	SDL_RenderCopy(r, sqtx, NULL, &bot1.pos);
	SDL_RenderCopy(r, balltx, NULL, &b.bpos);
	SDL_DestroyTexture(balltx);
	SDL_DestroyTexture(sqtx);

}
void Pong_Help::dividerInit(SDL_Renderer* r)
{
	//load textures
	div_tx = IMG_LoadTexture(r, "assets/squareWall.png");
	p1_namet = IMG_LoadTexture(r, "assets/p1txt.png");
	p2_namet = IMG_LoadTexture(r, "assets/p2txt.png");

	//constant libarary problem happening here
	//problem with renderer
	std::cout << SDL_GetError() << std::endl;


	//init the rectangles for divider and rally count
	nameplace2 = SDL_Rect();
	divRect = SDL_Rect();
	rallyRect = SDL_Rect();

	nameplace1.h = nameplace2.h = rallyRect.h = screenHeight / 12;
	nameplace1.w = nameplace2.w = rallyRect.w = screenWidth / 8;
	nameplace1.x = rallyRect.x = screenWidth / 8;
	nameplace2.x = screenWidth / 1.6;
	nameplace1.y = nameplace2.y = 20;

	rallyRect.y = screenHeight - rallyRect.h - 20;

	divRect.h = screenHeight;
	divRect.w = 5;
	divRect.x = screenWidth / 2;
	divRect.y = 0;
}

void Pong_Help::dividerAndNameDraw(SDL_Renderer* r)// this function exist in this form because of debugging
{
	SDL_RenderCopy(r, p1_namet, NULL, &nameplace1);
	SDL_RenderCopy(r, p2_namet, NULL, &nameplace2);
	SDL_RenderCopy(r, div_tx, NULL, &divRect);
	SDL_RenderCopy(r, rally_tx, NULL, &rallyRect);
}

void Pong_Help::drawWholeBoard(SDL_Renderer* r)
{
	backgroundDraw(r);
	mainEntitiesDraw(r);
	scoreDraw(r);
	dividerAndNameDraw(r);
	
}

Pong_Help::Pong_Help()
{}

Pong_Help::Pong_Help(SDL_Renderer* r)
{ // call the init functions
	//start scores at zeero
	p1.score = bot1.score = 0;
	scoreRectInit();
	dividerInit(r);
	ballRectInit();
	playersRectInit();

	//load "rally texture"
	rally_tx = IMG_LoadTexture(r, "assets/rally.png");

	//load the music
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		//success = false;
	}
	gScratch = Mix_LoadWAV("low.wav");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

}

void Pong_Help::boundary() //keep players in boudary
{
	if (p1.pos.y < 0) p1.pos.y = 0;
	if (p1.pos.y + p1.pos.h > screenHeight) p1.pos.y = screenHeight - p1.pos.h;
	if (bot1.pos.y < 0) bot1.pos.y = 0;
	if (bot1.pos.y + bot1.pos.h > screenHeight) bot1.pos.y = screenHeight - bot1.pos.h;
}

float Pong_Help::calc_angle(float y1, float y2, int height) //find the angle of the ball
{
	float rely = y1 + height / 2 - y2;
	rely /= height / 2.0;   
	return rely * MAX_ANGLE;
}

void Pong_Help::ballVeloManage()
{

	//cap the max speed
	if (abs(b.xv) >= BALL_MAXSPEED)
	{
		b.xv = BALL_MAXSPEED;
	}
	if (abs(b.yv) >= BALL_MAXSPEED)
	{
		b.yv = BALL_MAXSPEED;
	}
	b.x += b.xv;
	b.y += b.yv;

	// Ball Boundary Collision
	if (b.y < 0) 
	{
		b.y = 0;
		b.yv *= -1;
	}
	if (b.y + b.bpos.h >= screenHeight) 
	{
		b.y = screenHeight - b.bpos.h - 1;
		b.yv *= -1;
	}
	//afix the rect to xy
	b.bpos.x = (int)b.x;
	b.bpos.y = (int)b.y;

	if (SDL_HasIntersection(&p1.pos, &b.bpos)) 
	{
		//music fir bounce
		Mix_PlayChannel(-1, gScratch, 0);
		
		//player & ball
		b.x = p1.pos.x + p1.pos.w;

		b.speed = b.speed * BALL_ACCELERATE;

		float angle = calc_angle(p1.pos.y, b.y, p1.pos.h);
		b.xv = b.speed * cos(angle);
		b.yv = ((b.yv>0) ? -1 : 1) * b.speed * sin(angle);
		b.rallyDig1 += 1;
	}
	if (SDL_HasIntersection(&bot1.pos, &b.bpos)) 
	{
		//bounce sound
		Mix_PlayChannel(-1, gScratch, 0);

		b.x = bot1.pos.x - b.bpos.w;

		b.speed = b.speed * BALL_ACCELERATE;

		//calculate angle of bounce and speed
		float angle = calc_angle(bot1.pos.y, b.y, bot1.pos.h);
		b.xv = -1 * b.speed * cos(angle);
		b.yv = ((b.yv>0) ? -1 : 1) * b.speed * sin(angle);
		b.rallyDig1 += 1;
	}
	//increment the second digit of the rally count and reset the first
	if (b.rallyDig1 > 9)
	{
		b.rallyDig1 = 0;
		b.rallyDig2 += 1;
	}
}
void Pong_Help::clean_up()
{
	SDL_DestroyTexture(p2_namet);//could result in a mem leak if rects have problem
	SDL_DestroyTexture(p1_namet);
	SDL_DestroyTexture(div_tx);
	SDL_DestroyTexture(rally_tx);
	Mix_FreeChunk(gScratch);
}
Pong_Help::~Pong_Help()
{
	clean_up();
}
