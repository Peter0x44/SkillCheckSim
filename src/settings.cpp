#include <raylib.h>
#include <raygui.h>

#include "globals.h"
#include "gamestates.h"
#include "settings.h"

settingsscreen::settingsscreen(void)
{

}

settingsscreen::~settingsscreen(void)
{
	float volume = disablesounds ? 0.0f : 1.0f;
	SetSoundVolume(goodSkillCheck, volume);
	SetSoundVolume(greatSkillCheck, volume);
	SetSoundVolume(skillCheckWarning, volume);
	SetSoundVolume(failedSkillCheck, volume);
	SetSoundVolume(DBDClick, volume);
	SetSoundVolume(DBDClick2, volume);
	SetSoundVolume(DBDClick3, volume);
	SetSoundVolume(DBDClick4, volume);
}

void settingsscreen::render()
{
	DrawRectangleRounded(Backboard, 0.1f, 0, RAYWHITE);
	
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
