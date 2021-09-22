#pragma once
#include <raylib.h>

void DrawSkillCheck(float angle, Vector2 greatSkillCheckZone, Vector2 goodSkillCheckZone);
void LoadAssets(void);
void UnloadAssets(void);
const int screenWidth = 800;
const int screenHeight = 450;
const int radius = 100;

extern Vector2 middle;