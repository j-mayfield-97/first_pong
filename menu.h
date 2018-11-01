#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "enum.h"
//FOR SOME REASON This has access to main's renderer - ren
//get all logic of menu into this class
struct MenuStruct
{
	MenuStruct();
	MenuStruct(SDL_Renderer *r);
	void texture_wipe();
	void EHswap(SDL_Renderer* r);
	void ren_copies(SDL_Renderer* r);
	void hovering(SDL_Renderer* r);

	SDL_Rect menuingRect = SDL_Rect();
	SDL_Rect difficulty = SDL_Rect(); //on and off button style load easy and hard
	SDL_Rect opt = SDL_Rect(); // opt cahnges to opt window where you pick bot or player side by side
	SDL_Rect player = SDL_Rect();
	SDL_Rect bot = SDL_Rect();
	SDL_Rect quit = SDL_Rect();
	SDL_Rect* currentRect = &SDL_Rect();

private:
	SDL_Texture* menutx;
	SDL_Texture* overtx ;
	SDL_Texture* hovertx;
	SDL_Texture* difftx;
	SDL_Texture* opttx;
	SDL_Texture* playertx;
	SDL_Texture* bottx;
	SDL_Texture* quittx;

//for swaping easy and hard tiles
	int EHswapCheck = 1;
};

MenuStruct::MenuStruct() 
{ 
}

MenuStruct::MenuStruct(SDL_Renderer* r)
{
	//Menu Sign at top
	menuingRect.h = screenHeight / 4;
	menuingRect.w = screenWidth / 2;
	menuingRect.x = screenWidth / 4;
	menuingRect.y = 10;

	//option and player are not operational 
	opt.h = screenHeight / 5;
	//opt.w = screenWidth / 2;
	opt.x = screenWidth / 4;
	opt.y = menuingRect.h + menuingRect.y + 5;

	player.h = screenHeight / 5;
	//player.w = screenWidth / 5;
	player.x = opt.x - player.w - 5;
	player.y = opt.y;

	bot.h = screenHeight / 5;
	bot.w = screenWidth / 5;
	bot.x = opt.x + opt.w + 5;
	bot.y = opt.y;

	difficulty.h = screenHeight / 5;
	difficulty.w = screenWidth / 2;
	difficulty.x = screenWidth / 4;
	difficulty.y = opt.h + opt.y + 5;

	quit.h = screenHeight / 3;
	quit.w = screenWidth / 2;
	quit.x = screenWidth / 4;
	quit.y = difficulty.h + difficulty.y + 5;

	menutx = IMG_LoadTexture(r, "assets/menu.png");
	overtx = IMG_LoadTexture(r, "assets/redOverlay.png");
	hovertx = IMG_LoadTexture(r, "assets/blueOverlay.png");
	opttx = IMG_LoadTexture(r, "assets/menuOpt.png");
	difftx = IMG_LoadTexture(r, "assets/menuEasy.png");// i technically dont have to load it here , if i run the ehswap(), would it be better to not do unnecessary loads or not do unnecessary calls
	playertx = IMG_LoadTexture(r, "assets/menuPlayer.png");
	bottx = IMG_LoadTexture(r, "assets/menuBot.png");
	quittx  = IMG_LoadTexture(r, "assets/menuQuit.png");
}

//clean the textures
void MenuStruct::texture_wipe()
{
	SDL_DestroyTexture(menutx);
	SDL_DestroyTexture(overtx);
	SDL_DestroyTexture(hovertx);
	SDL_DestroyTexture(difftx);
	SDL_DestroyTexture(opttx);
	SDL_DestroyTexture(playertx);
	SDL_DestroyTexture(bottx);
	SDL_DestroyTexture(quittx);
}

void MenuStruct::EHswap(SDL_Renderer* r) 
{
	EHswapCheck *= -1;// keeps track of difficulty setting
	SDL_DestroyTexture(difftx);//prevent the leaks
	if (EHswapCheck < 0){ difftx = IMG_LoadTexture(r, "assets/menuHard.png"); }
	else{ difftx = IMG_LoadTexture(r, "assets/menuEasy.png"); }
	
}

void MenuStruct::hovering(SDL_Renderer * r) // maybe just pass a rect adress instead to set current rect
{
	SDL_RenderCopy(r, hovertx, NULL, currentRect);
}

void MenuStruct::ren_copies(SDL_Renderer* r)
{
	hovering(r);

	SDL_RenderCopy(r, overtx, NULL, &menuingRect);
	//SDL_RenderCopy(r, overtx, NULL, &opt);
	SDL_RenderCopy(r, overtx, NULL, &player);
	SDL_RenderCopy(r, overtx, NULL, &bot);
	SDL_RenderCopy(r, overtx, NULL, &difficulty);
	SDL_RenderCopy(r, overtx, NULL, &quit);

	SDL_RenderCopy(r, menutx, NULL, &menuingRect);
	SDL_RenderCopy(r, opttx, NULL, &opt);
	SDL_RenderCopy(r, playertx, NULL, &player);
	SDL_RenderCopy(r, bottx, NULL, &bot);
	SDL_RenderCopy(r, difftx, NULL, &difficulty); //make it run on swaptx
	SDL_RenderCopy(r, quittx, NULL, &quit);
}