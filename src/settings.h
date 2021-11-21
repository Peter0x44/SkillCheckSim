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
	const Rectangle changebackground = { 44, 120, 250, 50 };
	
	bool backbuttonpressed = false;
	bool disablesoundpressed = false;
	bool disablesounds = false;
	bool changebackgroundpressed = false;
	bool lol = false;
	
	const char* const messages[2] = {"sound enabled", "sound disabled"};
	const char* const messages2[3] = { "BG 1", "BG 2"};

public:
	void logic(void) final override;
	void render(void) final override;
	settingsscreen(void);
	~settingsscreen() final override;
};