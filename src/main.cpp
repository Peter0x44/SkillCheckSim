#include <raylib.h>
#include <cmath>
#define RAYGUI_IMPLEMENTATION
#include <extras/raygui.h> 
#undef RAYGUI_IMPLEMENTATION

#include "skillcheck.h"
#include "gamestates.h"

gamestate* currentstate;
gamestates stateid; //GAMESTATE VARIABLES
gamestates nextstate;


Sound goodSkillCheck;
Sound greatSkillCheck;
Sound skillCheckWarning;
Sound failedSkillCheck; //MORE VARIABLES
Texture2D background;
Texture2D achievementsbackground;
Texture2D helpbackground;
Font Roboto;

void LoadAssets(void); //LOAD ASSET FUNCTION, FURTHER DOWN

void UnloadAssets(void); //UNLOAD ASSET FUNCTION, FURTHER DOWN

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator"); //MAIN WINDOW

	GuiLoadStyle("../assets/candy.rgs");

	LoadAssets();

	currentstate = new skillcheckscreen();

	while (!WindowShouldClose()) //ONLY DOES WHEN WINDOW IS OPEN
	{
		currentstate->logic();

		BeginDrawing(); //DRAWNS TO SCREEN

			ClearBackground(GRAY); //BACKGROUND SET TO GRAY
			currentstate->render();

		EndDrawing(); //FINISHES DRAWING TO SCREEN

		changestate();

	}
}




void LoadAssets(void)
{
	InitAudioDevice();
	helpbackground = LoadTexture("../assets/help2.png");
	achievementsbackground = LoadTexture("../assets/bg3.png"); //LOADS TEXTURES FROM ASSETS
	background = LoadTexture("../assets/bg.png");
	greatSkillCheck = LoadSound("../assets/src_audio_great.mp3");
	skillCheckWarning = LoadSound("../assets/src_audio_advertise2.mp3"); //LOADS EVERY SOUND FROM ASSETS FOLDER
	failedSkillCheck = LoadSound("../assets/sc0.mp3");
	goodSkillCheck = LoadSound("../assets/src_audio_good.mp3");
	Roboto = LoadFont("../assets/Roboto-Light.ttf"); //LOADS FONT FROM ASSETS
}

void UnloadAssets(void)
{
	UnloadSound(greatSkillCheck);
	UnloadSound(skillCheckWarning);
	UnloadSound(failedSkillCheck);
	UnloadSound(goodSkillCheck); //UNLOADS EVERY SINGLE THING LOADED IN ASSETS FOLDER
	UnloadTexture(background);
	UnloadTexture(achievementsbackground);
	UnloadTexture(helpbackground);
	UnloadFont(Roboto);
	CloseAudioDevice();
}
