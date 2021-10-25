#include <raylib.h>
#include <cmath>
#include <fstream>
#include <cfloat>
#include <iostream>
#include <extras/raygui.h>

#include "globals.h"
#include "gamestates.h"
#include "skillcheck.h"

enum gamemodes
{
	Normal = 0,
	Ruin,
	DS
};

skillcheckscreen::skillcheckscreen(void)
{
	rotationAngle = spawnLocation;
	moveSkillCheck = false;
	GuiLoadStyle("../assets/terminal.rgs");

	std::ifstream file("file.bin", std::ifstream::binary);

	if (file.is_open())
	{
		file.read((char*)&scores, sizeof(scores));
	}
	else
	{
		scores.normalcombo = 0;
		scores.normalscore = 0;
		scores.normalmissed = 0;
		scores.normalmaxcombo = 0;
		scores.greatskillcheckhit = 0;
		scores.goodskillcheckhit = 0;

		scores.dscombo = 0;
		scores.dsscore = 0;
		scores.dsmissed = 0;
		scores.dsmaxcombo = 0;

		scores.hexcombo = 0;
		scores.hexscore = 0;
		scores.hexmissed = 0;
		scores.hexmaxcombo = 0;

	}

}

skillcheckscreen::~skillcheckscreen(void)
{
	std::ofstream file("file.bin", std::ofstream::binary);
	if (file.is_open())
	{
		file.write((char*)&scores, sizeof(scores));
	}
}

void skillcheckscreen::GenerateNormalSkillCheckZone(void)
{
	int rand = DoctorSkillCheck ? GetRandomValue(doctorSpawnZone1, doctorSpawnZone2) : GetRandomValue(spawnZone1, spawnZone2);
	float multiplier = UnnervingPresence ? 0.4f : 1.0f;
	
	if (DoctorSkillCheck)
	{
		greatSkillCheckZone = { (float)rand, (float)rand - 10.0f };   //Zones for where each skillcheck can spawn
		goodSkillCheckZone = { (float)rand - 10.0f, (float)rand - 10 - 30.0f*multiplier };
	}
	else
	{
		greatSkillCheckZone = { (float)rand, (float)rand + 10.0f };   //Zones for where each skillcheck can spawn
		goodSkillCheckZone = { (float)rand + 10.0f, (float)rand + 10 + 30.0f*multiplier };
	}
}

void skillcheckscreen::GenerateHexRuinSkillCheckZone(void)
{

	int rand = DoctorSkillCheck ? GetRandomValue(doctorSpawnZone1, doctorSpawnZone2) : GetRandomValue(spawnZone1, spawnZone2);
	float multiplier = UnnervingPresence ? 0.4f : 1.0f;

	if (DoctorSkillCheck)
	{
		greatSkillCheckZone = { (float)rand, (float)rand - 10.0f };   //Zones for where each skillcheck can spawn
		goodSkillCheckZone = { (float)rand - 10.0f, (float)rand - 10 - 30.0f * multiplier };
	}
	else
	{
		greatSkillCheckZone = { (float)rand, (float)rand + 10.0f };   //Zones for where each skillcheck can spawn
		goodSkillCheckZone = { (float)rand + 10.0f, (float)rand + 10 + 30.0f * multiplier };
	}
}

void skillcheckscreen::GenerateDecisiveStrikeSkillCheckZone(void)
{
	int rand = DoctorSkillCheck ? GetRandomValue(doctorSpawnZone1, doctorSpawnZone2) : GetRandomValue(spawnZone1, spawnZone2);
	float multiplier = UnnervingPresence ? 0.4f : 1.0f;

	if (DoctorSkillCheck)
	{
		greatSkillCheckZone = { (float)rand, (float)rand - 20.0f*multiplier };   //Zones for where each skillcheck can spawn
	}
	else
	{
		greatSkillCheckZone = { (float)rand, (float)rand + 20.0f*multiplier };   //Zones for where each skillcheck can spawn
	}
}

void skillcheckscreen::logic(void)
{

	switch (gameMode)
	{
	case Normal:
		NormalSkillCheck();
		break;
	case Ruin:
		HexRuinSkillCheck();
		break;
	case DS:
		DecisiveStrikeSkillCheck();
		break;
	}

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

}

void skillcheckscreen::render(void)
{
	DrawTexture(background, 0, 0, WHITE);

	DrawTextEx(Roboto, "Skill Check Simulator", Vector2{ (float)screenWidth - 120 - MeasureTextEx(Roboto, "Skill Check Simulator", 14, 1).x , 10 }, 28, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("X: %d", GetMouseX()), Vector2{ 10, 160 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("y: %d", GetMouseY()), Vector2{ 10, 190 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("rotationAngle: %.0f", rotationAngle), Vector2{ 10, 10 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("skillCheckZone: %.0f", greatSkillCheckZone.x), Vector2{ 10, 40 }, 20, 1, WHITE); // Drawing all text to the screen
	

	switch (gameMode)
	{
	case Normal:
		DrawTextEx(Roboto, TextFormat("Score: %d", scores.normalscore), Vector2{ 10, 70 }, 20, 1, WHITE);
		DrawTextEx(Roboto, TextFormat("Combo: %d", scores.normalcombo), Vector2{ 10, 100 }, 20, 1, WHITE);
		DrawTextEx(Roboto, TextFormat("Missed: %d", scores.normalmissed), Vector2{ 10, 130 }, 20, 1, WHITE);
		DrawNormalSkillCheck();
		break;
	case Ruin:
		DrawTextEx(Roboto, TextFormat("Score: %d", scores.hexscore), Vector2{ 10, 70 }, 20, 1, WHITE);
		DrawTextEx(Roboto, TextFormat("Combo: %d", scores.hexcombo), Vector2{ 10, 100 }, 20, 1, WHITE);
		DrawTextEx(Roboto, TextFormat("Missed: %d", scores.hexmissed), Vector2{ 10, 130 }, 20, 1, WHITE);
		DrawHexRuinSkillCheck();
		break;
	case DS:
		DrawTextEx(Roboto, TextFormat("Score: %d", scores.dsscore), Vector2{ 10, 70 }, 20, 1, WHITE);
		DrawTextEx(Roboto, TextFormat("Combo: %d", scores.dscombo), Vector2{ 10, 100 }, 20, 1, WHITE);
		DrawTextEx(Roboto, TextFormat("Missed: %d", scores.dsmissed), Vector2{ 10, 130 }, 20, 1, WHITE);
		DrawDecisiveStrikeSkillCheck();
		break;
	}

	if (skillcheckactive) GuiLock();

	if (GuiDropdownBox(Rectangle{ 550,80,210,50 }, "Normal;Hex: Ruin;Decisive Strike", &gameMode, guiDropdownboxEditmode)) 
	{
		guiDropdownboxEditmode = !guiDropdownboxEditmode;
		//PlaySound(DBDClick3);
	}
	
	UnnervingPresence = GuiCheckBox(UnnervingPresenceButton, "Unnerving Presence", UnnervingPresence);
	DoctorSkillCheck = GuiCheckBox(DoctorSkillCheckButton, "Doctor mode", DoctorSkillCheck);

	if (skillcheckactive) GuiUnlock();

	if (skillcheckactive) GuiSetState(GUI_STATE_FOCUSED);
	startbuttonpressed = GuiButton(startbutton, "Start");
	GuiSetState(GUI_STATE_NORMAL);

	if (!skillcheckactive) GuiSetState(GUI_STATE_FOCUSED);
	stopbuttonpressed = GuiButton(stopbutton, "Stop");
	GuiSetState(GUI_STATE_NORMAL);

	achievementspressed = GuiButton(achievbutton, "Achievements");  //Creation for all buttons
	helpbuttonpressed = GuiButton(Help, "help");

	//DrawText(TextFormat("%lf seconds until next skillcheck", spawnSkillcheckTimer - timer), 10, 10, 10, WHITE);
	//DrawText(TextFormat("Timer: %lf", timer), 20, 20, 10, WHITE);
}

void skillcheckscreen::DrawNormalSkillCheck(void)
{
	DrawCircleLines(middle.x, middle.y, 100, WHITE);
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.x - 270.0f, greatSkillCheckZone.y - 270.0f, 15, WHITE);
	DrawRing(middle, radius - 5, radius + 5, goodSkillCheckZone.x - 270.0f, goodSkillCheckZone.y - 270.0f, 15, BLACK); // Drawing of main circle and needle
	DrawRingLines(middle, radius - 5, radius + 5, goodSkillCheckZone.x - 270.0f, goodSkillCheckZone.y - 270.0f, 15, WHITE); // Drawing of main circle and needle
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawLineEx(
		middle,
		Vector2
		{
			middle.x + cosf(rotationAngle * DEG2RAD) * radius,
			middle.y - sinf(rotationAngle * DEG2RAD) * radius //drawing correct lines
		},
		5.0f,
		RED
	);
}

void skillcheckscreen::DrawHexRuinSkillCheck(void)
{
	DrawCircleLines(middle.x, middle.y, 100, WHITE);
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.x - 270.0f, greatSkillCheckZone.y - 270.0f, 15, RED);
	DrawRing(middle, radius - 5, radius + 5, goodSkillCheckZone.x - 270.0f, goodSkillCheckZone.y - 270.0f, 15, BLACK); // Drawing of main circle and needle
	DrawRingLines(middle, radius - 5, radius + 5, goodSkillCheckZone.x - 270.0f, goodSkillCheckZone.y - 270.0f, 15, RED); // Drawing of main circle and needle
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawLineEx(
		middle,
		Vector2
		{
			middle.x + cosf(rotationAngle * DEG2RAD) * radius,
			middle.y - sinf(rotationAngle * DEG2RAD) * radius //drawing correct lines
		},
		5.0f,
		RED
	);
}

void skillcheckscreen::DrawDecisiveStrikeSkillCheck(void)
{
	DrawCircleLines(middle.x, middle.y, 100, WHITE);
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.x - 270.0f, greatSkillCheckZone.y - 270.0f, 15, WHITE);
	DrawRingLines(middle, radius - 5, radius + 5, greatSkillCheckZone.x - 270.0f, greatSkillCheckZone.y - 270.0f, 15, BLACK);
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawLineEx(
		middle,
		Vector2
		{
			middle.x + cosf(rotationAngle * DEG2RAD) * radius,
			middle.y - sinf(rotationAngle * DEG2RAD) * radius //drawing correct lines
		},
		5.0f,
		RED
	);
}

void skillcheckscreen::NormalSkillCheck(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		moveSkillCheck = true;
		//scores.score = 0;
		//scores.combo = 0; // score and scores.combo is set back to 0 and the skillcheck starts to move
		//scores.missed = 0; // Main IF statement for when skillcheck start button is pressed
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
		GenerateNormalSkillCheckZone(); //Generation Skillcheck function
		PlaySound(skillCheckWarning);
		timer = GetTime();
		spawnSkillcheckTimer = DBL_MAX;
	}

	if (stopbuttonpressed && skillcheckactive)
	{
		skillcheckactive = false;
		moveSkillCheck = false;
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation; //When stop button is pressed skill check stops moving and zones are set back to 0,0
		greatSkillCheckZone = { 0, 0 };
		goodSkillCheckZone = { 0, 0 };
	}

	if (skillcheckactive)
	{
		timer = GetTime();

		middle = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			moveSkillCheck = true;
			spawnSkillcheckTimer = DBL_MAX; //TIMER IS TIME SINCE WINDOW WAS OPENED, THIS TIME HAS TO BE GREATER THAN SKILLCHECKTIMER TO SPAWN IN A SKILLCHECK
			GenerateNormalSkillCheckZone();
			PlaySound(skillCheckWarning);
		}


		if (DoctorSkillCheck && rotationAngle > doctorSkillCheckLimits) //|| !DoctorSkillCheck && rotationAngle > skillCheckLimits) // Player did not even attempt to hit the skill check
		{
			if (moveSkillCheck)
				++scores.normalmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.missed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.normalcombo = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);
		}
		else if (rotationAngle < skillCheckLimits)
		{
			if (moveSkillCheck)
				++scores.normalmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.missed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.normalcombo = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (DoctorSkillCheck)
			{
				if (rotationAngle < greatSkillCheckZone.x && rotationAngle > greatSkillCheckZone.y)
				{
					scores.normalscore = scores.normalscore + 25;
					scores.normalscore += scores.normalcombo;
					scores.normalcombo = scores.normalcombo + 2; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					++scores.greatskillcheckhit;
					++scores.greatskillcheckhitinarow;
					++scores.normalmaxcombo;
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
				}
				else if (rotationAngle < goodSkillCheckZone.x && rotationAngle > goodSkillCheckZone.y)
				{
					++scores.normalscore;
					scores.normalscore += scores.normalcombo;
					++scores.normalcombo;
					++scores.goodskillcheckhit;
					++scores.goodskillcheckhitinarow;
					++scores.normalmaxcombo;
					PlaySound(goodSkillCheck); //LOGIC for when rotationangle is in goodskillcheck zone, score is increased and right sound effect is played
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.normalmissed;
						scores.goodskillcheckhitinarow = 0;
						scores.greatskillcheckhitinarow = 0;
						scores.normalmaxcombo = 0;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.normalcombo = 0;
					moveSkillCheck = false;
				}
			}
			else
			{
				if (rotationAngle > greatSkillCheckZone.x && rotationAngle < greatSkillCheckZone.y)
				{
					scores.normalscore = scores.normalscore + 25;
					scores.normalscore += scores.normalcombo;
					scores.normalcombo = scores.normalcombo + 2; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					++scores.greatskillcheckhit;
					++scores.normalmaxcombo;
					++scores.greatskillcheckhitinarow;
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
				}
				else if (rotationAngle > goodSkillCheckZone.x && rotationAngle < goodSkillCheckZone.y)
				{
					++scores.normalscore;
					scores.normalscore += scores.normalcombo;
					++scores.normalcombo;
					++scores.goodskillcheckhit;
					++scores.goodskillcheckhitinarow;
					++scores.normalmaxcombo;
					PlaySound(goodSkillCheck); //LOGIC for when rotationangle is in goodskillcheck zone, score is increased and right sound effect is played
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.normalmissed;
						scores.goodskillcheckhitinarow = 0;
						scores.greatskillcheckhitinarow = 0;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.normalcombo = 0;
					moveSkillCheck = false;
				}
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);

		}

		if (moveSkillCheck)
		{
			if (DoctorSkillCheck)
				rotationAngle += GetFrameTime() * 60 * 6; //LOGIC - how fast rotationangle will move
			else
				rotationAngle -= GetFrameTime() * 60 * 3;
		}
	}
}

void skillcheckscreen::HexRuinSkillCheck(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		moveSkillCheck = true;
		scores.hexscore = 0;
		scores.hexcombo = 0; // scores.score and scores.combo is set back to 0 and the skillcheck starts to move
		scores.hexmissed = 0; // Main IF statement for when skillcheck start button is pressed
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
		GenerateHexRuinSkillCheckZone(); //Generation Skillcheck function
		PlaySound(skillCheckWarning);
		timer = GetTime();
		spawnSkillcheckTimer = DBL_MAX;
	}

	if (stopbuttonpressed && skillcheckactive)
	{
		skillcheckactive = false;
		moveSkillCheck = false;
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation; //When stop button is pressed skill check stops moving and zones are set back to 0,0
		greatSkillCheckZone = { 0, 0 };
		goodSkillCheckZone = { 0, 0 };
	}

	if (skillcheckactive)
	{
		timer = GetTime();

		middle = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			moveSkillCheck = true;
			spawnSkillcheckTimer = DBL_MAX; //TIMER IS TIME SINCE WINDOW WAS OPENED, THIS TIME HAS TO BE GREATER THAN SKILLCHECKTIMER TO SPAWN IN A SKILLCHECK
			GenerateHexRuinSkillCheckZone();
			PlaySound(skillCheckWarning);
		}


		if (DoctorSkillCheck && rotationAngle > doctorSkillCheckLimits) //|| !DoctorSkillCheck && rotationAngle > skillCheckLimits) // Player did not even attempt to hit the skill check
		{
			if (moveSkillCheck)
				++scores.hexmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.missed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.hexcombo = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);
		}
		else if (rotationAngle < skillCheckLimits)
		{
			if (moveSkillCheck)
				++scores.hexmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.missed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.hexcombo = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (DoctorSkillCheck)
			{
				if (rotationAngle < greatSkillCheckZone.x && rotationAngle > greatSkillCheckZone.y)
				{
					++scores.hexscore;
					scores.hexscore += scores.hexcombo;
					++scores.hexcombo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.hexmissed;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.hexcombo = 0;
					moveSkillCheck = false;
				}
			}
			else
			{
				if (rotationAngle > greatSkillCheckZone.x && rotationAngle < greatSkillCheckZone.y)
				{
					++scores.hexscore;
					scores.hexscore += scores.hexcombo;
					++scores.hexcombo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.hexmissed;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.hexcombo = 0;
					moveSkillCheck = false;
				}
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);

		}

		if (moveSkillCheck)
		{
			if (DoctorSkillCheck)
				rotationAngle += GetFrameTime() * 60 * 6; //LOGIC - how fast rotationangle will move
			else
				rotationAngle -= GetFrameTime() * 60 * 6;
		}
	}
}

void skillcheckscreen::DecisiveStrikeSkillCheck(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		moveSkillCheck = true;
		scores.dsscore = 0;
		scores.dscombo = 0; // score and scores.combo is set back to 0 and the skillcheck starts to move
		scores.dsmissed = 0; // Main IF statement for when skillcheck start button is pressed
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
		GenerateDecisiveStrikeSkillCheckZone(); //Generation Skillcheck function
		PlaySound(skillCheckWarning);
		timer = GetTime();
		spawnSkillcheckTimer = DBL_MAX;
	}

	if (stopbuttonpressed && skillcheckactive)
	{
		skillcheckactive = false;
		moveSkillCheck = false;
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation; //When stop button is pressed skill check stops moving and zones are set back to 0,0
		greatSkillCheckZone = { 0, 0 };
		goodSkillCheckZone = { 0, 0 };
	}

	if (skillcheckactive)
	{
		timer = GetTime();

		middle = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			moveSkillCheck = true;
			spawnSkillcheckTimer = DBL_MAX; //TIMER IS TIME SINCE WINDOW WAS OPENED, THIS TIME HAS TO BE GREATER THAN SKILLCHECKTIMER TO SPAWN IN A SKILLCHECK
			GenerateDecisiveStrikeSkillCheckZone();
			PlaySound(skillCheckWarning);
		}


		if (DoctorSkillCheck && rotationAngle > doctorSkillCheckLimits) //|| !DoctorSkillCheck && rotationAngle > skillCheckLimits) // Player did not even attempt to hit the skill check
		{
			if (moveSkillCheck)
				++scores.dsmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.missed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.dscombo = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);
		}
		else if (rotationAngle < skillCheckLimits)
		{
			if (moveSkillCheck)
				++scores.dsmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.missed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.dscombo = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (DoctorSkillCheck)
			{
				if (rotationAngle < greatSkillCheckZone.x && rotationAngle > greatSkillCheckZone.y)
				{
					++scores.dsscore;
					scores.dsscore += scores.dscombo;
					++scores.dscombo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.dsmissed;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.dscombo = 0;
					moveSkillCheck = false;
				}
			}
			else
			{
				if (rotationAngle > greatSkillCheckZone.x && rotationAngle < greatSkillCheckZone.y)
				{
					++scores.dsscore;
					scores.dsscore += scores.dscombo;
					++scores.dscombo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.dsmissed;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.dscombo = 0;
					moveSkillCheck = false;
				}
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1, 2);

		}

		if (moveSkillCheck)
		{
			if (DoctorSkillCheck)
				rotationAngle += GetFrameTime() * 60 * 6; //LOGIC - how fast rotationangle will move
			else
				rotationAngle -= GetFrameTime() * 60 * 6;
		}
	}
}

