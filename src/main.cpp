#include <raylib.h>
#include <cmath>
#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include "skillcheck.h"
#include "gamestates.h"

gamestate* currentstate;
gamestates stateid;
gamestates nextstate;


Sound goodSkillCheck;
Sound greatSkillCheck;
Sound skillCheckWarning;
Sound failedSkillCheck;
Texture2D background;

void LoadAssets(void);

void UnloadAssets(void);

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator");

	LoadAssets();

	currentstate = new skillcheckscreen();

	while (!WindowShouldClose())
	{
		currentstate->logic();

		BeginDrawing();

			ClearBackground(GRAY);
			currentstate->render();

		EndDrawing();

		changestate();

	}
}




void LoadAssets(void)
{
	InitAudioDevice();
	background = LoadTexture("../assets/bg.png");
	greatSkillCheck = LoadSound("../assets/src_audio_great.mp3");
	skillCheckWarning = LoadSound("../assets/src_audio_advertise2.mp3");
	failedSkillCheck = LoadSound("../assets/sc0.mp3");
	goodSkillCheck = LoadSound("../assets/src_audio_good.mp3");
}

void UnloadAssets(void)
{
	UnloadSound(greatSkillCheck);
	UnloadSound(skillCheckWarning);
	UnloadSound(failedSkillCheck);
	UnloadSound(goodSkillCheck);
	UnloadTexture(background);
	CloseAudioDevice();
}
