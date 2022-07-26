#pragma once
#include <memory>
#include <list>
#include "D2DFramework.h"
#include "ComException.h"
#include "Actor.h"
#include "Player.h"

class Game : public D2DFramework
{
protected:
	const float GAME_COLUMN{ 15.0f };
	const float GAME_ROW{ 10.0f };
	const float BEGIN_X{ 35.0f };
	const float BEGIN_Y{ 100.0f };
	const float BOX_SIZE{ 64.0f };
	
	std::unique_ptr<Actor> mspBackGround;
	std::unique_ptr<Player> mspPlayer;
	std::list<std::shared_ptr<Actor>> mspWall;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"Sokoban",
		UINT width = 1024, UINT height = 800) override;

	virtual void Release() override;
	virtual void Render() override;
	virtual int GameLoop() override;

private:
	void CreateSokoban();
};

