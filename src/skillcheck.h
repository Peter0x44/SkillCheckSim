#pragma once
#include <raylib.h>

#include "gamestates.h"
#include "globals.h"


class skillcheckscreen: public gamestate
{
private:
	void DrawSkillCheck(void); //DRAW SKILL CHECK FUNCTION

	void GenerateSkillcheckZone(void); //GENERATION SKILL CHECK FUNCTION

	Vector2 middle = { screenWidth / 2, screenHeight / 2 };

	const float spawnLocation = 90.0f; //STARTING LOCATION OF SKILL CHECK NEEDLE
	const int spawnZone1 = -30; //SPAWN ZONES FOR SKILL CHECKS
	const int spawnZone2 = -270;
	const Rectangle startbutton = { middle.x, 340, 100, 50 };
	const Rectangle stopbutton = { middle.x - 100, 340, 100, 50 };
	const Rectangle achievbutton = { 10, 224, 100, 50 };
	const Rectangle ModesButton = { 10 , 279, 100 ,50 }; //A LOT OF VARIABLES
	const Rectangle Help = { 10 , 334, 100 ,50 };
	bool startbuttonpressed = false;
	bool stopbuttonpressed = false;
	bool achievementspressed = false; //VARIABLES FOR WHEN BUTTONS ARE PRESSED
	bool skillcheckactive = false;
	bool modesbuttonpressed = false;
	bool helpbuttonpressed = false;

	const int radius = 100; //RADIUS OF CIRCLE

	int score = 0;
	int combo = 0; //SCORE VARIABLES
	int missed = 0;

	Vector2 greatSkillCheckZone = {0, 0};
	Vector2 goodSkillCheckZone = {0, 0}; //VARIABLES FOR SKILL CHECK ZONES
	float rotationAngle = spawnLocation;
	bool moveSkillCheck = true;
	bool buttonclicked = false;

	double timer;
	double spawnSkillcheckTimer; //TIMERS

public:
	void logic(void) final override;
	void render(void) final override;

	skillcheckscreen(void); //SKILL CHECK SCREEN
	~skillcheckscreen(void) final override;

};

extern Vector2 middle;
