#pragma once

#include <raylib.h>

struct zone
{
	float begin;
	float end;
};

struct SkillCheckState
{
	bool doctor;
	bool unnerving;
	zone goodZone;
	zone greatZone;
	float rotation;
};

constexpr float radius = 100.0f;

class SkillCheck
{
public:
	virtual void GenZone(void) = 0;
	virtual void DrawSkillcheck(void) = 0;

	virtual void OnGood(void) = 0;
	virtual void OnGreat(void) = 0;
	virtual void OnMiss(void) = 0;

	SkillCheck(SkillCheckState& state_) : state(state_) {}
	virtual ~SkillCheck(void) = default;
protected:
	SkillCheckState& state;
	Vector2 GetMiddle(void);
	void DrawNeedle(void);
	void DrawCircle(void);
private:
};

class GeneratorSkillCheck : public SkillCheck
{
	void GenZone(void) override;
	void DrawSkillcheck(void) override;

	using SkillCheck::SkillCheck;

	void OnGood(void) override;
	void OnGreat(void) override;
	void OnMiss(void) override;
};

class HealingSkillCheck : public SkillCheck
{
	void GenZone(void) override;
	void DrawSkillcheck(void) override;

	using SkillCheck::SkillCheck;

	void OnGood(void) override;
	void OnGreat(void) override;
	void OnMiss(void) override;
};

class HexRuinSkillCheck : public SkillCheck
{
	void GenZone(void) override;
	void DrawSkillcheck(void) override;

	using SkillCheck::SkillCheck;

	void OnGood(void) override;
	void OnGreat(void) override;
	void OnMiss(void) override;
};

class DecisiveStrikeSkillCheck : public SkillCheck
{
	void GenZone(void) override;
	void DrawSkillcheck(void) override;

	using SkillCheck::SkillCheck;

	void OnGood(void) override;
	void OnGreat(void) override;
	void OnMiss(void) override;
};
