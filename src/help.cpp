#include <raylib.h>
#include <extras/raygui.h>

#include "help.h"
#include "globals.h"

helpscreen::helpscreen(void)
{

}

helpscreen::~helpscreen(void)
{

}

void helpscreen::render()
{
	DrawTexture(helpbackground, 0, 0, WHITE);

	backbuttonpressed = GuiButton(backbutton, "Back"); //BACK BUTTON DRAWN


}

void helpscreen::logic()
{
	if (backbuttonpressed)
	{
		setnextstate(gamestates::skillcheckscreen); //SETS SCREEN BACK TO SKILL CHECK SCREEN
	}

}