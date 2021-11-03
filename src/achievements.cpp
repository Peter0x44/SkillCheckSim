#include <fstream>

#include <raylib.h>
#include <extras/raygui.h>
#include <cstring>

#include "achievements.h"
#include "globals.h"
#include "skillcheck.h"

enum achievementtitle
{
	get7000bp = 0,
	get32000bp,
	hit50greatskillchecks,
	hit100greatskillchecks,
	hit500greatskillchecks,
	fail50skillchecks,
	fail100skillchecks,
	fail500skillchecks,
	fail1000skillchecks,
	hit5greatskillchecksinarow,
	hit10greatskillchecksinarow,
	play1000skillchecks,
	play3000skillchecks,
	play5000skillchecks,
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

	boolforachievements[get7000bp] = (scores.bloodpoints >= 7000);
	boolforachievements[get32000bp] = (scores.bloodpoints >= 32000);
	boolforachievements[hit50greatskillchecks] = (scores.greatskillcheckhit >= 50);
	boolforachievements[hit100greatskillchecks] = (scores.greatskillcheckhit >= 100);
	boolforachievements[hit500greatskillchecks] = (scores.greatskillcheckhit >= 5000);
	boolforachievements[fail50skillchecks] = (scores.skillchecksmissed >= 50);
	boolforachievements[fail100skillchecks] = (scores.skillchecksmissed >= 100);
	boolforachievements[fail500skillchecks] = (scores.skillchecksmissed >= 500);
	boolforachievements[fail1000skillchecks] = (scores.skillchecksmissed >= 1000);
	boolforachievements[hit5greatskillchecksinarow] = (scores.maxgreatskillcheckshitinarow >= 5);
	boolforachievements[hit10greatskillchecksinarow] = (scores.maxgreatskillcheckshitinarow >= 10);
	boolforachievements[play1000skillchecks] = (scores.totalskillchecks >= 1000);
	boolforachievements[play3000skillchecks] = (scores.totalskillchecks >= 3000);
	boolforachievements[play5000skillchecks] = (scores.totalskillchecks >= 5000);
	boolforachievements[questionmark] = (scores.secretachievement);
}


achievementscreen::~achievementscreen(void)
{
	std::ofstream file("file.bin", std::ofstream::binary);
	if (file.is_open())
	{
		file.write((char*)&scores, sizeof(scores));
	}
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
			DrawTexturePro(achievementsheet, Rectangle{ (float)i * 64, 0, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY, 64, 64 }, Vector2{ 0, 0 }, 0, WHITE);
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
		if (boolforachievements[i+7])
		{
			DrawTexturePro(achievementsheet, Rectangle{ (float)(i + 7) * 64, 0, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY + 68, 64, 64 }, Vector2{ 0, 0 }, 0, WHITE);
			//DrawTextEx(Roboto, achievements[i], Vector2{ 45, float(55 + i * 35) }, 20, 2, RED);
		}
		else
		{
			DrawTexturePro(achievementsheet, Rectangle{ (float)(i + 7) * 64, 64, 64, 64 }, Rectangle{ gridOffsetX + (float)i * 68, (float)gridOffsetY + 68, 64, 64 }, Vector2{ 0, 0 }, 0, WHITE); //DRAWNS ALL ACHIEVEMENTS FROM ARRAY IN #ACHIEVEMENTS.H
		}

	}

	if (boolforachievements[questionmark])
	{
		DrawTexturePro(achievementsheet, Rectangle{ 64*14, 0, 64, 64}, Rectangle{ 50, 50, 64, 64}, Vector2 {0, 0}, 0, WHITE);
	}

	if (achievementshoveredx > -1 && achievementshoveredy > -1)
	{
		DrawTextEx(Roboto, achievementTitle[achievementshoveredx + 7*achievementshoveredy], Vector2{ screenWidth / 2 - (float)MeasureTextEx(Roboto, achievementTitle[achievementshoveredx + 7*achievementshoveredy], 20, 1).x / 2 , screenHeight / 2 }, 20, 1, RED);
		DrawTextEx(Roboto, achievementCondition[achievementshoveredx + 7*achievementshoveredy], Vector2{ screenWidth / 2 - (float)MeasureTextEx(Roboto, achievementCondition[achievementshoveredx + 7*achievementshoveredy], 20, 1).x / 2 , screenHeight / 1.5 }, 20, 1, BLACK);
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


	if (CursorX < gridOffsetX || CursorX > (gridOffsetX + 68 * 7) - 4)
	{
		achievementshoveredx = -1;
	}
	else 
	{
		achievementshoveredx = (CursorX - gridOffsetX) / 68;
	}

	if (CursorY < gridOffsetY || CursorY > (gridOffsetY + 68 * 2) - 4)
	{
		achievementshoveredy = -1;
	}
	else
	{
		achievementshoveredy = (CursorY - gridOffsetY) / 68;
	}

	const char* const tyler = "tyler";
	int key = GetCharPressed();

	while (key > 0)
	{
		if (letterpressed == strlen(tyler)-1)
		{
			boolforachievements[questionmark] = true;
			scores.secretachievement = true;
			letterpressed = 0;
		}
		else if (tyler[letterpressed] == key)
		{
			++letterpressed;
		}
		else
		{
			letterpressed = 0;
		}

		key = GetCharPressed();
	}
}
