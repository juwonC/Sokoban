#include <random>
#include "Box.h"

Box::Box(D2DFramework* pFramework) : Actor(pFramework, L"Data/box.png")
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> x(1, 11);
	std::uniform_int_distribution<int> y(1, 6);

	mX = BOX_X + x(gen) * BOX_SIZE;
	mY = BOX_Y + y(gen) * BOX_SIZE;

	mBoxPosition.bottom = mY + BOX_SIZE;
	mBoxPosition.left = mX;
	mBoxPosition.right = mX + BOX_SIZE;
	mBoxPosition.top = mY;
}

void Box::Draw()
{	
	auto pRT = mpFramework->GetRenderTarget();
	auto size = mpBitmap->GetPixelSize();

	D2D1_RECT_F rect{
		0.0f, 0.0f,
		static_cast<float>(0.0f + size.width),
		static_cast<float>(0.0f + size.height)
	};

	auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);

	pRT->SetTransform(matTranslate);
	pRT->DrawBitmap(mpBitmap, rect, mOpacity);

	mBoxPosition.bottom = mY + BOX_SIZE;
	mBoxPosition.left = mX;
	mBoxPosition.right = mX + BOX_SIZE;
	mBoxPosition.top = mY;
}

// TODO: MOVE
void Box::Move(std::list<std::shared_ptr<Box>>& boxList, WPARAM key)
{
	switch (key)
	{
		case VK_UP:

			if (CheckMove(boxList, key))
			{
				mY -= BOX_SIZE;
			}
			break;

		case VK_RIGHT:

			if (CheckMove(boxList, key))
			{
				mX += BOX_SIZE;
			}
			break;

		case VK_DOWN:

			if (CheckMove(boxList, key))
			{
				mY += BOX_SIZE;
			}
			break;

		case VK_LEFT:

			if (CheckMove(boxList, key))
			{
				mX -= BOX_SIZE;
			}
			break;

		default:
			break;
	}
}

// TODO: CheckMove
bool Box::CheckMove(std::list<std::shared_ptr<Box>>& boxList, WPARAM key)
{
	switch (key)
	{
		case VK_UP:

			for (auto& e : boxList)
			{
				if ((e->GetRect().top == (mY - BOX_SIZE) && e->GetRect().left == mX) || mY == TOP)
				{
					return false;
				}
			}
			break;

		case VK_RIGHT:

			for (auto& e : boxList)
			{
				if ((e->GetRect().left == (mX + BOX_SIZE) && e->GetRect().top == mY) || mX == RIGHT)
				{
					return false;
				}
			}
			break;

		case VK_DOWN:

			for (auto& e : boxList)
			{
				if ((e->GetRect().top == (mY + BOX_SIZE) && e->GetRect().left == mX) || mY == BOTTOM)
				{
					return false;
				}
			}
			break;

		case VK_LEFT:

			for (auto& e : boxList)
			{
				if ((e->GetRect().left == (mX - BOX_SIZE) && e->GetRect().top == mY) || mX == LEFT)
				{
					return false;
				}
			}
			break;

		default:
			break;
	}
	
	return true;
}
