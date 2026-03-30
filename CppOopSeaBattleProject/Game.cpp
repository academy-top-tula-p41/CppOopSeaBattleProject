#include "Game.h"

Game::Game(Platform* platform) 
	: platform{ platform }{}

void Game::Setup()
{
	std::string name = platform->GamePlatform()->SetupGame();

	HumanPlayer* humanPlayer = new HumanPlayer(name, platform->PlayerPlatform());

	ComputerPlayer* computerPlayer = new ComputerPlayer();

	players.push_back(humanPlayer);
	players.push_back(computerPlayer);

	for (Player* player : players)
		player->SetFlotilla();
}

void Game::Process()
{
	HitType hit;
	Point point;

	while (true)
	{
		point = players[currentPlayer]->Shot();

		hit = players[!currentPlayer]->CheckShot(point);

		if (hit == HitType::Destroy)
		{
			if (players[!currentPlayer]->FlotillaSize() == 0)
				break;
		}

		if (hit == HitType::Beside)
			currentPlayer = !currentPlayer;
	}
}
