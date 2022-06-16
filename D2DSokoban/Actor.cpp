#include "Actor.h"

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename) :
	mpFramework{ pFramework },
	mX{}, mY{}, mOpacity{ 1.0f }
{
	LoadWICImage(filename);
}

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename, 
	float x, float y, float opacity) : Actor(pFramework, filename)
{
	mX = x;
	mY = y;
	mOpacity = opacity;
}

Actor::~Actor()
{
	mspBitmap.ReleaseAndGetAddressOf();
}

HRESULT Actor::LoadWICImage(LPCWSTR filename)
{
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;
	HRESULT hr{};

	auto pWICFactory{ mpFramework->GetWICFactory() };
	if (pWICFactory == nullptr)
	{
		return E_FAIL;
	}
	
	// 디코더 생성
	hr = pWICFactory->CreateDecoderFromFilename(
		filename,
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
	hr = mpFramework->GetRenderTarget()->CreateBitmapFromWicBitmap(
		converter.Get(),
		mspBitmap.ReleaseAndGetAddressOf()
	);
	ThrowIfFailed(hr);

	return S_OK;
}

void Actor::Draw(float x, float y, float opacity)
{
	auto size{ mspBitmap->GetPixelSize() };
	D2D1_RECT_F rect{
		x, y,
		static_cast<float>(x + size.width),
		static_cast<float>(y + size.height)
	};

	mpFramework->GetRenderTarget()->DrawBitmap(
		mspBitmap.Get(),
		rect,
		opacity
	);
}

void Actor::Draw()
{
	Draw(mX, mY, mOpacity);
}
