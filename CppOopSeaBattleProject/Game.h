#pragma once
#include "Player.h"
#include "Platform.h"

class Game
{
	std::vector<Player*> players;
	bool currentPlayer{ false };

	Platform* platform;
public:
	Game(Platform* platform);

	void Setup();
	void Process();
};

