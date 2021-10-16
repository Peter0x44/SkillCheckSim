#include <raylib.h>
#include <extras/raygui.h>

#include "modes.h"
#include "globals.h"

modesscreen::modesscreen(void)
{

}

modesscreen::~modesscreen(void)
{

}

void modesscreen::render()
{
	DrawRectangleRounded(Backboard, 0.1, 0, RAYWHITE);
	DrawTextEx(Roboto, "modes", Vector2{ (float)screenWidth / 2 - MeasureTextEx(Roboto ,"modes", 20, 1).x / 2, 10 }, 20, 1, BLACK);
	backbuttonpressed = GuiButton(backbutton, "Back");
	//ClearBackground(PURPLE);
}

void modesscreen::logic()
{
	if (backbuttonpressed)
	{
		setnextstate(gamestates::skillcheckscreen); //SETS SCREEN BACK TO SKILL CHECK SCREEN
	}

}