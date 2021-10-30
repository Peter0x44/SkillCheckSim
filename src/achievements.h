#pragma once

#include "gamestates.h"
#include "globals.h"
#include "skillcheck.h"

class achievementscreen : public gamestate
{
private:
	stats scores;
	Rectangle Backboard = { screenWidth / 2 - 375, screenHeight / 2 - 188, 750, 350 };
	//Rectangle Backboard = { screenWidth / 8, screenHeight / 40, screenWidth * (2/3), screenHeight * (2) };

	//const int AchievementNumber = 8;

	const char* const achievements[16] = {
		"hit 10 great skill checks in a row",
		"miss 50 skillchecks in a row",
		"Hit 50 great skillchecks",
		"Miss 10 skillchecks in a row", //ARRAY OF ACHIEVEMENTS
		"hit 50 greatskillchecks in a row",
		"hit 200 great skill checks in a row",
		"hit 500 great skill checks overall",
		"???"
	};

	const char* const achievementTitle[16] = {
		"You pip'd so you had fun: Get 7000 Bloodpoints",
		"Farming : MAX: Get 32000 Bloodpoints",
		"Level up: Hit 50 great skill checks",
		"Trust me: Hit 100 great skill checks",
		"I'm a engineer: Hit 500 great skill checks",
		"Brand New Dwight: Fail 50 skill checks",
		"Blame the lag: Fail 100 skill checks",
		"Well deserved facecamp: Fail 500 skill checks",
		"-rep Please uninstall: Fail 1000 skill checks",
		"Not even immersed: Hit 5 great skill checks in a row",
		"Best player in the world: Hit 10 great skill checks in a row ",
		"Now play the actual game: Play 1000 skill checks",
		"What in tarnation ?: Play 2000 skill checks",
		"Infinite abuser: Play 3000 skill checks ",
		"Esport ready: Play 5000 skill checks",
		"Blame Mclean: ???"
	};

	const Rectangle backbutton = { screenWidth - 50, screenHeight - 50, 50, 50 }; //BACK BUTTON IS DRAWN
	bool backbuttonpressed = false; 

	bool boolforachievements[16] = {
		false
	};

	//bool hit10skillchecksinarow = false;
	//bool miss50skillchecksinarow = false;
	//bool hit50greatskillchecks = false;
	//bool miss10skillchecksinarow = false;
	//bool hit50greatskillchecksinarow = false;
	//bool hit200greatskillchecksinarow = false;
	//bool hit500greatskillchecksoverall = false;
	//bool questionmark = false;

	const int gridOffsetX = (screenWidth - 68 * 7) / 2;
	const int gridOffsetY = 55;
	int achievementshoveredx;
	int achievementshoveredy;




public:
	void logic(void) final override;
	void render(void) final override;
	achievementscreen(void);
	~achievementscreen() final override;
};
