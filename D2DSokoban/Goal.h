#pragma once

#include <memory>
#include <list>
#include "Actor.h"

class Goal : public Actor
{
protected:
	const float GOAL_X{ 100.0f };
	const float GOAL_Y{ 164.0f };
	const float GOAL_SIZE{ 64.0f };

public:
	Goal(D2DFramework* pFramework);

	virtual void Draw() override;
};

