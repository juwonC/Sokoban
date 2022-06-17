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
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;
	HRESULT hr{};

	auto pWICFactory{ mspWICFactory.Get() };
	if (pWICFactory == nullptr)
	{
		return E_FAIL;
	}

	// 디코더 생성
	hr = pWICFactory->CreateDecoderFromFilename(
		filename.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		bitmapDecoder.GetAddressOf()
	);
	ThrowIfFailed(hr);

	// 프레임 획득
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	ThrowIfFailed(bitmapDecoder->GetFrame(0, frame.GetAddressOf()));

	// 포멧 컨버터
	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	ThrowIfFailed(pWICFactory->CreateFormatConverter(converter.GetAddressOf()));

	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0,
		WICBitmapPaletteTypeCustom
	);
	ThrowIfFailed(hr);

	// 변환된 데이터에서 비트맵 생성
	hr = mpRenderTarget->CreateBitmapFromWicBitmap(
		converter.Get(),
		ppBitmap
	);
	ThrowIfFailed(hr);

	return S_OK;
}

ID2D1Bitmap* BitmapManager::LoadBitmap(std::wstring filename)
{
	if (mspWICFactory == nullptr)
	{
		return nullptr;
	}

	ID2D1Bitmap* pBitmap{};
	auto result = mBitmapResources.insert(
		std::pair<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap>>(filename, nullptr)
	);

	if (result.second == true)
	{
		auto spBitmap = Microsoft::WRL::ComPtr<ID2D1Bitmap>();
		LoadWICBitmap(filename, spBitmap.GetAddressOf());
		result.first->second = spBitmap;
	}
	
	pBitmap = result.first->second.Get();

	return pBitmap;
}
