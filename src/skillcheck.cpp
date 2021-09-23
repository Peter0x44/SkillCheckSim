#include <raylib.h>
#include <cmath>
#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>

#include "skillcheck.h"

Sound goodSkillCheck;
Sound greatSkillCheck;
Sound skillCheckWarning;
Sound failedSkillCheck;

Vector2 middle = { screenWidth / 2, screenHeight / 2 };

const float spawnLocation = 90.0f;
const int spawnZone1 = -30;
const int spawnZone2 = -270;
const Rectangle startbutton = { middle.x, 340, 100, 50 };
const Rectangle stopbutton = { middle.x - 100, 340, 100, 50 };
bool startbuttonpressed = false;
bool stopbuttonpressed = false;
bool skillcheckactive = false;

int main(void)
{

	SetConfigFlags(FLAG_MSAA_4X_HINT);


	int score = 0;
	int combo = 0;
	int missed = 0;

	Vector2 greatSkillCheckZone;
	Vector2 goodSkillCheckZone;
	float rotationAngle = spawnLocation;
	bool moveSkillCheck = true;
	bool buttonclicked = false;

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator");

	LoadAssets();

	//SetTargetFPS(60);

	double timer;
	double spawnSkillcheckTimer;

	timer = GetTime();
	spawnSkillcheckTimer = timer + 2;

	GenerateSkillcheckZone(greatSkillCheckZone, goodSkillCheckZone);

	//skillCheckZone = currentskillcheck;

	while (!WindowShouldClose())
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
				GenerateSkillcheckZone(greatSkillCheckZone, goodSkillCheckZone);
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
			else if (IsKeyPressed(KEY_SPACE))
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



		BeginDrawing();

			ClearBackground(GRAY);
			//LoadTexture()
			//DrawTexture()

			//DrawText(TextFormat("score: %d", score), 10, 10, 20, BLACK);
			DrawText("Skill Check Simulator", screenWidth-10-MeasureText("Skill Check Simulator", 14), 10, 14, BLACK);
			DrawText(TextFormat("X: %d", GetMouseX()), 10, 160, 20, BLACK);
			DrawText(TextFormat("y: %d", GetMouseY()), 10, 190, 20, BLACK);
			DrawText(TextFormat("rotationAngle: %.0f", rotationAngle), 10, 10, 20, BLACK);
			DrawText(TextFormat("skillCheckZone: %.0f", greatSkillCheckZone.x), 10, 40, 20, BLACK);
			DrawText(TextFormat("Score: %d", score), 10, 70, 20, BLACK);
			DrawText(TextFormat("Combo: %d", combo), 10, 100, 20, BLACK);
			DrawText(TextFormat("Missed: %d", missed), 10, 130, 20, BLACK);
			

			DrawSkillCheck(rotationAngle, greatSkillCheckZone, goodSkillCheckZone);
			startbuttonpressed = GuiButton(startbutton, "Start");
			stopbuttonpressed = GuiButton(stopbutton, "Stop");

		EndDrawing();
	}

	UnloadAssets();
	CloseWindow();		// Close window and OpenGL context
	return 0;
}

void DrawSkillCheck(float angle, Vector2 greatSkillCheckZone, Vector2 goodSkillCheckZone) 
{
	DrawCircleLines(middle.x, middle.y, 100, BLACK);
	DrawRing(middle, radius - 5, radius + 5, greatSkillCheckZone.x - 270.0f, greatSkillCheckZone.y - 270.0f, 15, WHITE);
	DrawRing(middle, radius - 5, radius + 5, goodSkillCheckZone.x - 270.0f, goodSkillCheckZone.y - 270.0f, 15, BLACK);
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
}

void GenerateSkillcheckZone(Vector2& greatSkillCheckZone, Vector2& goodSkillCheckZone)
{
	int rand = GetRandomValue(spawnZone1, spawnZone2);
	greatSkillCheckZone = { (float)rand, (float)rand + 10.0f };
	goodSkillCheckZone = { (float)rand + 10.0f, (float)rand + 40.0f };
}

void LoadAssets(void)
{
	InitAudioDevice();
	greatSkillCheck = LoadSound("../assets/src_audio_great.mp3");
	skillCheckWarning = LoadSound("../assets/src_audio_advertise2.mp3");
	failedSkillCheck = LoadSound("../assets/sc0.mp3");
	goodSkillCheck = LoadSound("../assets/src_audio_good.mp3");
	int bruh = 1;
}

void UnloadAssets(void)
{
	UnloadSound(greatSkillCheck);
	UnloadSound(skillCheckWarning);
	UnloadSound(failedSkillCheck);
	UnloadSound(goodSkillCheck);
	CloseAudioDevice();
}