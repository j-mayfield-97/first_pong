#pragma once
// code used for reference written by Micheal Anquilla 
// and lazyfoo.net
#include <iostream>
#include <random>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "menu.h"
#include "pongHelp.h"
#include "ai.h"

//Creating very SDL pointers
SDL_Window* window ;
SDL_Renderer* ren ;
Mix_Music* gMusic = NULL;
TTF_Font* gFont = NULL;
SDL_Texture* mTexture = NULL;

void iconMake()//put this somewhere else?? 
{
	//icon making
	SDL_Surface* icon_surface = IMG_Load("assets/pongball.png");
	SDL_SetWindowIcon(window, icon_surface);
	SDL_FreeSurface(icon_surface);
}

void init()
{ //make the window
	window = SDL_CreateWindow("Pong_Test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth,screenHeight,SDL_WINDOW_SHOWN);
	
	if (window == NULL) 
	{ 
		std::cout << "window creation failed"<< std::endl; 
	}
	else
	{
		//make the renderer
		ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (ren == NULL)
		{
			std::cout << "renderer creation failed" << std::endl;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
			iconMake();//icon 
			
			//mouse cursor handling
			SDL_ShowCursor(SDL_DISABLE);
			//SDL_SetRelativeMouseMode(SDL_TRUE); // this should loc the mouse in place
		
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		//success = false;
	}
	TTF_Init();
	gFont = TTF_OpenFont("lazy.ttf", 30);
}

void loadFromRenderedText(std::string textureText)
{
	SDL_Color textColor = { 0, 0, 0 };

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(ren, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			int mWidth = screenWidth;
			int mHeight = screenHeight;
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}

void render_text(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

void render_text(int x, int y, SDL_Rect* clip , double angle, SDL_Point* center , SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 0, screenHeight / 2, screenWidth , screenHeight / 10 };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx(ren, mTexture, clip, &renderQuad, angle, center, flip);
}
void clean()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	Mix_FreeMusic(gMusic);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
//text for menu help
void tth_help()
{
	SDL_Rect renderQuad = { 0, screenHeight / 2, screenWidth , screenHeight / 10};
	SDL_Color textColor = { 100, 0, 150, 50 };
	SDL_Surface*  surf = TTF_RenderText_Blended(gFont, "M for menu   P for pause", textColor);
	SDL_Texture* textureTTF = SDL_CreateTextureFromSurface(ren, surf);
	SDL_RenderCopy(ren, textureTTF, NULL, &renderQuad);
}

//keep the game at 60fps
void fps()
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	frameStart = SDL_GetTicks();

	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime)
	{
		SDL_Delay(frameDelay - frameTime);
	}
}

void welcome()
{
	//simple wlcome and controls
	std::cout << "Welcome To Pong!" << std::endl;
	SDL_Texture* tx = IMG_LoadTexture(ren, "assets/welcome.png");
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tx, NULL, NULL);
	SDL_RenderPresent(ren);
	SDL_Delay(2500);
	SDL_DestroyTexture(tx);
}
void goodbye()
{
	std::cout << "Thanks for Playing. I Love You" <<std::endl;
}

bool pause(SDL_Event e,Pong_Help* pon)//menu has a cleaner structure
{
	SDL_Rect pausingRect = SDL_Rect();
	pausingRect.h = screenHeight / 3;
	pausingRect.w = screenWidth / 2;
	pausingRect.x = pausingRect.y = screenWidth/4;
	//if frame counter > 120 , load next one, >240, load next >360 framecount =0 
	//assuming it runs 60fps count should work
	
	bool ret =true;
	bool pausing = true;
	int counter = 0;

	SDL_Texture * tx0 = IMG_LoadTexture(ren, "assets/pause0.png");//make sure youre not loading unnecessarily
	SDL_Texture * tx1 = IMG_LoadTexture(ren, "assets/pause1.png");
	SDL_Texture * tx2 = IMG_LoadTexture(ren, "assets/pause2.png");
	SDL_Texture * overtx = IMG_LoadTexture(ren, "assets/blueOverlay.png");

	while (pausing)
	{
		fps();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				pausing = false;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					//end it all
					pausing = false; 
					ret = false;
					break;
				case SDL_SCANCODE_P:
					pausing = false;
				}
			}
			
		}

		SDL_RenderClear(ren);
		pon->backgroundDraw(ren);
		pon->mainEntitiesDraw(ren);
		SDL_RenderCopy(ren, overtx, NULL, &pausingRect);

		//should swap every sec
		if (counter <= 60 )
		{
			SDL_RenderCopy(ren, tx0, NULL, &pausingRect);
		}
		if (counter > 60 && counter < 120 )
		{
			SDL_RenderCopy(ren, tx1, NULL, &pausingRect);
		}
		if (counter>120 )
		{
			SDL_RenderCopy(ren, tx2, NULL, &pausingRect);
			if (counter > 180 ) { counter = 0; }//reset to zero
		}
		counter += 1;
		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(tx0);
	SDL_DestroyTexture(tx1);
	SDL_DestroyTexture(tx2);
	SDL_DestroyTexture(overtx);

	return ret;
}

bool menu(SDL_Event e,Pong_Help* pon) //pong _help has an event so it doesnt need to pass e
{
	bool ret = true;
	bool menuing = true;
	SDL_Point mousePos = SDL_Point();//point of the mouse
	int x = 0;
	int y = 0;

	//mouse becomes visible
	SDL_ShowCursor(SDL_ENABLE);
	MenuStruct menuObj = MenuStruct(ren);
	
	while (menuing)
	{
		SDL_RenderClear(ren);
		while (SDL_PollEvent(&e))
		{
			//find the mouse on the screen
			SDL_GetMouseState(&x, &y);
			mousePos.x = x;
			mousePos.y = y;
			
			if (e.type == SDL_QUIT)// quit condition
			{
				menuing = false;
				ret = false;
			}
			//scan on all input
			if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEMOTION|| e.type == SDL_MOUSEBUTTONUP)
			{				
				switch (e.key.keysym.scancode) 
				{
				case SDL_SCANCODE_ESCAPE:
					menuing = false; //end it all
					ret = false;
					break;
				}
				if (SDL_PointInRect(&mousePos, &menuObj.menuingRect))//hovering play button
				{
					menuObj.currentRect = &menuObj.menuingRect ;
					if (e.type == SDL_MOUSEBUTTONUP) { menuing = false; }
				}
				if (SDL_PointInRect(&mousePos, &menuObj.difficulty))//hovering difficulty
				{
					menuObj.currentRect = &menuObj.difficulty;
					if (e.type == SDL_MOUSEBUTTONUP) 
					{
						menuObj.EHswap(ren); 
						pon->a.difficultyCheck(&pon-> bot1);
					}
				}
				if (SDL_PointInRect(&mousePos, &menuObj.quit))//hovering quit
				{
					menuObj.currentRect = &menuObj.quit;
					if (e.type == SDL_MOUSEBUTTONUP) { menuing = false; ret = false; }
				}
			}
		}
		//rendering here only 
		pon->drawWholeBoard(ren);
		menuObj.ren_copies(ren);
		SDL_RenderPresent(ren);
	}
	menuObj.texture_wipe();
	SDL_ShowCursor(SDL_DISABLE);
	return ret;
}
void rescaling(SDL_Window* win, int*a, int*b) //lots of problems here 
{
	SDL_GetWindowSize(win, a, b);//doesnt seem possible to change const variables
	std::cout << SDL_GetError() << std::endl;
}

void ai(player * p, ball b) //moves slower than player , change speed for easy and hard
{
	if (p->pos.y + rand() % 2 > b.bpos.y) //move up
	{
		p->pos.y -= p->speed;
	}
	if (p->pos.y + (p->pos.h) + rand() % 2 < b.bpos.y) // move down
	{
		p->pos.y += p->speed;
	}
	
}

//the main loop
void gameLoop()
{
	//the main game object
	Pong_Help pon = Pong_Help(ren);

	bool running = true; //exit condition

	SDL_Event e; // control events

	//init the window renderer icon and music
	init();

	//main game music load
	gMusic = Mix_LoadMUS("eb_loop.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		//success = false;
	}
	Mix_PlayMusic(gMusic, -1);
	welcome();
	bool menuBuddy = true;
	//put a clickable start button to start the game 
	//make the menu button say "play" button instead
	while (running) 
	{
		fps();//limits frames to 60
		//rescaling(window,w, z); rescaling doesnt work at all
		bool pauseBuddy = false;

		pon.scoreManage();

		while (SDL_PollEvent(&e))//see if you can get this switch into a function somewhere else
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					goodbye();
					running = false; //end it all
					break;
				case SDL_SCANCODE_W:
					pon.p1.pos.y-=10; //move up
					break;
				case SDL_SCANCODE_S:
					pon.p1.pos.y += 10; //move down
					break;
				case SDL_SCANCODE_P:
					pauseBuddy = true; //pause
					break;
				case SDL_SCANCODE_M:
					menuBuddy = true; //menu
					break;
				case SDL_SCANCODE_SPACE: //random ball direction for testing
					pon.b.xv = (rand() % 2 == 0) ? 4 : -1 * 4;
					pon.b.yv = (rand() % 2 == 0) ? 4 : -1 * 4;
					break;
				}
			}
			
		}
		//basic ai
		ai(&pon.bot1, pon.b);

		//control ball and boundaries
		pon.ballVeloManage();
		pon.boundary();

		SDL_RenderClear(ren);
		//rendering goes first one is on bottom layer - to last on 
		//put all of these in a sep function so it keeps drawind Present scene, so you can have menu run render clear.	
		pon.drawWholeBoard(ren);
		tth_help();
		SDL_RenderPresent(ren);

		//conditions to leave the main game loop to other game loops
		if(pauseBuddy){ running = pause(e, &pon); }
		if (menuBuddy){ running = menu(e, &pon); }

		menuBuddy = false;// this is here to have a button to start
	}
	pon.~Pong_Help();
	clean();
}

int main(int argc,char* argv[])
{
	gameLoop();
	return 0;
}
