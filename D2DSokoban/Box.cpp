#include "Box.h"
#include <random>

Box::Box(D2DFramework* pFramework) : Actor(pFramework, L"Data/box.png")
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> x(1, 11);
	std::uniform_int_distribution<int> y(1, 6);

	mX = BOX_X + x(gen) * BOX_SIZE;
	mY = BOX_Y + y(gen) * BOX_SIZE;
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
}
