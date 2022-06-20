#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <wrl/client.h>
#include "ComException.h"

class D2DFramework
{
private:
	const LPCWSTR WindowClassName{ L"D2DWindowClass" };

protected:
	HWND mHwnd{};

	Microsoft::WRL::ComPtr<ID2D1Factory>				mspD2DFactory{};
	Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget>		mspRenderTarget{};

protected:
	HRESULT InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height);
	virtual HRESULT InitD2D();
	virtual HRESULT CreateDeviceResources();

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", 
		UINT width = 1024, UINT height = 768);

	virtual void Release();
	virtual int GameLoop();
	virtual void Render();

	void ShowErrorMsg(LPCWSTR msg, HRESULT error = 0, LPCWSTR title = L"Error");

public:
	ID2D1HwndRenderTarget* GetRenderTarget()
	{
		return mspRenderTarget.Get();
	}

public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

