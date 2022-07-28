#pragma once
#include "Actor.h"

class Box : public Actor
{
protected:
	const float TOP{ 164.0f };
	const float BOTTOM{ 612.0f };
	const float LEFT{ 100.0f };
	const float RIGHT{ 868.0f };
	const float BOX_X{ 100.0f };
	const float BOX_Y{ 164.0f };
	const float BOX_SIZE{ 64.0f };

public:
	Box(D2DFramework* pFramework);

	virtual void Draw() override;
};

