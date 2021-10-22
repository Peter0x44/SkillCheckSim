#pragma once
#include <raylib.h>

#include "gamestates.h"
#include "globals.h"

struct stats
{
	int score = 0;
	int combo = 0; //SCORE VARIABLES
	int missed = 0;
};

class skillcheckscreen: public gamestate
{
private:
	void DrawNormalSkillCheck(void); //DRAW SKILL CHECK FUNCTION
	void DrawHexRuinSkillCheck(void);
	void DrawDecisiveStrikeSkillCheck(void);

	void GenerateNormalSkillCheckZone(void); //GENERATION SKILL CHECK FUNCTION
	void GenerateHexRuinSkillCheckZone(void);
	void GenerateDecisiveStrikeSkillCheckZone(void);

	void NormalSkillCheck(void); // NORMAL SKILL CHECK
	void HexRuinSkillCheck(void); //HEX RUIN SKILL CHECK
	void DecisiveStrikeSkillCheck(void);

	Vector2 middle = { screenWidth / 2, screenHeight / 2 };

	const float spawnLocation = 90.0f; //STARTING LOCATION OF SKILL CHECK NEEDLE
	const float doctorSpawnLocation = -270.0f;
	const float skillCheckLimits = -270.0f;
	const float doctorSkillCheckLimits = 90.0f;

	const int spawnZone1 = -30; //SPAWN ZONES FOR SKILL CHECKS
	const int spawnZone2 = -270;
	const int doctorSpawnZone1 = -150; //SPAWN ZONES FOR SKILL CHECKS
	const int doctorSpawnZone2 = 90;

	const Rectangle startbutton = { middle.x, 340, 100, 50 };
	const Rectangle stopbutton = { middle.x - 100, 340, 100, 50 };
	const Rectangle achievbutton = { 10, 224, 200, 50 }; //A LOT OF VARIABLES
	const Rectangle Help = { 10 , 279, 200 ,50 };
	const Rectangle UnnervingPresenceButton = {10, 354, 50, 20};
	const Rectangle DoctorSkillCheckButton = { 10, 390, 50, 20 };

	bool startbuttonpressed = false;
	bool stopbuttonpressed = false;
	bool achievementspressed = false; //VARIABLES FOR WHEN BUTTONS ARE PRESSED
	bool skillcheckactive = false;
	bool helpbuttonpressed = false;

	bool UnnervingPresence = false;
	bool DoctorSkillCheck = false;

	const int radius = 100; //RADIUS OF CIRCLE

	stats scores;

	int gameMode = 0;
	bool guiDropdownboxEditmode = false;

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
