#include <raylib.h>
#include <extras/raygui.h>

#include "achievements.h"
#include "globals.h"

achievementscreen::achievementscreen(void)
{

}

achievementscreen::~achievementscreen(void)
{

}

void achievementscreen::render()
{

	DrawRectangleRounded(Backboard, 0.1, 0, RAYWHITE);
	DrawTextEx(Roboto, "achievements", Vector2{ (float)screenWidth / 2 - MeasureTextEx(Roboto ,"achievements", 20, 1).x / 2, 10 }, 20, 1, BLACK);
	backbuttonpressed = GuiButton(backbutton, "Back");
	for (int i = 0; i < 8; ++i)
	{
		DrawText(achievements[i], 45, 55 + i * 25, 20, BLACK);
	}
	//DrawTexture(achievementsbackground, 0, 0, WHITE);
}

void achievementscreen::logic()
{
	if (backbuttonpressed) 
	{
		setnextstate(gamestates::skillcheckscreen);
	}


}