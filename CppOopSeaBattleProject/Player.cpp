#include "Player.h"

Player::Player(std::string name)
	: name{ name },
	battleField{ new Field() }{ }

Player::Player()
	: Player("Computer"){ }

std::string& Player::Name()
{
	return this->name;
}

Field*& Player::BattleField()
{
	return this->battleField;
}

std::vector<Ship*>& Player::Flotilla()
{
	return this->flotilla;
}

int Player::FlotillaSize()
{
	int size{};
	for (Ship* ship : flotilla)
		if (!ship->IsDead())
			size++;
	return size;
}

HitType Player::CheckShot(Point point)
{
	HitType hit{ battleField->CheckShot(point) };
	battleField->SetCellShot(point);

	if (hit == HitType::Beside)
		return hit;

	for (Ship* ship : flotilla)
	{
		if (ship->IsPoint(point))
		{
			ship->Damage()++;
			if (ship->IsDead())
				return HitType::Destroy;
			else
				return HitType::Wound;
		}
	}
}

HumanPlayer::HumanPlayer(std::string name, 
	IPlayerPlatform* playerPlatform)
	: Player(name), playerPlatform{ playerPlatform } {}

void HumanPlayer::SetFlotilla()
{
	this->flotilla = this->playerPlatform->SetFlotilla(this->Name());
	this->battleField->SetShips(this->flotilla);
}
