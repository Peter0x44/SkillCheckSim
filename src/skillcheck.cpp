#include <raylib.h>
#include <cmath>

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int radius = 100;

	SetConfigFlags(FLAG_MSAA_4X_HINT);


	int score = 0;

	Vector2 middle;
	Vector2 skillCheckZone;
	float rotationAngle = 90.0f;
	bool moveSkillCheck = true;

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator");

	//SetTargetFPS(60);

	double timer;
	double spawnSkillcheckTimer;

	timer = GetTime();
	spawnSkillcheckTimer = timer + 2;
	int bruh = GetRandomValue(90, 90 + 180);
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
			int rand = GetRandomValue(90, 90 + 180);
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

			ClearBackground(RAYWHITE);

			DrawCircleLines(middle.x, middle.y, 100, BLACK);

			DrawRing(middle, radius-5, radius+5, skillCheckZone.x, skillCheckZone.y, 15, GREEN);


			DrawLineEx
			(
				middle, 
				Vector2
				{
					middle.x + cosf(rotationAngle * DEG2RAD)*radius,
					middle.y + sinf(rotationAngle * DEG2RAD)*radius
				}, 
				6.0f,
				RED
			);
		EndDrawing();
	}

	CloseWindow();		// Close window and OpenGL context
	return 0;
}


