#pragma once
#include <raylib.h>

#include "gamestates.h"
#include "globals.h"


struct stats
{
	int bloodpoints;
	int skillchecksmissed;
	int maxcombo;
	int skillchecksmissedinarow;
	int combo;

	int greatskillcheckhit;
	int goodskillcheckhit;
	int greatskillcheckhitinarow;
	int goodskillcheckhitinarow;

	int totalskillchecks;
	int maxgreatskillcheckshitinarow;
	bool secretachievement;
};

struct zone
{
	float begin;
	float end;
};

class skillcheckscreen: public gamestate
{
private:
	void DrawGeneratorSkillCheck(void); //DRAW SKILL CHECK FUNCTION
	void DrawHealingSkillCheck(void);
	void DrawHexRuinSkillCheck(void);
	void DrawDecisiveStrikeSkillCheck(void);
	void DrawSecretSkillCheck(void);

	void DrawNeedle(void);
	void DrawCircle(void);

	void GenerateGeneratorSkillCheckZone(void);
	void GenerateHealingSkillCheckZone(void);
	void GenerateHexRuinSkillCheckZone(void);
	void GenerateDecisiveStrikeSkillCheckZone(void);
	void GenerateSecretSkillCheckZone(void);

	void GeneratorSkillCheck(void);
	void HealingSkillCheck(void);
	void HexRuinSkillCheck(void);
	void DecisiveStrikeSkillCheck(void);
	void SecretSkillCheck(void);

	Vector2 middle = { screenWidth / 2, screenHeight / 2 };

	const float spawnLocation = 0.0f; //STARTING LOCATION OF SKILL CHECK NEEDLE
	const float doctorSpawnLocation = -270.0f;
	const float skillCheckLimits = 360.0f;
	const float doctorSkillCheckLimits = 90.0f;

	const int spawnZone1 = -30; //SPAWN ZONES FOR SKILL CHECKS
	const int spawnZone2 = -270;
	const int doctorSpawnZone1 = -150; //SPAWN ZONES FOR SKILL CHECKS
	const int doctorSpawnZone2 = 90;

	const Rectangle startbutton = { middle.x, 340, 100, 50 };
	const Rectangle stopbutton = { middle.x - 100, 340, 100, 50 };
	const Rectangle achievbutton = { 10, 224, 200, 50 };
	const Rectangle Help = { 10 , 279, 200 ,50 };
	const Rectangle UnnervingPresenceButton = {10, 354, 50, 20};
	const Rectangle DoctorSkillCheckButton = { 10, 390, 50, 20 };
	const Rectangle deletebutton = { 680, 400, 120, 50 };
	const Rectangle settingsbutton = { 580, 400, 100, 50};

	bool startbuttonpressed = false;
	bool stopbuttonpressed = false;
	bool achievementspressed = false; //VARIABLES FOR WHEN BUTTONS ARE PRESSED
	bool skillcheckactive = false;
	bool helpbuttonpressed = false;
	bool deletebuttonpressed = false;
	bool settingsbuttonpressed = false;

	bool UnnervingPresence = false;
	bool DoctorSkillCheck = false;

	const int radius = 100; //RADIUS OF CIRCLE

	stats scores;

	int gameMode = 0;
	bool guiDropdownboxEditmode = false;

	zone greatSkillCheckZone = {0, 0};
	zone goodSkillCheckZone = {0, 0}; //VARIABLES FOR SKILL CHECK ZONES
	zone secretSkillCheckZone = { 0, 0 };

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
