#include "skillcheck_behavior.h"

#include <raylib.h>
#include "globals.h"

#include <cmath>

Vector2 SkillCheck::GetMiddle(void)
{
	Vector2 v;
	v.x = GetScreenWidth()/2;
	v.y = GetScreenHeight()/2;
	return v;
}

void SkillCheck::DrawCircle(void)
{
	DrawCircleLinesV(GetMiddle(), radius, WHITE);
}

void SkillCheck::DrawNeedle(void)
{
	Vector2 lineEnd;
	Vector2 middle = GetMiddle();
	if (state.doctor)
	{
		lineEnd = Vector2 {
			middle.x - std::sin(state.rotation * DEG2RAD) * radius,
			middle.y - std::cos(state.rotation * DEG2RAD) * radius
		};
	}
	else
	{
		lineEnd = Vector2 {
			middle.x + std::sin(state.rotation * DEG2RAD) * radius,
			middle.y - std::cos(state.rotation * DEG2RAD) * radius
		};
	}

	DrawLineEx(
		GetMiddle(),
		lineEnd,
		5.0f,
		RED
	);
}

// https://deadbydaylight.fandom.com/wiki/Skill_Checks

// Skill check (generator):
// Great success zone length: 3%
// Good success zone length: 13%

void GeneratorSkillCheck::GenZone(void)
{
	float generatorSkillCheckGreatWidth = 360.0f * 0.03f;
	float generatorSkillCheckGoodWidth = 360.0f * 0.13f;

	if (state.unnerving) generatorSkillCheckGoodWidth *= 0.4f;

	float generatorSkillCheckTotalWidth = generatorSkillCheckGoodWidth + generatorSkillCheckGreatWidth;

	// Skillchecks start at 4 o'clock and end at 11 o'clock
	int rand = GetRandomValue(360/12*4, 360/12*11-generatorSkillCheckTotalWidth);

	state.greatZone = { (float)rand, (float)rand + generatorSkillCheckGreatWidth };   //Zones for where each skillcheck can spawn
	state.goodZone = { (float)rand + generatorSkillCheckGreatWidth, (float)rand + generatorSkillCheckGoodWidth };
}

// Skill check (healing):
// Great success zone length: 3%
// Good success zone length: 15%

void HealingSkillCheck::GenZone(void)
{
	float generatorSkillCheckGreatWidth = 360.0f * 0.03f;
	float generatorSkillCheckGoodWidth = 360.0f * 0.15f;

	if (state.unnerving) generatorSkillCheckGoodWidth *= 0.4f;

	float generatorSkillCheckTotalWidth = generatorSkillCheckGoodWidth + generatorSkillCheckGreatWidth;

	// Skillchecks start at 4 o'clock and end at 11 o'clock
	int rand = GetRandomValue(360/12*4, 360/12*11-generatorSkillCheckTotalWidth);

	state.greatZone = { (float)rand, (float)rand + generatorSkillCheckGreatWidth };   //Zones for where each skillcheck can spawn
	state.goodZone = { (float)rand + generatorSkillCheckGreatWidth, (float)rand + generatorSkillCheckGoodWidth };
}

// skill check (ruin):
// Same as generator skill check
// Only hitting the great zone gives points

void HexRuinSkillCheck::GenZone(void)
{
	float generatorSkillCheckGreatWidth = 360.0f * 0.03f;
	float generatorSkillCheckGoodWidth = 360.0f * 0.13f;

	if (state.unnerving) generatorSkillCheckGoodWidth *= 0.4f;

	float generatorSkillCheckTotalWidth = generatorSkillCheckGoodWidth + generatorSkillCheckGreatWidth;

	// Skillchecks start at 4 o'clock and end at 11 o'clock
	int rand = GetRandomValue(360/12*4, 360/12*11-generatorSkillCheckTotalWidth);

	state.greatZone = { (float)rand, (float)rand + generatorSkillCheckGreatWidth };   //Zones for where each skillcheck can spawn
	state.goodZone = { (float)rand + generatorSkillCheckGreatWidth, (float)rand + generatorSkillCheckGoodWidth };
}

// Skill check (decisive strike):
// Great success zone length: 7%
// Good success zone length: 0%

void DecisiveStrikeSkillCheck::GenZone(void)
{
	float decisiveStrikeSkillCheckGreatWidth = 360.0f * 0.07f;

	// In reality, Unnerving Presense doesn't actually affect this
	// But it does here, because why not.
	if (state.unnerving) decisiveStrikeSkillCheckGreatWidth *= 0.4f;

	// Decisive strike skillchecks start at 8 o'clock and end at 11 o'clock
	int rand = GetRandomValue(360/12*8, 360/12*11-decisiveStrikeSkillCheckGreatWidth);

	state.greatZone = { (float)rand, (float)rand + decisiveStrikeSkillCheckGreatWidth };   //Zones for where each skillcheck can spawn
	state.goodZone = { 0.0f, 0.0f }; // No good zone for decisive strike
}

void GeneratorSkillCheck::DrawSkillcheck(void)
{
	DrawCircle();

	if (state.doctor)
	{
		zone doctorGreat 
		{
			270.0f - state.greatZone.begin - (state.greatZone.end - state.greatZone.begin),
			270.0f - state.greatZone.begin
		};
		zone doctorGood
		{
			270.0f - state.goodZone.begin - (state.goodZone.end - state.goodZone.begin),
			270.0f - state.goodZone.begin
		};

		DrawRing(GetMiddle(), radius - 5, radius + 5, doctorGreat.begin, doctorGreat.end, 15, WHITE);
		DrawRing(GetMiddle(), radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(GetMiddle(), radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, WHITE); // Drawing of main circle and needle
	}
	else
	{
		DrawRing(GetMiddle(), radius - 5, radius + 5, state.greatZone.begin-90.0f, state.greatZone.end-90.0f, 15, WHITE);
		DrawRing(GetMiddle(), radius - 5, radius + 5, state.goodZone.begin-90.0f, state.goodZone.end-90.0f, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(GetMiddle(), radius - 5, radius + 5, state.goodZone.begin-90.0f, state.goodZone.end-90.0f, 15, WHITE); // Drawing of main circle and needle
	}
	DrawNeedle();
}

void HealingSkillCheck::DrawSkillcheck(void)
{
	DrawCircle();

	if (state.doctor)
	{
		zone doctorGreat 
		{
			270.0f - state.greatZone.begin - (state.greatZone.end - state.greatZone.begin),
			270.0f - state.greatZone.begin
		};
		zone doctorGood
		{
			270.0f - state.goodZone.begin - (state.goodZone.end - state.goodZone.begin),
			270.0f - state.goodZone.begin
		};

		DrawRing(GetMiddle(), radius - 5, radius + 5, doctorGreat.begin, doctorGreat.end, 15, WHITE);
		DrawRing(GetMiddle(), radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(GetMiddle(), radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, WHITE); // Drawing of main circle and needle
	}
	else
	{
		DrawRing(GetMiddle(), radius - 5, radius + 5, state.greatZone.begin-90.0f, state.greatZone.end-90.0f, 15, WHITE);
		DrawRing(GetMiddle(), radius - 5, radius + 5, state.goodZone.begin-90.0f, state.goodZone.end-90.0f, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(GetMiddle(), radius - 5, radius + 5, state.goodZone.begin-90.0f, state.goodZone.end-90.0f, 15, WHITE); // Drawing of main circle and needle
	}
	DrawNeedle();
}

void HexRuinSkillCheck::DrawSkillcheck(void)
{
	DrawCircle();

	if (state.doctor)
	{
		zone doctorGreat
		{
			270.0f - state.greatZone.begin - (state.greatZone.end - state.greatZone.begin),
			270.0f - state.greatZone.begin
		};
		zone doctorGood
		{
			270.0f - state.goodZone.begin - (state.goodZone.end - state.goodZone.begin),
			270.0f - state.goodZone.begin
		};

		DrawRing(GetMiddle(), radius - 5, radius + 5, doctorGreat.begin, doctorGreat.end, 15, RED);
		DrawRing(GetMiddle(), radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(GetMiddle(), radius - 5, radius + 5, doctorGood.begin, doctorGood.end, 15, RED); // Drawing of main circle and needle
	}
	else
	{
		DrawRing(GetMiddle(), radius - 5, radius + 5, state.greatZone.begin-90.0f, state.greatZone.end-90.0f, 15, RED);
		DrawRing(GetMiddle(), radius - 5, radius + 5, state.goodZone.begin-90.0f, state.goodZone.end-90.0f, 15, BLACK); // Drawing of main circle and needle
		DrawRingLines(GetMiddle(), radius - 5, radius + 5, state.goodZone.begin-90.0f, state.goodZone.end-90.0f, 15, RED); // Drawing of main circle and needle
	}
	DrawNeedle();
}

void DecisiveStrikeSkillCheck::DrawSkillcheck(void)
{
	Vector2 middle = GetMiddle();

	DrawCircle();
	if (state.doctor)
	{
		zone doctorGreat
		{
			270.0f - state.greatZone.begin - (state.greatZone.end - state.greatZone.begin),
			270.0f - state.greatZone.begin
		};
		DrawRing(middle, radius - 5, radius + 5, doctorGreat.begin, doctorGreat.end, 15, WHITE);
	}
	else
	{
		DrawRing(middle, radius - 5, radius + 5, state.greatZone.begin-90.0f, state.greatZone.end-90.0f, 15, WHITE);
	}
	DrawNeedle();
}


void GeneratorSkillCheck::OnGood(void)
{
	PlaySound(goodSkillCheck);
}
void GeneratorSkillCheck::OnGreat(void)
{
	PlaySound(greatSkillCheck);
}
void GeneratorSkillCheck::OnMiss(void)
{
	PlaySound(failedSkillCheck);
}

void HealingSkillCheck::OnGood(void)
{
	PlaySound(goodSkillCheck);
}
void HealingSkillCheck::OnGreat(void)
{
	PlaySound(greatSkillCheck);
}
void HealingSkillCheck::OnMiss(void)
{
	PlaySound(failedSkillCheck);
}

void HexRuinSkillCheck::OnGood(void)
{
	PlaySound(sparks);
}
void HexRuinSkillCheck::OnGreat(void)
{
	PlaySound(greatSkillCheck);
}
void HexRuinSkillCheck::OnMiss(void)
{
	PlaySound(failedSkillCheck);
}

void DecisiveStrikeSkillCheck::OnGood(void)
{
	// nop
}
void DecisiveStrikeSkillCheck::OnGreat(void)
{
	PlaySound(greatSkillCheck);
}
void DecisiveStrikeSkillCheck::OnMiss(void)
{
	// nop
}
