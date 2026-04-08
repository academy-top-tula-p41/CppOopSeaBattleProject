#pragma once

#include <string>
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
	virtual std::string SetupGame() = 0;
	virtual void ViewGame() = 0;
	virtual void ViewShot(Point point, bool currentPlayer) = 0;
	virtual void GameOver() = 0;
};

class IPlayerPlatform
{
public:
	virtual std::vector<Ship*> SetFlotilla(std::string name) = 0;
	virtual Point Shot() = 0;
};

