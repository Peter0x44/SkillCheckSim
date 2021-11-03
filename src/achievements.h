#pragma once

#include "gamestates.h"
#include "globals.h"
#include "skillcheck.h"

class achievementscreen : public gamestate
{
private:
	stats scores;
	Rectangle Backboard = { screenWidth / 2 - 375, screenHeight / 2 - 188, 750, 350 };

	const char* const achievementCondition[16] = {
		"Get 7000 Bloodpoints",
		"Get 32000 Bloodpoints",
		"Hit 50 great skill checks",
		"Hit 100 great skill checks",
		"Hit 500 great skill checks",
		"Fail 50 skill checks",
		"Fail 100 skill checks",
		"Fail 500 skill checks",
		"Fail 1000 skill checks",
		"Hit 5 great skill checks in a row",
		"Hit 10 great skill checks in a row ",
		"Play 1000 skill checks",
		"Play 2000 skill checks",
		"Play 3000 skill checks ",
		"Play 5000 skill checks",
		"???"
	};

	const char* const achievementTitle[16] = {
		"You pip'd so you had fun",
		"Farming : MAX",
		"Level up",
		"Trust me",
		"I'm a engineer",
		"Brand New Dwight",
		"Blame the lag",
		"Well deserved facecamp",
		"-rep Please uninstall",
		"Not even immersed",
		"Best player in the world",
		"Now play the actual game",
		"What in tarnation?",
		"Infinite abuser",
		"Esport ready",
		"Blame Mclean",
	};

	const Rectangle backbutton = { screenWidth - 50, screenHeight - 50, 50, 50 }; //BACK BUTTON IS DRAWN
	bool backbuttonpressed = false; 

	bool boolforachievements[16] = {
		false
	};

	const int gridOffsetX = (screenWidth - 68 * 7) / 2;
	const int gridOffsetY = 55;
	int achievementshoveredx;
	int achievementshoveredy;

	int letterpressed = 0;

public:
	void logic(void) final override;
	void render(void) final override;
	achievementscreen(void);
	~achievementscreen() final override;
};
