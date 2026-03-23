#pragma once
#include "Player.h"

class Game
{
	std::vector<Player*> players;
	bool currentPlayer{ false };
public:
	Game();

	void Setup();
	void Process();
};

