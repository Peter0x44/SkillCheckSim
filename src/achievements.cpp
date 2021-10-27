#include <fstream>

#include <raylib.h>
#include <extras/raygui.h>
#include <cstring>

#include "achievements.h"
#include "globals.h"
#include "skillcheck.h"

enum achievementtitle
{
	hit10skillchecksinarow = 0,
	miss50skillchecksinarow,
	hit50greatskillchecks,
	miss10skillchecks,
	hit50greatskillchecksinarow,
	hit200greatskillchecksinarow,
	hit500skillchecksoverall,
	questionmark

};

achievementscreen::achievementscreen(void)
{
	std::ifstream file("file.bin", std::ifstream::binary);

	if (file.is_open())
	{
		file.read((char*)&scores, sizeof(scores));
			
	}
	else
	{
		std::memset(&scores, 0, sizeof(scores));

	}

	printf("%d:,%d:,%d:,%d:", scores.normalscore, scores.normalcombo, scores.normalmissed, scores.normalmaxcombo);

	boolforachievements[hit10skillchecksinarow] = (scores.greatskillcheckhit <= 10 && scores.normalmaxcombo <= 10);
	boolforachievements[miss50skillchecksinarow] = (scores.normalmissed <= 50 || scores.dsmissed <= 50 || scores.hexmissed <= 50);
	boolforachievements[hit50greatskillchecks] = (scores.greatskillcheckhit <= 50);
	boolforachievements[miss10skillchecks] = (scores.normalmissed <= 10);
	boolforachievements[hit50greatskillchecksinarow] = (scores.greatskillcheckhitinarow <= 50);
	boolforachievements[hit200greatskillchecksinarow] = (scores.greatskillcheckhitinarow <= 200);
	boolforachievements[hit500skillchecksoverall] = (scores.greatskillcheckhit + scores.goodskillcheckhit <= 500);
	boolforachievements[questionmark] = (scores.goodskillcheckhit = 500);

	//if (scores.greatskillcheckhit <= 10 && scores.normalmaxcombo <= 10) {
	//	//hit10skillchecksinarow = true;
	//	printf("hello");
	//}

	//if (scores.goodskillcheckhit <= 10 && scores.normalmaxcombo <= 10) {
	//	//hit10skillchecksinarow = true;
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
	//DrawTextEx(Roboto, "Achievements turn Black When Completed!", Vector2{ 25, 400 }, 30, 1, BLACK);
	for (int i = 0; i < 7; ++i) //CYCLES THROUGH ARRAY
	{
		if (boolforachievements[i])
		{
			DrawTexturePro(achievementsheet, Rectangle{ (float)i * 64, 0, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY, 64, 64 }, Vector2{0, 0}, 0, WHITE);
			//DrawTextEx(Roboto, achievements[i], Vector2{ 45, float(55 + i * 35) }, 20, 2, RED);
		}
		else 
		{
			DrawTexturePro(achievementsheet, Rectangle{ (float)i * 64, 64, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY, 64, 64 }, Vector2{ 0, 0 }, 0, WHITE); //DRAWNS ALL ACHIEVEMENTS FROM ARRAY IN #ACHIEVEMENTS.H

		}
	}
	//DrawTexture(achievementsbackground, 0, 0, WHITE);

	for (int i = 0; i < 7; ++i)
	{
		if (boolforachievements[i])
		{
			DrawTexturePro(achievementsheet, Rectangle{ (float)(i + 7) * 64, 0, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY + 68, 64, 64 }, Vector2{ 0, 0 }, 0, WHITE);
			//DrawTextEx(Roboto, achievements[i], Vector2{ 45, float(55 + i * 35) }, 20, 2, RED);
		}
		else
		{
			DrawTexturePro(achievementsheet, Rectangle{ (float)(i + 7) * 64, 64, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY + 68, 64, 64 }, Vector2{ 0, 0 }, 0, WHITE); //DRAWNS ALL ACHIEVEMENTS FROM ARRAY IN #ACHIEVEMENTS.H

		}
	}

	if (achievementshoveredx > -1 && achievementshoveredy > -1)
	{
		DrawTextEx(Roboto, achievementTitle[achievementshoveredx * (achievementshoveredy + 1)], Vector2{ screenWidth / 2 - (float)MeasureTextEx(Roboto, achievementTitle[achievementshoveredx * (achievementshoveredy + 1)], 20, 1).x / 2 , screenHeight / 2 }, 20, 1, RED);
	}

}

void achievementscreen::logic()
{

	if (backbuttonpressed) 
	{
		PlaySound(DBDClick4);
		setnextstate(gamestates::skillcheckscreen); //changes screen back to skillcheckscreen
	}

	int CursorX = GetMouseX();
	int CursorY = GetMouseY();

	printf("%d\n", achievementshoveredx);

	if (CursorX < gridOffsetX || CursorX > gridOffsetX + 68 * 7)
	{
		achievementshoveredx = -1;
	}
	else 
	{
		achievementshoveredx = (CursorX - gridOffsetX) / 68;
	}

	if (CursorY < gridOffsetY || CursorY > gridOffsetY + 68 * 2)
	{
		achievementshoveredy = -1;
	}
	else
	{
		achievementshoveredy = (CursorY - gridOffsetY) / 68;
	}

}