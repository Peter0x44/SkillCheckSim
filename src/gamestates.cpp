#include "gamestates.h"
#include "skillcheck.h"
#include "achievements.h"
#include "help.h"
#include "settings.h"

extern gamestate* currentstate;
extern gamestates stateid;
extern gamestates nextstate;

static inline void unreachable(void)
{
#if defined(_MSC_VER) && !defined(__clang__)
	__assume(false);
#else
	__builtin_unreachable();
#endif
}

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
			break;
		case gamestates::helpscreen:
			currentstate = new helpscreen();
			break;
		case gamestates::settingsscreen:
			currentstate = new settingsscreen();
			break;
		case gamestates::null:
			// silence warning
			unreachable();
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
