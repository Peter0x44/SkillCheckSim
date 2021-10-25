#include <fstream>

#include <raylib.h>
#include <extras/raygui.h>

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
		scores.normalcombo = 0;
		scores.normalscore = 0;
		scores.normalmissed = 0;
		scores.normalmaxcombo = 0;

		scores.dscombo = 0;
		scores.dsscore = 0;
		scores.dsmissed = 0;
		scores.dsmaxcombo = 0;

		scores.hexcombo = 0;
		scores.hexscore = 0;
		scores.hexmissed = 0;
		scores.hexmaxcombo = 0;

	}

	printf("%d:,%d:,%d:,%d:", scores.normalscore, scores.normalcombo, scores.normalmissed, scores.normalmaxcombo);

	boolforachievements[hit10skillchecksinarow] = (scores.greatskillcheckhit <= 10 && scores.normalmaxcombo <= 10);
	boolforachievements[miss50skillchecksinarow] = (scores.normalmissed <= 50 || scores.dsmissed <= 50 || scores.hexmissed <= 50);
	boolforachievements[hit50greatskillchecks] = (scores.greatskillcheckhit <= 50);
	boolforachievements[miss10skillchecks] = (scores.normalmissed <= 10);
	boolforachievements[hit50greatskillchecksinarow] = (scores.greatskillcheckhitinarow <= 50);
	boolforachievements[hit200greatskillchecksinarow] = (scores.greatskillcheckhitinarow <= 200);
	boolforachievements[hit500skillchecksoverall] = (scores.greatskillcheckhit + scores.goodskillcheckhit <= 500);
	
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
	for (int i = 0; i < 8; ++i) //CYCLES THROUGH ARRAY
	{
		if (boolforachievements[i])
		{
			DrawTextEx(Roboto, achievements[i], Vector2{ 45, float(55 + i * 35) }, 30, 1, RED);
		}
		else 
		{
			DrawTextEx(Roboto, achievements[i], Vector2{ 45, float(55 + i * 35) }, 30, 1, BLACK); //DRAWNS ALL ACHIEVEMENTS FROM ARRAY IN #ACHIEVEMENTS.H

		}
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