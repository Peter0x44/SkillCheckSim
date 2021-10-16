#pragma once

#include "gamestates.h"
#include "globals.h"

class modesscreen: public gamestate
{
private:
	Rectangle Backboard = { screenWidth / 2 - 375, screenHeight / 2 - 188, 750, 350 };

public:
	void logic(void) final override;
	void render(void) final override;
	modesscreen(void);
	~modesscreen() final override;
};
