#pragma once

#include <vector>
#include "Ship.h"

class IGamePlatform;
class IPlayerPlatform;

class Platform
{
	IGamePlatform* gamePlatform;
	IPlayerPlatform* playerPlatform;
public:
	Platform(IGamePlatform* gamePlatform,
			IPlayerPlatform* playerPlatform);

	IGamePlatform* GamePlatform();
	IPlayerPlatform* PlayerPlatform();
};

class IGamePlatform
{
public:
	virtual void SetupGame() = 0;
	virtual void ViewGame() = 0;
	virtual void GameOver() = 0;
};

class IPlayerPlatform
{
public:
	virtual std::vector<Ship*> SetFlotilla() = 0;
	virtual Point Shot() = 0;
};

