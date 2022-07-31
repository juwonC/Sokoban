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

	bool mCheck;
	D2D1_RECT_F mGoalPosition;

	ID2D1Bitmap* mpBoxOnGoal;

public:
	Goal(D2DFramework* pFramework);

	virtual void Draw() override;

	inline D2D1_RECT_F GetRect() { return mGoalPosition; }
	inline void CheckTrue() { mCheck = true; }
	inline bool GetCheck() { return mCheck; }
};

