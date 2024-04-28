#pragma once
#include <raylib.h>

#include "gamestates.h"
#include "globals.h"
#include "skillcheck_behavior.h"


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
	//bool secretachievement;
	// easter egg achievement - decide what to do later
};

class skillcheckscreen final: public gamestate
{
private:
	void DrawGeneratorSkillCheck(void); //DRAW SKILL CHECK FUNCTION
	void DrawHealingSkillCheck(void);
	void DrawHexRuinSkillCheck(void);
	void DrawDecisiveStrikeSkillCheck(void);

	void SkillCheckLogic(void);

	Vector2 middle = { screenWidth / 2, screenHeight / 2 };

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

	int gameMode = 0;
	SkillCheck* skillCheck;
	SkillCheckState state; 

	const int radius = 100; //RADIUS OF CIRCLE

	stats scores;

	bool guiDropdownboxEditmode = false;

	bool moveSkillCheck = true;

	double timer;
	double spawnSkillcheckTimer; //TIMERS

public:
	void logic(void) final override;
	void render(void) final override;

	skillcheckscreen(void); //SKILL CHECK SCREEN
	~skillcheckscreen(void) final override;
};

extern Vector2 middle;
