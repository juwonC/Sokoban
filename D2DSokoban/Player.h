#pragma once
#include "Actor.h"

enum class Direction
{
	Front,
	Back,
	Right,
	Left
};

class Player : public Actor
{
private:
	ID2D1Bitmap* mpBack;
	ID2D1Bitmap* mpRight;
	ID2D1Bitmap* mpLeft;
	ID2D1Bitmap* mpTemp;

	Direction mDirection;

public:
	Player(D2DFramework* pFramework);

	virtual void Draw() override;
	void Move();
};

