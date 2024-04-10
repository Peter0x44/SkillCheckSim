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
	Ruin,
	DS,
	Secret
};

skillcheckscreen::skillcheckscreen(void)
{
	rotationAngle = 0;
	moveSkillCheck = false;

	std::ifstream file("file.bin", std::ifstream::binary);

	if (file.is_open())
	{
		file.read((char*)&scores, sizeof(scores));
	}
	else
	{
		std::memset(&scores, 0, sizeof(scores)); //SETS ALL SCORE VARIABLES TO 0
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

// https://deadbydaylight.fandom.com/wiki/Skill_Checks

// "Regular" skill check (generator:
// Great Success Zone Length: 3%
// Good Success Zone Length: 13%
// 

void skillcheckscreen::GenerateGeneratorSkillCheckZone(void)
{
	float generatorSkillCheckGreatWidth = 360.0f * 0.03f;
	float generatorSkillCheckGoodWidth = 360.0f * 0.13f;
	if (UnnervingPresence) generatorSkillCheckGoodWidth *= 0.4f;

	// Skillchecks start at 4 o'clock and end at 11 o'clock
	int rand = GetRandomValue(360/12*4, 360/12*11-generatorSkillCheckGoodWidth);
	
	greatSkillCheckZone = { (float)rand, (float)rand + generatorSkillCheckGreatWidth };   //Zones for where each skillcheck can spawn
	goodSkillCheckZone = { (float)rand + generatorSkillCheckGreatWidth, (float)rand + generatorSkillCheckGoodWidth };
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

void skillcheckscreen::GenerateSecretSkillCheckZone(void)
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

void skillcheckscreen::logic(void)
{

	switch (gameMode)
	{
	case Generator:
		GeneratorSkillCheck();
		break;
	case Ruin:
		HexRuinSkillCheck();
		break;
	case DS:
		DecisiveStrikeSkillCheck();
		break;
	case Secret:
		SecretSkillCheck();
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
	DrawTexture(background, 0, 0, WHITE);

	DrawTextEx(Roboto, "Skill Check Simulator", Vector2{ (float)screenWidth - 120 - MeasureTextEx(Roboto, "Skill Check Simulator", 14, 1).x , 10 }, 28, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("X: %d", GetMouseX()), Vector2{ 10, 160 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("y: %d", GetMouseY()), Vector2{ 10, 190 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("rotationAngle: %.0f", rotationAngle), Vector2{ 10, 10 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("skillCheckZone: %.0f", greatSkillCheckZone.begin), Vector2{ 10, 40 }, 20, 1, WHITE); // Drawing all text to the screen
	DrawTextEx(Roboto, TextFormat("Bloodpoints: %d", scores.bloodpoints), Vector2{ 10, 70 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("Combo: %d", scores.combo), Vector2{ 10, 100 }, 20, 1, WHITE);
	DrawTextEx(Roboto, TextFormat("Missed: %d", scores.skillchecksmissed), Vector2{ 10, 130 }, 20, 1, WHITE);
//	DrawTextEx(Roboto, TextFormat("streak: %d", scores.greatskillcheckhit), Vector2{ 10, 130 }, 20, 1, WHITE);
	

	switch (gameMode)
	{
	case Generator:
		DrawGeneratorSkillCheck();
		break;
	case Ruin:
		DrawHexRuinSkillCheck();
		break;
	case DS:
		DrawDecisiveStrikeSkillCheck();
		break;
	case Secret:
		DrawSecretSkillCheck();
		break;
	}

	if (skillcheckactive) GuiLock();

	const char* const dropdownboxstring = scores.secretachievement ? "Generator;Hex: Ruin;Decisive Strike; Secret Mode" : "Generator;Hex: Ruin;Decisive Strike";

	if (GuiDropdownBox(Rectangle{ 550,80,210,50 }, dropdownboxstring, &gameMode, guiDropdownboxEditmode))
	{
		guiDropdownboxEditmode = !guiDropdownboxEditmode;
	}
	
	GuiCheckBox(UnnervingPresenceButton, "Unnerving Presence", &UnnervingPresence);
	GuiCheckBox(DoctorSkillCheckButton, "Doctor mode", &DoctorSkillCheck);

	if (skillcheckactive) GuiUnlock();

	if (skillcheckactive) GuiSetState(STATE_FOCUSED);
	startbuttonpressed = GuiButton(startbutton, "Start");
	GuiSetState(STATE_NORMAL);

	if (!skillcheckactive) GuiSetState(STATE_FOCUSED);
	stopbuttonpressed = GuiButton(stopbutton, "Stop");
	GuiSetState(STATE_NORMAL);

	achievementspressed = GuiButton(achievbutton, "Achievements");  //Creation for all buttons
	helpbuttonpressed = GuiButton(Help, "help");
	deletebuttonpressed = GuiButton(deletebutton, "Reset Stats");
	settingsbuttonpressed = GuiButton(settingsbutton, "Settings");

	//DrawText(TextFormat("%lf seconds until next skillcheck", spawnSkillcheckTimer - timer), 10, 10, 10, WHITE);
	//DrawText(TextFormat("Timer: %lf", timer), 20, 20, 10, WHITE);
}

void skillcheckscreen::DrawNeedle(void)
{

	Vector2 lineEnd;
	if (DoctorSkillCheck)
	{
		lineEnd = Vector2 {
			middle.x - sinf(rotationAngle * DEG2RAD) * radius,
			middle.y - cosf(rotationAngle * DEG2RAD) * radius
		};
	}
	else
	{
		lineEnd = Vector2 {
			middle.x + sinf(rotationAngle * DEG2RAD) * radius,
			middle.y - cosf(rotationAngle * DEG2RAD) * radius
		};
	}

	DrawLineEx(
		middle,
		lineEnd,
		5.0f,
		RED
	);
}

void skillcheckscreen::DrawCircle(void)
{
	DrawCircleLines(middle.x, middle.y, 100, WHITE);
}

void skillcheckscreen::DrawGeneratorSkillCheck(void)
{
	DrawCircle();

	if (DoctorSkillCheck)
	{
		zone doctorGreat 
		{
			270.0f - greatSkillCheckZone.begin - (greatSkillCheckZone.end - greatSkillCheckZone.begin),
			270.0f - greatSkillCheckZone.begin
		};
		zone doctorGood
		{
			270.0f - goodSkillCheckZone.begin - (goodSkillCheckZone.end - goodSkillCheckZone.begin),
			270.0f - goodSkillCheckZone.begin
		};

		DrawRing(middle, radius - 5, radius + 5, doctorGreat.begin, doctorGreat.end, 15, WHITE);
		DrawRing(middle, radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(middle, radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, WHITE); // Drawing of main circle and needle


	}
	else
	{
		DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.begin-90.0f, greatSkillCheckZone.end-90.0f, 15, WHITE);
		DrawRing(middle, radius - 5, radius + 5, goodSkillCheckZone.begin-90.0f, goodSkillCheckZone.end-90.0f, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(middle, radius - 5, radius + 5, goodSkillCheckZone.begin-90.0f, goodSkillCheckZone.end-90.0f, 15, WHITE); // Drawing of main circle and needle
	}
	DrawNeedle();
}

void skillcheckscreen::DrawHexRuinSkillCheck(void)
{
	DrawCircle();
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.begin - 270.0f, greatSkillCheckZone.end - 270.0f, 15, RED);
	DrawRing(middle, radius - 5, radius + 5, goodSkillCheckZone.begin - 270.0f, goodSkillCheckZone.end - 270.0f, 15, BLACK); // Drawing of main circle and needle
	DrawRingLines(middle, radius - 5, radius + 5, goodSkillCheckZone.begin - 270.0f, goodSkillCheckZone.end - 270.0f, 15, RED); // Drawing of main circle and needle
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawNeedle();
}

void skillcheckscreen::DrawDecisiveStrikeSkillCheck(void)
{
	DrawCircle();
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.begin - 270.0f, greatSkillCheckZone.end - 270.0f, 15, WHITE);
	DrawRingLines(middle, radius - 5, radius + 5, greatSkillCheckZone.begin - 270.0f, greatSkillCheckZone.end - 270.0f, 15, DARKBLUE);
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawNeedle();
}

void skillcheckscreen::DrawSecretSkillCheck(void)
{
	DrawCircle();
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.begin - 270.0f, greatSkillCheckZone.end - 270.0f, 15, SKYBLUE);
	DrawRingLines(middle, radius - 5, radius + 5, greatSkillCheckZone.begin - 270.0f, greatSkillCheckZone.end - 270.0f, 15, BLACK);
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawNeedle();
}

void skillcheckscreen::GeneratorSkillCheck(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		moveSkillCheck = true;
		//scores.bloodpoints = 0;
		//scores.combo = 0; // score and scores.combo is set back to 0 and the skillcheck starts to move
		//scores.skillchecksmissed = 0; // Main IF statement for when skillcheck start button is pressed
		rotationAngle = 0;
		GenerateGeneratorSkillCheckZone(); //Generation Skillcheck function
		PlaySound(skillCheckWarning);
		timer = GetTime();
		spawnSkillcheckTimer = DBL_MAX;
	}

	if (stopbuttonpressed && skillcheckactive)
	{
		skillcheckactive = false;
		moveSkillCheck = false;
		rotationAngle = 0;
		greatSkillCheckZone = { 0, 0 };
		goodSkillCheckZone = { 0, 0 };
	}

	if (skillcheckactive)
	{
		timer = GetTime();

		middle = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = 0;
			moveSkillCheck = true;
			spawnSkillcheckTimer = DBL_MAX;
			++scores.totalskillchecks;

			GenerateGeneratorSkillCheckZone();
			PlaySound(skillCheckWarning);
		}

		if (rotationAngle > 360.0f)
		{
			// skillcheck has done full turn, must be missed
			if (moveSkillCheck)
				++scores.skillchecksmissed;
			moveSkillCheck = false;
			rotationAngle = 0;
			PlaySound(failedSkillCheck);
			scores.combo = 0;

			scores.greatskillcheckhitinarow = 0;
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (rotationAngle > greatSkillCheckZone.begin && rotationAngle < greatSkillCheckZone.end)
			{
				scores.bloodpoints = scores.bloodpoints + 2500;
				scores.bloodpoints += scores.combo;
				scores.combo = scores.combo + 1; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
				++scores.greatskillcheckhit;
				++scores.maxcombo;
				++scores.greatskillcheckhitinarow;

				if (scores.maxgreatskillcheckshitinarow < scores.greatskillcheckhitinarow)
				{
					scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
				}

				PlaySound(greatSkillCheck);
				moveSkillCheck = false;
			}
			else if (rotationAngle > goodSkillCheckZone.begin && rotationAngle < goodSkillCheckZone.end)
			{
				scores.bloodpoints = scores.bloodpoints + 50;
				scores.bloodpoints += scores.combo;
				++scores.combo;
				++scores.goodskillcheckhit;
				++scores.goodskillcheckhitinarow;
				++scores.maxcombo;
				scores.greatskillcheckhitinarow = 0;

				PlaySound(goodSkillCheck); //LOGIC for when rotationangle is in goodskillcheck zone, score is increased and right sound effect is played
				moveSkillCheck = false;
			}
			else
			{
				if (moveSkillCheck)
				{
					// Missed skill check
					++scores.skillchecksmissed;
					PlaySound(failedSkillCheck);
				}
				scores.greatskillcheckhitinarow = 0;
				scores.combo = 0;
				moveSkillCheck = false;
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;

		}

		if (moveSkillCheck)
		{
			// Generator skillchecks apparently take 1.1 seconds
			// healing skillchecks take 1.2
			// TODO: verify
			rotationAngle += GetFrameTime() * 360.0f/1.1f;
		}
	}
}

void skillcheckscreen::HexRuinSkillCheck(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		moveSkillCheck = true;
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
			++scores.totalskillchecks;

			GenerateHexRuinSkillCheckZone();
			PlaySound(skillCheckWarning);
		}


		if (DoctorSkillCheck && rotationAngle > doctorSkillCheckLimits) //|| !DoctorSkillCheck && rotationAngle > skillCheckLimits) // Player did not even attempt to hit the skill check
		{
			if (moveSkillCheck)
				++scores.skillchecksmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.skillchecksmissed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.combo = 0;
			scores.greatskillcheckhitinarow = 0;

			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;
		}
		else if (rotationAngle < skillCheckLimits)
		{
			if (moveSkillCheck)
				++scores.skillchecksmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.skillchecksmissed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.combo = 0;

			scores.greatskillcheckhitinarow = 0;

			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (DoctorSkillCheck)
			{
				if (rotationAngle < greatSkillCheckZone.begin && rotationAngle > greatSkillCheckZone.end)
				{
					scores.bloodpoints = scores.bloodpoints + 50;
					scores.bloodpoints += scores.combo;
					++scores.combo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					++scores.greatskillcheckhitinarow;
					++scores.greatskillcheckhit;
					if (scores.greatskillcheckhitinarow > scores.maxgreatskillcheckshitinarow)
					{
						scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
					}
					PlaySound(goodSkillCheck);
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.skillchecksmissed;

						scores.greatskillcheckhitinarow = 0;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.combo = 0;
					++scores.totalskillchecks;
					moveSkillCheck = false;
				}
			}
			else
			{
				if (rotationAngle > greatSkillCheckZone.begin && rotationAngle < greatSkillCheckZone.end)
				{
					scores.bloodpoints = scores.bloodpoints + 50;
					scores.bloodpoints += scores.combo;
					++scores.combo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					++scores.greatskillcheckhitinarow;
					++scores.greatskillcheckhit;

					if (scores.greatskillcheckhitinarow > scores.maxgreatskillcheckshitinarow)
					{
						scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
						printf("bruh");
					}

					PlaySound(goodSkillCheck);
					moveSkillCheck = false;
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.skillchecksmissed;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.combo = 0;
					scores.greatskillcheckhitinarow = 0;

					moveSkillCheck = false;
				}
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;

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
			++scores.totalskillchecks;

			GenerateDecisiveStrikeSkillCheckZone();
			PlaySound(skillCheckWarning);
		}


		if (DoctorSkillCheck && rotationAngle > doctorSkillCheckLimits) //|| !DoctorSkillCheck && rotationAngle > skillCheckLimits) // Player did not even attempt to hit the skill check
		{
			if (moveSkillCheck)
				++scores.skillchecksmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.skillchecksmissed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.combo = 0;

			scores.greatskillcheckhitinarow = 0;

			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;
		}
		else if (rotationAngle < skillCheckLimits)
		{
			if (moveSkillCheck)
				++scores.skillchecksmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.skillchecksmissed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.combo = 0;

			scores.greatskillcheckhitinarow = 0;

			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (DoctorSkillCheck)
			{
				if (rotationAngle < greatSkillCheckZone.begin && rotationAngle > greatSkillCheckZone.end)
				{
					scores.bloodpoints = scores.bloodpoints + 50;
					scores.bloodpoints += scores.combo;
					++scores.greatskillcheckhitinarow;
					++scores.greatskillcheckhit;
					++scores.combo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
					if (scores.greatskillcheckhitinarow > scores.maxgreatskillcheckshitinarow)
					{
						scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
					}
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.skillchecksmissed;

						scores.greatskillcheckhitinarow = 0;

						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.combo = 0;
					moveSkillCheck = false;
				}
			}
			else
			{
				if (rotationAngle > greatSkillCheckZone.begin && rotationAngle < greatSkillCheckZone.end)
				{
					scores.bloodpoints +=  50;
					scores.bloodpoints += scores.combo;
					++scores.greatskillcheckhitinarow;
					++scores.greatskillcheckhit;
					++scores.combo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
					if (scores.greatskillcheckhitinarow > scores.maxgreatskillcheckshitinarow)
					{
						scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
					}
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.skillchecksmissed;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.combo = 0;
					scores.greatskillcheckhitinarow = 0;
					moveSkillCheck = false;
				}
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 2000) / 1000.0f;

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

void skillcheckscreen::SecretSkillCheck(void)
{
	if (startbuttonpressed && !skillcheckactive)
	{
		skillcheckactive = true;
		moveSkillCheck = true;
		rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
		GenerateSecretSkillCheckZone(); //Generation Skillcheck function
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
			scores.totalskillchecks += 200;

			GenerateSecretSkillCheckZone();
			PlaySound(skillCheckWarning);
		}


		if (DoctorSkillCheck && rotationAngle > doctorSkillCheckLimits) //|| !DoctorSkillCheck && rotationAngle > skillCheckLimits) // Player did not even attempt to hit the skill check
		{
			if (moveSkillCheck)
				++scores.skillchecksmissed;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.skillchecksmissed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.combo = 0;

			scores.greatskillcheckhitinarow = 0;

			spawnSkillcheckTimer = timer + GetRandomValue(1000, 1500) / 1000.0f;
		}
		else if (rotationAngle < skillCheckLimits)
		{
			if (moveSkillCheck)
				scores.skillchecksmissed += 200;
			moveSkillCheck = false; //LOGIC - if rotationAngle > 270 then the skillcheck has done a full rotation therefore scores.skillchecksmissed goes up by 1 and rotationangle is set back to start
			rotationAngle = DoctorSkillCheck ? doctorSpawnLocation : spawnLocation;
			PlaySound(failedSkillCheck);
			scores.combo = 0;

			scores.greatskillcheckhitinarow = 0;

			spawnSkillcheckTimer = timer + GetRandomValue(1000, 1500) / 1000.0f;
		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (DoctorSkillCheck)
			{
				if (rotationAngle < greatSkillCheckZone.begin && rotationAngle > greatSkillCheckZone.end)
				{
					scores.bloodpoints += 20000;
					scores.bloodpoints += scores.combo;
					++scores.greatskillcheckhitinarow;
					++scores.greatskillcheckhit;
					scores.combo = scores.combo + 50; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
					if (scores.greatskillcheckhitinarow > scores.maxgreatskillcheckshitinarow)
					{
						scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
					}
				}
				else
				{
					if (moveSkillCheck)
					{
						++scores.skillchecksmissed;

						scores.greatskillcheckhitinarow = 0;

						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.combo = 0;
					moveSkillCheck = false;
				}
			}
			else
			{
				if (rotationAngle > greatSkillCheckZone.begin && rotationAngle < greatSkillCheckZone.end)
				{
					scores.bloodpoints += 20000;
					scores.bloodpoints += scores.combo;
					++scores.greatskillcheckhitinarow;
					++scores.greatskillcheckhit;
					++scores.combo; //LOGIC for when rotationangle is in the greatskillcheckzone, score is increased and right sound is played
					PlaySound(greatSkillCheck);
					moveSkillCheck = false;
					if (scores.greatskillcheckhitinarow > scores.maxgreatskillcheckshitinarow)
					{
						scores.maxgreatskillcheckshitinarow = scores.greatskillcheckhitinarow;
					}
				}
				else
				{
					if (moveSkillCheck)
					{
						scores.skillchecksmissed += 200;
						PlaySound(failedSkillCheck); //LOGIC for when you dont try and hit skill check, automatic miss
					}
					scores.combo = 0;
					scores.greatskillcheckhitinarow = 0;
					moveSkillCheck = false;
				}
			}
			spawnSkillcheckTimer = timer + GetRandomValue(1000, 1500) / 1000.0f;
		}

		if (moveSkillCheck)
		{
			if (DoctorSkillCheck)
				rotationAngle += GetFrameTime() * 60 * 8; //LOGIC - how fast rotationangle will move
			else
				rotationAngle -= GetFrameTime() * 60 * 8;
		}
	}
}

