#pragma once

#include <memory>
#include <vector>
#include "Actor.h"

class ActorSample : public D2DFramework
{
	std::unique_ptr<Actor> mspPlayer;
	std::vector<std::unique_ptr<Actor>> mspWall;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"Sokoban",
		UINT width = 1024, UINT height = 768) override;

	virtual void Release() override;
	virtual void Render() override;
};

