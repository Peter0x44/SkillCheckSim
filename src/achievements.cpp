#include <fstream>

#include <raylib.h>
#include <extras/raygui.h>

#include "achievements.h"
#include "globals.h"
#include "skillcheck.h"

achievementscreen::achievementscreen(void)
{
	std::ifstream file("file.bin", std::ifstream::binary);

	if (file.is_open())
	{
		file.read((char*)&scores, sizeof(scores));
	}

	printf("%d:,%d:,%d:", scores.score, scores.combo, scores.missed);

	//if (scores.greatskillcheckhit == 10 && scores.maxcombo == 10) {
	//	hit10skillchecksinarow = true;
	//	printf("hello");
	//}

	//if (scores.goodskillcheckhit == 10 && scores.maxcombo == 10) {
	//	hit10skillchecksinarow = true;
	//	printf("hello");
	//}
}

achievementscreen::~achievementscreen(void)
{

}

void achievementscreen::render()
{

	DrawRectangleRounded(Backboard, 0.1, 0, RAYWHITE);
	DrawTextEx(Roboto, "achievements", Vector2{ (float)screenWidth / 2 - MeasureTextEx(Roboto ,"achievements", 20, 1).x / 2, 10 }, 20, 1, BLACK);
	backbuttonpressed = GuiButton(backbutton, "Back"); //BACK BUTTON DRAWN
	for (int i = 0; i < 8; ++i) //CYCLES THROUGH ARRAY
	{
		DrawTextEx(Roboto, achievements[i], Vector2{45, float(55 + i * 35)}, 30, 1, BLACK); //DRAWNS ALL ACHIEVEMENTS FROM ARRAY IN #ACHIEVEMENTS.H
	}
	//DrawTexture(achievementsbackground, 0, 0, WHITE);
}

void achievementscreen::logic()
{

	if (backbuttonpressed) 
	{
		PlaySound(DBDClick4);
		setnextstate(gamestates::skillcheckscreen); //changes screen back to skillcheckscreen
	}

}