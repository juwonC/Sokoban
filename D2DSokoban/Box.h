#pragma once

#include <memory>
#include <list>
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

	D2D1_RECT_F mBoxPosition;

public:
	Box(D2DFramework* pFramework);

	virtual void Draw() override;
	void Move(std::list<std::shared_ptr<Box>>& boxList, WPARAM key);
	bool CheckMove(std::list<std::shared_ptr<Box>>& boxList, WPARAM key);

	inline D2D1_RECT_F GetRect() { return mBoxPosition; }
};

