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
Texture2D achievementsbackground;
Font Roboto;

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
	achievementsbackground = LoadTexture("../assets/bg3.png");
	background = LoadTexture("../assets/bg.png");
	greatSkillCheck = LoadSound("../assets/src_audio_great.mp3");
	skillCheckWarning = LoadSound("../assets/src_audio_advertise2.mp3");
	failedSkillCheck = LoadSound("../assets/sc0.mp3");
	goodSkillCheck = LoadSound("../assets/src_audio_good.mp3");
	Roboto = LoadFont("../assets/Roboto-Light.ttf");
}

void UnloadAssets(void)
{
	UnloadSound(greatSkillCheck);
	UnloadSound(skillCheckWarning);
	UnloadSound(failedSkillCheck);
	UnloadSound(goodSkillCheck);
	UnloadTexture(background);
	UnloadTexture(achievementsbackground);
	UnloadFont(Roboto);
	CloseAudioDevice();
}
