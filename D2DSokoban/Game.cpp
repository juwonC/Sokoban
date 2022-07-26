#include "Game.h"

HRESULT Game::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr);

	CreateSokoban();
    
    return S_OK;
}

void Game::Release()
{
	mspPlayer.reset();

	for (auto& e : mspGround)
	{
		e.reset();
	}
	mspGround.clear();

	for (auto& e : mspWall)
	{
		e.reset();
	}
	mspWall.clear();
	
	D2DFramework::Release();
}

void Game::Render()
{
    HRESULT hr;

    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	mspBackGround->Draw();

	for (auto& e : mspWall)
	{
		e->Draw();
	}
	for (auto& e : mspGround)
	{
		e->Draw();
	}

    mspPlayer->Draw();

    hr = mspRenderTarget->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

int Game::GameLoop()
{
	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	MSG msg{};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
			if (msg.message == WM_KEYDOWN)
			{
				mspPlayer->Move(msg.wParam);
			}
		}
		else
		{
			Render();
		}
	}

	Release();

	return static_cast<int>(msg.wParam);
}

void Game::CreateSokoban()
{
	float posX{ BEGIN_X }, posY{ BEGIN_Y };

	for (int x = 0; x < GAME_COLUMN; ++x)
	{
		posY = BEGIN_Y;

		for (int y = 0; y < GAME_ROW; ++y)
		{
			if (posX == BEGIN_X || posY == BEGIN_Y ||
				x == GAME_COLUMN - 1 || y == GAME_ROW - 1)
			{
				mspWall.push_back(std::make_shared<Actor>(this, L"Data/game_wall.png", posX, posY));
			}
			else
			{
				mspGround.push_back(std::make_shared<Actor>(this, L"Data/game_ground.png", posX, posY));
			}

			posY += BOX_SIZE;
		}
		posX += BOX_SIZE;
	}
	
	mspBackGround = std::make_unique<Actor>(this, L"Data/bg_blank.png", 0.0f, 0.0f);
	mspPlayer = std::make_unique<Player>(this);
}
