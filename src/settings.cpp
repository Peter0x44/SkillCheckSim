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
	disablesoundpressed = GuiButton(disablesoundsbutton, messages[disablesounds]);
	changebackgroundpressed = GuiButton(changebackground, messages2[lol]);
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
	
	
	if (disablesoundpressed) 
	{
		disablesounds = !disablesounds;
		if (disablesounds)
		{
			SetSoundVolume(goodSkillCheck, 0);
			SetSoundVolume(greatSkillCheck, 0);
			SetSoundVolume(skillCheckWarning, 0);
			SetSoundVolume(failedSkillCheck, 0);
			SetSoundVolume(DBDClick, 0);
			SetSoundVolume(DBDClick2, 0);
			SetSoundVolume(DBDClick3, 0);
			SetSoundVolume(DBDClick4, 0);
		}
		else
		{
			SetSoundVolume(goodSkillCheck, 1);
			SetSoundVolume(greatSkillCheck, 1);
			SetSoundVolume(skillCheckWarning, 1);
			SetSoundVolume(failedSkillCheck, 1);
			SetSoundVolume(DBDClick, 1);
			SetSoundVolume(DBDClick2, 1);
			SetSoundVolume(DBDClick3, 1);
			SetSoundVolume(DBDClick4, 1);
		}
			
	}

	if (changebackgroundpressed)
	{
		lol = !lol;
		if (lol)
		{
			//blablabla
		}
		else
		{
			//blablabla
		}
	}

	


}