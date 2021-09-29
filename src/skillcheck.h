#pragma once
#include <raylib.h>

#include "gamestates.h"
#include "globals.h"


class skillcheckscreen: public gamestate
{
private:
	void DrawSkillCheck(void);

	void GenerateSkillcheckZone(void);

	Vector2 middle = { screenWidth / 2, screenHeight / 2 };

	const float spawnLocation = 90.0f;
	const int spawnZone1 = -30;
	const int spawnZone2 = -270;
	const Rectangle startbutton = { middle.x, 340, 100, 50 };
	const Rectangle stopbutton = { middle.x - 100, 340, 100, 50 };
	const Rectangle achievbutton = { 10, 224, 100, 50 };
	const Rectangle ModesButton = { 10 , 279, 100 ,50 };
	const Rectangle Help = { 10 , 334, 100 ,50 };
	bool startbuttonpressed = false;
	bool stopbuttonpressed = false;
	bool achievementspressed = false;
	bool skillcheckactive = false;
	bool modesbuttonpressed = false;
	bool helpbuttonpressed = false;

	const int radius = 100;

	int score = 0;
	int combo = 0;
	int missed = 0;

	Vector2 greatSkillCheckZone = {0, 0};
	Vector2 goodSkillCheckZone = {0, 0};
	float rotationAngle = spawnLocation;
	bool moveSkillCheck = true;
	bool buttonclicked = false;

	double timer;
	double spawnSkillcheckTimer;

public:
	void logic(void) final override;
	void render(void) final override;

	skillcheckscreen(void);
	~skillcheckscreen(void) final override;

};

extern Vector2 middle;
