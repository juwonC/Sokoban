#include <windows.h>
#include "Game.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd )
{
	int result{};
	
	try
	{
		Game myFramework;
		
		if (SUCCEEDED(myFramework.Initialize(hInstance)))
		{
			result = myFramework.GameLoop();
		}
	}
	catch (const com_exception& e)
	{
		static wchar_t wstr[64] = {};
		size_t len;

		mbstowcs_s(&len, wstr, e.what(), 64);
		MessageBox(nullptr, wstr, L"DirectX Exception", MB_ICONEXCLAMATION | MB_OK);
	}

	return result;
}