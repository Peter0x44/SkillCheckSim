#include <raylib.h>
#include <cmath>
#include <iostream>

#include "skillcheck.h"


Vector2 middle;

const float spawnLocation = 90.0f;
const int spawnZone1 = 0;
const int spawnZone2 = -270;

int main(void)
{
	std::cout << "pls don't delete" << std::endl;

	SetConfigFlags(FLAG_MSAA_4X_HINT);


	int score = 0;

	Vector2 skillCheckZone;
	float rotationAngle = spawnLocation;
	bool moveSkillCheck = true;
	int currentskillcheck;

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator");

	//SetTargetFPS(60);

	double timer;
	double spawnSkillcheckTimer;

	timer = GetTime();
	spawnSkillcheckTimer = timer + 2;
	int bruh = GetRandomValue(spawnZone1, spawnZone2);
	skillCheckZone = { (float)bruh, (float)bruh + 15.0f };
	//skillCheckZone = currentskillcheck;

	while (!WindowShouldClose())
	{
		timer = GetTime();

		middle = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = spawnLocation;
			moveSkillCheck = true;
			spawnSkillcheckTimer = timer + 2;
			//int rand = GetRandomValue(0, 90 + 180);
			int rand = GetRandomValue(spawnZone1, spawnZone2);
			skillCheckZone = { (float)rand, (float)rand + 15.0f };
		}


		if (rotationAngle < -270.0f)
		{
			moveSkillCheck = false;
			rotationAngle = spawnLocation;
		}
		else if (IsKeyPressed(KEY_SPACE)) {
			moveSkillCheck = false;
			if (rotationAngle > skillCheckZone.x && rotationAngle < skillCheckZone.y)
			++score;

		}
			
			
		if (moveSkillCheck)
		{
			rotationAngle -= GetFrameTime() * 60 * 6;
		}





		BeginDrawing();

			ClearBackground(GRAY);

			//DrawText(TextFormat("score: %d", score), 10, 10, 20, BLACK);
			DrawText(TextFormat("rotationAngle: %.0f", rotationAngle), 10, 10, 20, BLACK);
			DrawText(TextFormat("skillCheckZone: %.0f", skillCheckZone.x), 10, 40, 20, BLACK);
			DrawText(TextFormat("Score: %d", score), 10, 70, 20, BLACK);

			DrawSkillCheck(rotationAngle, skillCheckZone);

		EndDrawing();
	}

	CloseWindow();		// Close window and OpenGL context
	return 0;
}

void DrawSkillCheck(float angle, Vector2 skillCheckZone) 
{
	DrawCircleLines(middle.x, middle.y, 100, BLACK);
	DrawRing(middle, radius - 5, radius + 5, skillCheckZone.x - 270.0f, skillCheckZone.y - 270.0f, 15, GREEN);
	//DrawRing(middle, radius - 5, radius + 5, 0 , 10, 15, GREEN);
	DrawLineEx(
		middle,
		Vector2
		{
			middle.x + cosf(angle * DEG2RAD) * radius,
			middle.y - sinf(angle * DEG2RAD) * radius
		},
		5.0f,
		RED
	);
	//DrawLineEx(
	//	middle,
	//	Vector2
	//	{
	//		middle.x + cosf(skillCheckZone.x * DEG2RAD) * radius,
	//		middle.y - sinf(skillCheckZone.y* DEG2RAD) * radius
	//	},
	//	5.0f,
	//	RED
	//);
}