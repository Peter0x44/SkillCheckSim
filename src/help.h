#pragma once

#include "gamestates.h"
#include "globals.h"

class helpscreen: public gamestate
{
private:
	const Rectangle backbutton = { screenWidth - 50, screenHeight - 50, 50, 50 };
	bool backbuttonpressed = false;

public:
	void logic(void) final override;
	void render(void) final override;
	helpscreen(void);
	~helpscreen() final override;
};