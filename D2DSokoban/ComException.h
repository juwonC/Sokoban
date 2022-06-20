#pragma once

#include <windows.h>
#include <exception>
#include <stdio.h>
#include <string>

class com_exception : public std::exception
{
private:
	HRESULT mResult;
	std::string mDescription;

public:
	com_exception(HRESULT hr) : mResult(hr), mDescription{} {}
	com_exception(HRESULT hr, std::string msg) : mResult(hr), mDescription{ msg } {}

	virtual const char* what() const override
	{
		static char str[512] = {};

		if (mDescription.length() == 0)
		{
			sprintf_s(
				str, "Failure with HRESULT of %08X",
				static_cast<unsigned int>(mResult)
			);
		}
		else
		{
			sprintf_s(str, "Failure with HRESULT of %08X\n\n-> %s",
					static_cast<unsigned int>(mResult), mDescription.c_str()
				);
		}

		return str;
	}
};

inline void ThrowIfFailed(HRESULT hr, std::string msg = "")
{
	if (FAILED(hr))
	{
		throw com_exception(hr, msg);
	}
}

