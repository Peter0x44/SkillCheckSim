#include <raylib.h>
#include <cmath>

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int radius = 100;

	int score = 0;

	Vector2 middle;
	Vector2 skillCheckZone;
	float rotationAngle = 90.0f;
	bool moveSkillCheck = true;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	double timer;
	double spawnSkillcheckTimer;

	timer = GetTime();
	spawnSkillcheckTimer = timer + 2;

	while (!WindowShouldClose())
	{
		timer = GetTime();

		middle = { GetScreenWidth()/2, GetScreenHeight()/2 };

		if (timer > spawnSkillcheckTimer)
		{
			rotationAngle = -90.0f;
			moveSkillCheck = true;
			spawnSkillcheckTimer = timer + 2;
		}

		DrawText(TextFormat("score: %d", score), 10, 10, 20, BLACK);

		if (rotationAngle > 270.0f || IsKeyPressed(KEY_SPACE))
		{
			moveSkillCheck = false;
		}
	
		if (moveSkillCheck)
		{
			rotationAngle += GetFrameTime() * 60 * 6;
		}


		BeginDrawing();

			ClearBackground(RAYWHITE);

			DrawLineEx
			(
				middle, 
				Vector2
				{
					middle.x + cosf(rotationAngle * DEG2RAD)*radius,
					middle.y + sinf(rotationAngle * DEG2RAD)*radius
				}, 
				10,
				RED
			);

			DrawCircleLines(middle.x, middle.y, 100, BLACK);

		EndDrawing();
	}

	CloseWindow();		// Close window and OpenGL context
	return 0;
}


