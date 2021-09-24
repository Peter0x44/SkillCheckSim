#include <raylib.h>
#include <cmath>
#include <extras/raygui.h>

#include "globals.h"
#include "gamestates.h"
#include "skillcheck.h"

skillcheckscreen::skillcheckscreen(void)
{
	float rotationAngle = spawnLocation;
}

skillcheckscreen::~skillcheckscreen(void)
{

}

void skillcheckscreen::GenerateSkillcheckZone(void)
{
	int rand = GetRandomValue(spawnZone1, spawnZone2);
	greatSkillCheckZone = { (float)rand, (float)rand + 10.0f };
	goodSkillCheckZone = { (float)rand + 10.0f, (float)rand + 40.0f };
}

void skillcheckscreen::logic(void)
{
	if (startbuttonpressed)
	{
		skillcheckactive = true;
		score = 0;
		combo = 0;
		missed = 0;
		rotationAngle = spawnLocation;
	}
	if (stopbuttonpressed)
	{
		skillcheckactive = false;
	}

	if (skillcheckactive)
	{
		timer = GetTime();

		middle = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = spawnLocation;
			moveSkillCheck = true;
			spawnSkillcheckTimer = timer + 2;
			GenerateSkillcheckZone();
			PlaySound(skillCheckWarning);
		}


		if (rotationAngle < -270.0f)
		{
			if (moveSkillCheck)
				++missed;
			moveSkillCheck = false;
			rotationAngle = spawnLocation;
			PlaySound(failedSkillCheck);
			combo = 0;

		}
		else if (IsKeyPressed(KEY_SPACE) && moveSkillCheck)
		{
			if (rotationAngle > greatSkillCheckZone.x && rotationAngle < greatSkillCheckZone.y)
			{
				++score;
				score += combo;
				++combo;
				PlaySound(greatSkillCheck);
				moveSkillCheck = false;
			}
			else if (rotationAngle > goodSkillCheckZone.x && rotationAngle < goodSkillCheckZone.y)
			{
				++score;
				score += combo;
				++combo;
				PlaySound(goodSkillCheck);
				moveSkillCheck = false;
			}
			else
			{
				if (moveSkillCheck)
				{
					++missed;
					PlaySound(failedSkillCheck);
				}
				moveSkillCheck = false;
				combo = 0;

			}
		}


		if (moveSkillCheck)
		{
			rotationAngle -= GetFrameTime() * 60 * 6;
		}

		if (buttonclicked)
		{
			PlaySound(greatSkillCheck);
			buttonclicked = false;
		}
	}
}

void skillcheckscreen::render(void)
{
	DrawTexture(background, 0, 0, WHITE);

	DrawText("Skill Check Simulator", screenWidth - 10 - MeasureText("Skill Check Simulator", 14), 10, 14, WHITE);
	DrawText(TextFormat("X: %d", GetMouseX()), 10, 160, 20, WHITE);
	DrawText(TextFormat("y: %d", GetMouseY()), 10, 190, 20, WHITE);
	DrawText(TextFormat("rotationAngle: %.0f", rotationAngle), 10, 10, 20, WHITE);
	DrawText(TextFormat("skillCheckZone: %.0f", greatSkillCheckZone.x), 10, 40, 20, WHITE);
	DrawText(TextFormat("Score: %d", score), 10, 70, 20, WHITE);
	DrawText(TextFormat("Combo: %d", combo), 10, 100, 20, WHITE);
	DrawText(TextFormat("Missed: %d", missed), 10, 130, 20, WHITE);


	DrawSkillCheck();
	startbuttonpressed = GuiButton(startbutton, "Start");
	stopbuttonpressed = GuiButton(stopbutton, "Stop");
	achievementspressed = GuiButton(achievbutton, "Achievements");
}

void skillcheckscreen::DrawSkillCheck(void) 
{
	DrawCircleLines(middle.x, middle.y, 100, WHITE);
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.x - 270.0f, greatSkillCheckZone.y - 270.0f, 15, WHITE);
	DrawRing(middle, radius - 5, radius + 5, goodSkillCheckZone.x - 270.0f, goodSkillCheckZone.y - 270.0f, 15, RED);
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawLineEx(
		middle,
		Vector2
		{
			middle.x + cosf(rotationAngle * DEG2RAD) * radius,
			middle.y - sinf(rotationAngle * DEG2RAD) * radius
		},
		5.0f,
		RED
	);
}
