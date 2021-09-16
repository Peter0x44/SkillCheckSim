#include <raylib.h>
#include <cmath>

#include "skillcheck.h"


Vector2 middle;

int main(void)
{


	SetConfigFlags(FLAG_MSAA_4X_HINT);


	int score = 0;

	Vector2 skillCheckZone;
	float rotationAngle = -90.0f;
	bool moveSkillCheck = true;

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator");

	//SetTargetFPS(60);

	double timer;
	double spawnSkillcheckTimer;

	timer = GetTime();
	spawnSkillcheckTimer = timer + 2;
	//int bruh = GetRandomValue(0, 90 + 180);
	int bruh = GetRandomValue(0, 360);
	skillCheckZone = { (float)bruh, (float)bruh + 15.0f };

	while (!WindowShouldClose())
	{
		timer = GetTime();

		middle = { (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = -90.0f;
			moveSkillCheck = true;
			spawnSkillcheckTimer = timer + 2;
			//int rand = GetRandomValue(0, 90 + 180);
			int rand = GetRandomValue(0, 360);
			skillCheckZone = { (float)rand, (float)rand + 15.0f };
		}

		DrawText(TextFormat("score: %d", score), 10, 10, 20, BLACK);

		if (rotationAngle > 270.0f)
		{
			moveSkillCheck = false;
			rotationAngle = 270.0f;
		}
		else if (IsKeyPressed(KEY_SPACE))
		{
			moveSkillCheck = false;
		}
	
		if (moveSkillCheck)
		{
			rotationAngle += GetFrameTime() * 60 * 6;
		}


		BeginDrawing();

			ClearBackground(GRAY);
			DrawSkillCheck(rotationAngle, Vector2{ 0,20 });

		EndDrawing();
	}

	CloseWindow();		// Close window and OpenGL context
	return 0;
}

void DrawSkillCheck(float angle, Vector2 skillCheckZone) 
{
	DrawCircleLines(middle.x, middle.y, 100, BLACK);
	DrawRing(middle, radius - 5, radius + 5, skillCheckZone.x, skillCheckZone.y, 15, GREEN);
	DrawLineEx(
		middle,
		Vector2
		{
			middle.x + cosf(angle * DEG2RAD) * radius,
			middle.y + sinf(angle * DEG2RAD) * radius
		},
		5.0f,
		RED
	);
		

}

