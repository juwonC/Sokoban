#include <string>
#include "Player.h"
#include "BitmapManager.h"
#include <sstream>

Player::Player(D2DFramework* pFramework) : Actor(pFramework, L"Data/player_front.png")
{
	mX = X;
	mY = Y;
	
	mDirection = Direction::Front;
	
	mPlayerPosition.bottom = mY + BOX_SIZE;
	mPlayerPosition.left = mX;
	mPlayerPosition.right = mX + BOX_SIZE;
	mPlayerPosition.top = mY;

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

		case Direction::Right:
			mpTemp = mpRight;
			break;

		case Direction::Back:
			mpTemp = mpBack;
			break;

		case Direction::Left:
			mpTemp = mpLeft;
			break;
	}

	D2D1_RECT_F rect{
		0.0f, 0.0f,
		static_cast<float>(0.0f + size.width),
		static_cast<float>(0.0f + size.height)
	};

	auto matTranslate = D2D1::Matrix3x2F::Translation(mX, mY);

	pRT->SetTransform(matTranslate);
	pRT->DrawBitmap(mpTemp, rect, mOpacity);
}

void Player::Move()
{
}
