#include "Game.h"

Game::Game()
{
	HumanPlayer* humanPlayer = new HumanPlayer();
	ComputerPlayer* computerPlayer = new ComputerPlayer();

	players.push_back(humanPlayer);
	players.push_back(computerPlayer);
}

void Game::Setup()
{
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
