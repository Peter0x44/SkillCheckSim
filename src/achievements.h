#pragma once

#include "gamestates.h"

class achievementscreen : public gamestate
{
private:

public:
	void logic(void) final override;
	void render(void) final override;
	achievementscreen(void);
	~achievementscreen() final override;
};