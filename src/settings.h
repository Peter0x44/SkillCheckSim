#pragma once
#include <raylib.h>

#include "gamestates.h"
#include "globals.h"

class settingsscreen : public gamestate
{
	
private:
	Rectangle Backboard = { screenWidth / 2 - 375, screenHeight / 2 - 188, 750, 350 };
	
	const Rectangle disablesoundsbutton = { 44, 65, 250, 50 };
	const Rectangle backbutton = { screenWidth - 50, screenHeight - 50, 50, 50 }; //BACK BUTTON DRAWN
	
	bool backbuttonpressed = false;
	bool disablesoundpressed = false;
	bool disablesounds = false;
	
	const char* const messages[2] = {"sound enabled", "sound disabled"};

public:
	void logic(void) final override;
	void render(void) final override;
	settingsscreen(void);
	~settingsscreen() final override;
};