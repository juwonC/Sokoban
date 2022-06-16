#include "ActorSample.h"

HRESULT ActorSample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr);

    mspPlayer = std::make_unique<Actor>((D2DFramework*)this, L"Data/player_01.png", 100.0f, 100.0f);
    
	for (int i = 0; i < 10; ++i)
	{
		mspWall.push_back(std::make_unique<Actor>((D2DFramework*)this, L"Data/block_06.png", i * 64.0f, 0.0f));
	}

    return S_OK;
}

void ActorSample::Release()
{
	for (auto& e : mspWall)
	{
		e.reset();
	}
	mspPlayer.reset();

    D2DFramework::Release();
}

void ActorSample::Render()
{
	HRESULT hr;

	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	mspPlayer->Draw();
	for (auto& e : mspWall)
	{
		e->Draw();
	}

	hr = mspRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}
