#include <fstream>

#include <raylib.h>
#include <extras/raygui.h>
#include <cstring>

#include "achievements.h"
#include "globals.h"
#include "skillcheck.h"
#include "settings.h"

settingsscreen::settingsscreen(void)
{

}

settingsscreen::~settingsscreen(void)
{

}

void settingsscreen::render()
{
	DrawRectangleRounded(Backboard, 0.1, 0, RAYWHITE);
	
	backbuttonpressed = GuiButton(backbutton, "Back"); //BACK BUTTON DRAWN
	disablesoundpressed = GuiButton(disablesoundsbutton, "Disable Sound");
	DrawTextEx(Roboto, "settings", Vector2{ (float)screenWidth / 2 - MeasureTextEx(Roboto ,"achievements", 20, 1).x / 2, 10 }, 20, 1, BLACK);
	
	//if (disablesoundpressed) GuiSetState(GUI_STATE_FOCUSED);
	//disablesoundpressed = GuiButton(disablesoundsbutton, "Disable All Sounds");
	//GuiSetState(GUI_STATE_NORMAL);
	
	//if (!disablesoundpressed) GuiSetState(GUI_STATE_FOCUSED);
	//backbuttonpressed = GuiButton(backbutton, "Back");
	//GuiSetState(GUI_STATE_NORMAL);
}

void settingsscreen::logic()
{
	if (backbuttonpressed)
	{
		PlaySound(DBDClick4);
		setnextstate(gamestates::skillcheckscreen); //SETS SCREEN BACK TO SKILL CHECK SCREEN
	}

}