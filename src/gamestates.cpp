#include "gamestates.h"
#include "skillcheck.h"
#include "achievements.h"
#include "help.h"

extern gamestate* currentstate;
extern gamestates stateid;
extern gamestates nextstate;

void changestate(void)
{
	if (nextstate != gamestates::null)
	{ 
		delete currentstate;
		
		switch (nextstate)
		{
		case gamestates::skillcheckscreen:
			currentstate = new skillcheckscreen();
			break;
		case gamestates::achievementsscreen:
			currentstate = new achievementscreen();
			break; //EACH NEW SCREEN, USING OOP
		case gamestates::helpscreen:
			currentstate = new helpscreen();
			break;
		}

		stateid = nextstate;
		nextstate = gamestates::null;
	}
}

void setnextstate(const gamestates newstate)
{
	nextstate = newstate;
}