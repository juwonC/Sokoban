#include <string>
#include "Player.h"
#include "BitmapManager.h"

Player::Player(D2DFramework* pFramework) : Actor(pFramework, L"Data/player_front.png")
{
	mDirection = Direction::Front;
	
	mpBack = BitmapManager::Instance().LoadBitmap(L"Data/player_back.png");
	mpLeft = BitmapManager::Instance().LoadBitmap(L"Data/player_left.png");
	mpRight = BitmapManager::Instance().LoadBitmap(L"Data/player_right.png");
	mpTemp = mpBitmap;
}

void Player::Draw()
{
	auto pRT = mpFramework->GetRenderTarget();
	auto size = mpBitmap->GetPixelSize();

	switch (mDirection)
	{
		case Direction::Front:
			mpTemp = mpBitmap;
			break;

		case Direction::Back:
			mpTemp = mpBack;
			break;

		case Direction::Right:
			mpTemp = mpRight;
			break;

		case Direction::Left:
			mpTemp = mpLeft;
			break;
	}

	D2D1_RECT_F rect{
		mX, mY,
		static_cast<float>(mX + size.width),
		static_cast<float>(mY + size.height)
	};

	pRT->DrawBitmap(mpTemp, rect, mOpacity);
}

void Player::Move()
{
}
