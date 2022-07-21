#include "Game.h"

HRESULT Game::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr);

    mspPlayer = std::make_unique<Player>(this);
    
    return S_OK;
}

void Game::Release()
{
    D2DFramework::Release();
}

void Game::Render()
{
    HRESULT hr;

    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

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
