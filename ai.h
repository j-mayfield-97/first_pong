#pragma once
#include "player.h"

//class to help change the diffuclty of bot
class diffHelp :
	public player
{
	bool difficult = true; // the first time this function is called it should make it difficult
	bool changed_previously = false;
	int originalSize;
	int originalSpeed; //keep the orignal speed iniitalized in pong_helper
public:
	diffHelp();
	~diffHelp();

	inline void difficultyCheck(player* bot)
	{
		if (!changed_previously)//best way to get it to save the original data only once without seperate funtions and parameters? 
		{
			originalSize = bot->pos.h;
			originalSpeed = bot->speed;
		}
		changed_previously = true;
		
		if (difficult) // the difficulty setting makes the bot larger and faster
		{
			bot->pos.h *= 4;
			bot->speed*=2;
		}
		else
		{
			
			bot->speed = originalSpeed;
			bot->pos.h = originalSize;
		}
		difficult = !difficult;
	}
};

