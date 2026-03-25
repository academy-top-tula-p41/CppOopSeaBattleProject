#include "Platform.h"

Platform::Platform(IGamePlatform* gamePlatform, 
	IPlayerPlatform* playerPlatform)
	: gamePlatform{ gamePlatform },
	playerPlatform{ playerPlatform } {}

IGamePlatform* Platform::GamePlatform()
{
	return this->gamePlatform;
}

IPlayerPlatform* Platform::PlayerPlatform()
{
	return this->playerPlatform;
}
