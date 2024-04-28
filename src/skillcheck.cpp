#include <raylib.h>
#include <cmath>
#include <fstream>
#include <cfloat>
#include <iostream>
#include <raygui.h>
#include <cstring>

#include "globals.h"
#include "gamestates.h"
#include "skillcheck.h"

enum gamemodes
{
	Generator = 0,
	Healing,
	Ruin,
	DS
};

skillcheckscreen::skillcheckscreen(void)
{
	state.rotation = 0;
	moveSkillCheck = false;

	// TODO seralize into/outof json or ini?
	std::ifstream file("file.bin", std::ifstream::binary);

	if (file.is_open())
	{
		file.read((char*)&scores, sizeof(scores));
	}
	else
	{
		std::memset(&scores, 0, sizeof(scores)); //SETS ALL SCORE VARIABLES TO 0
	}

	state = {};
	skillCheck = new GeneratorSkillCheck(state);
}

skillcheckscreen::~skillcheckscreen(void)
{
	std::ofstream file("file.bin", std::ofstream::binary);
	if (file.is_open())
	{
		file.write((char*)&scores, sizeof(scores));
	}
	delete skillCheck;
}

void skillcheckscreen::logic(void)
{

	SkillCheckLogic();

	if (achievementspressed)
	{
		PlaySound(DBDClick);
		setnextstate(gamestates::achievementsscreen); //achievement button pressed - screen changes to achievement screen
	}

	if (helpbuttonpressed)
	{
		PlaySound(DBDClick2);
		setnextstate(gamestates::helpscreen); //help button pressed - screen changes to help screen
	}

	if (deletebuttonpressed)
	{
		std::remove("file.bin");
		std::memset(&scores, 0, sizeof(scores));
		gameMode = Generator;
	}
	
	if (settingsbuttonpressed)
	{
		setnextstate(gamestates::settingsscreen);
	}
}

void skillcheckscreen::render(void)
{
	DrawTexturePro(
			background,
			Rectangle {0, 0, (float)background.width, (float)background.height},
			Rectangle {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
			Vector2 {0, 0},
			0.0f,
			WHITE
	);

	DrawTextEx(Roboto, "Skill Check Simulator", Vector2{ (float)screenWidth - 120 - MeasureTextEx(Roboto, "Skill Check Simulator", 14, 1).x , 10 }, 28, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("X: %d", GetMouseX()), Vector2{ 10, 160 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("y: %d", GetMouseY()), Vector2{ 10, 190 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("state.rotation: %.0f", state.rotation), Vector2{ 10, 10 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("skillCheckZone: %.0f", state.greatZone.begin), Vector2{ 10, 40 }, 20, 1, WHITE); // Drawing all text to the screen
	DrawTextEx(Roboto, TextFormat("Bloodpoints: %d", scores.bloodpoints), Vector2{ 10, 70 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("Combo: %d", scores.combo), Vector2{ 10, 100 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("Missed: %d", scores.skillchecksmissed), Vector2{ 10, 130 }, 20, 1, WHITE);
//	DrawTextEx(Roboto, TextFormat("streak: %d", scores.greatskillcheckhit), Vector2{ 10, 130 }, 20, 1, WHITE);
	
	skillCheck->DrawSkillcheck();

	if (skillcheckactive) GuiLock();

	const char* const dropdownboxstring = "Generator;Healing;Hex: Ruin;Decisive Strike";

	int previousMode = gameMode;
	if (GuiDropdownBox(Rectangle{ 550,80,210,50 }, dropdownboxstring, &gameMode, guiDropdownboxEditmode))
	{
		guiDropdownboxEditmode = !guiDropdownboxEditmode;
	}

	if (gameMode != previousMode)
	{
		delete skillCheck;
		switch (gameMode)
		{
		case Generator:
			skillCheck = new GeneratorSkillCheck(state);
			break;
		case Healing:
			skillCheck = new HealingSkillCheck(state);
			break;
		case Ruin:
			skillCheck = new HexRuinSkillCheck(state);
			break;
		case DS:
			skillCheck = new DecisiveStrikeSkillCheck(state);
			break;
		}
	}
	
	GuiCheckBox(UnnervingPresenceButton, "Unnerving presence", &state.unnerving);
	GuiCheckBox(DoctorSkillCheckButton, "Doctor mode", &state.doctor);

	if (skillcheckactive) GuiUnlock();

	if (skillcheckactive) GuiSetState(STATE_FOCUSED);
	startbuttonpressed = GuiButton(startbutton, "Start");
	GuiSetState(STATE_NORMAL);

	if (!skillcheckactive) GuiSetState(STATE_FOCUSED);
	stopbuttonpressed = GuiButton(stopbutton, "Stop");
	GuiSetState(STATE_NORMAL);

	achievementspressed = GuiButton(achievbutton, "Achievements");  //Creation for all buttons
	helpbuttonpressed = GuiButton(Help, "Help");
	deletebuttonpressed = GuiButton(deletebutton, "Reset Stats");
	settingsbuttonpressed = GuiButton(settingsbutton, "Settings");

	//DrawText(TextFormat("%lf seconds until next skillcheck", spawnSkillcheckTimer - timer), 10, 10, 10, WHITE);
	//DrawText(TextFormat("Timer: %lf", timer), 20, 20, 10, WHITE);
}

void skillcheckscreen::SkillCheckLogic(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		timer = GetTime();
		spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0;
	}

	if (stopbuttonpressed && skillcheckactive)
	{
		skillcheckactive = false;
		moveSkillCheck = false;
		state.rotation = 0;
		state.greatZone = { 0, 0 };
		state.goodZone = { 0, 0 };
	}

	if (skillcheckactive)
	{
		timer = GetTime();

		if (timer > spawnSkillcheckTimer)
		{
			state.rotation = 0;
			moveSkillCheck = true;
			spawnSkillcheckTimer = DBL_MAX;
			PlaySound(skillCheckWarning);
			skillCheck->GenZone();
		}

		if (state.rotation > 360.0f)
		{
			// skillcheck has done full turn, must be missed
			moveSkillCheck = false;
			state.rotation = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0;
			skillCheck->OnMiss();
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (state.rotation > state.greatZone.begin 
				&& state.rotation < state.greatZone.end)
			{
				moveSkillCheck = false;
				skillCheck->OnGreat();
			}
			else if (state.rotation > state.goodZone.begin
				&& state.rotation < state.goodZone.end)
			{
				moveSkillCheck = false;
				skillCheck->OnGood();
			}
			else
			{
				if (moveSkillCheck)
				{
					skillCheck->OnMiss();
				}
				moveSkillCheck = false;
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0;
		}

		if (moveSkillCheck)
		{
			// healing skillchecks apparently take 1.2 seconds
			state.rotation += GetFrameTime() * 360.0f/1.2f;
		}
	}
}
