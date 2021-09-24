#pragma once

enum class gamestates
{
	skillcheckscreen, 
	achievements,
	null
};

struct gamestate
{
	virtual void logic(void) = 0;
	virtual void render(void) = 0;
	virtual ~gamestate() {};
};

void changestate(void);

void setnextstate(const gamestates newstate);