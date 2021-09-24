#include "gamestates.h"
#include "skillcheck.h"

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
		}

		stateid = nextstate;
		nextstate = gamestates::null;
	}
}

void setnextstate(const gamestates newstate)
{
	nextstate = newstate;
}
