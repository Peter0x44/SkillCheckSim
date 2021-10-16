#pragma once

#include "gamestates.h"
#include "globals.h"

class achievementscreen : public gamestate
{
private:
	Rectangle Backboard = { screenWidth / 2 - 375, screenHeight / 2 - 188, 750, 350 };
	//Rectangle Backboard = { screenWidth / 8, screenHeight / 40, screenWidth * (2/3), screenHeight * (2) };

	//const int AchievementNumber = 8;

	const char* achievements[8] = {
		"hit 10 great skill checks in a row",
		"miss 50 skillchecks in a row",
		"Hit 50 great skillchecks on veteran mode",
		"Miss 10 skillchecks in a row",
		"hit 50 greatskillchecks in a row on easy",
		"hit 200 great skill checks in a row",
		"hit 500 great skill checks overall",
		"???"
	};

public:
	void logic(void) final override;
	void render(void) final override;
	achievementscreen(void);
	~achievementscreen() final override;
};