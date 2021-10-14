#pragma once

#include "gamestates.h"

class modesscreen: public gamestate
{
private:

public:
	void logic(void) final override;
	void render(void) final override;
	modesscreen(void);
	~modesscreen() final override;
};
