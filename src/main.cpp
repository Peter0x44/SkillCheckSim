#include <raylib.h>
#include <cmath>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

#include "skillcheck.h"
#include "gamestates.h"

gamestate* currentstate;
gamestates stateid; //GAMESTATE VARIABLES
gamestates nextstate;


Sound goodSkillCheck;
Sound greatSkillCheck;
Sound skillCheckWarning;
Sound failedSkillCheck; //VARIABLES FOR THE SOUNDS PLAYED IN THE GAME
Sound DBDClick;
Sound DBDClick2;
Sound DBDClick3;
Sound DBDClick4;

Texture2D background;
Texture2D achievementsbackground;
Texture2D helpbackground;
Texture2D achievementsheet;

Font Roboto;

void LoadAssets(void); //LOAD ASSET FUNCTION, FURTHER DOWN

void UnloadAssets(void); //UNLOAD ASSET FUNCTION, FURTHER DOWN

int main(void)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Skillcheck Simulator"); //MAIN WINDOW

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

	delete currentstate;
	CloseWindow();

}




void LoadAssets(void)
{
	InitAudioDevice();
	helpbackground = LoadTexture("../assets/help2.png");
	achievementsbackground = LoadTexture("../assets/bg3.png"); //LOADS TEXTURES FROM ASSETS
	background = LoadTexture("../assets/bg.png");
	achievementsheet = LoadTexture("../assets/achievementsheet.png");

	greatSkillCheck = LoadSound("../assets/src_audio_great.mp3");
	skillCheckWarning = LoadSound("../assets/src_audio_advertise2.mp3"); //LOADS EVERY SOUND FROM ASSETS FOLDER
	failedSkillCheck = LoadSound("../assets/sc0.mp3");
	goodSkillCheck = LoadSound("../assets/src_audio_good.mp3");
	DBDClick = LoadSound("../assets/buttonclick1.mp3");
	DBDClick2 = LoadSound("../assets/buttonclick2.mp3"); //ALL SOUNDS FOR BUTTONS
	DBDClick3 = LoadSound("../assets/buttonclick3.mp3");
	DBDClick4 = LoadSound("../assets/buttonclick4.mp3");

	Roboto = LoadFont("../assets/Roboto-Light.ttf"); //LOADS FONT FROM ASSETS
	GuiLoadStyle("../assets/lol10.rgs");
	GuiSetFont(Roboto);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

	Image icon = LoadImage("../assets/icon2.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
}

void UnloadAssets(void)
{
	UnloadSound(greatSkillCheck);
	UnloadSound(skillCheckWarning);
	UnloadSound(failedSkillCheck);
	UnloadSound(goodSkillCheck); //UNLOADS EVERY SINGLE THING LOADED IN ASSETS FOLDER
	UnloadSound(DBDClick);
	UnloadSound(DBDClick2); //ALL SOUNDS FOR BUTTONS
	UnloadSound(DBDClick3);
	UnloadSound(DBDClick4);
	
	UnloadTexture(background);
	UnloadTexture(achievementsbackground);
	UnloadTexture(helpbackground);
	UnloadTexture(achievementsheet);

	UnloadFont(Roboto);
	CloseAudioDevice();
}
