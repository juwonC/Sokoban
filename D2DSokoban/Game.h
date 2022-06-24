#pragma once
#include <memory>
#include "D2DFramework.h"
#include "ComException.h"
#include "Actor.h"
#include "Player.h"

class Game : public D2DFramework
{
	std::unique_ptr<Player> mspPlayer;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"Sokoban",
		UINT width = 1024, UINT height = 800) override;

	virtual void Release() override;
	virtual void Render() override;
};

