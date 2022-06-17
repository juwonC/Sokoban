#include "BitmapManager.h"

#pragma comment (lib, "WindowsCodecs.lib")

HRESULT BitmapManager::Initialize(ID2D1HwndRenderTarget* pRT)
{
    if (pRT == nullptr)
    {
        return E_FAIL;
    }

    mpRenderTarget = pRT;
    
    HRESULT hr = ::CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(mspWICFactory.GetAddressOf())
    );
    ThrowIfFailed(hr);

    return hr;
}

void BitmapManager::Release()
{
    for (auto& bitmap : mBitmapResources)
    {
        bitmap.second.Reset();
    }

    mspWICFactory.Reset();
}

HRESULT BitmapManager::LoadWICBitmap(std::wstring filename, ID2D1Bitmap** ppBitmap)
{
    return E_NOTIMPL;
}

ID2D1Bitmap* BitmapManager::LoadBitmap(std::wstring filename)
{
    return nullptr;
}
