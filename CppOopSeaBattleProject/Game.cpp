#include "Game.h"

Game::Game(Platform* platform) 
	: platform{ platform }{}

std::vector<Player*>& Game::Players()
{
	return this->players;
}

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

	platform->GamePlatform()->ViewGame();

	while (true)
	{
		point = players[currentPlayer]->Shot();
		hit = players[!currentPlayer]->CheckShot(point);

		this->platform->GamePlatform()->ViewShot(point, currentPlayer);

		if (hit == HitType::Destroy)
		{
			if (players[!currentPlayer]->FlotillaSize() == 0)
				break;
		}

		if (hit == HitType::Beside)
			currentPlayer = !currentPlayer;
	}
}
