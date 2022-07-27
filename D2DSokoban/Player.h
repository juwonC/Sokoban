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
protected:
	const float TOP{ 164.0f };
	const float BOTTOM{ 612.0f };
	const float LEFT{ 100.0f };
	const float RIGHT{ 868.0f };
	const float X{ 100.0f };
	const float Y{ 164.0f };
	const float BOX_SIZE{ 64.0f };

	D2D1_RECT_F mPlayerPosition;

	ID2D1Bitmap* mpBack;
	ID2D1Bitmap* mpRight;
	ID2D1Bitmap* mpLeft;
	ID2D1Bitmap* mpTemp;

	Direction mDirection;

public:
	Player(D2DFramework* pFramework);

	virtual void Draw() override;
	void Move(WPARAM key);
};

