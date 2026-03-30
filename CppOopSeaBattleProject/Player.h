#pragma once
#include <string>
#include "Field.h"
#include "Platform.h"

class Player
{
protected:
	std::string name;
	Field* battleField;
	std::vector<Ship*> flotilla;
public:
	Player(std::string name);
	Player();

	std::string& Name();
	Field*& BattleField();
	std::vector<Ship*>& Flotilla();

	int FlotillaSize();

	HitType CheckShot(Point point);

	virtual void SetFlotilla() = 0;
	virtual Point Shot() = 0;
};

class HumanPlayer : public Player
{
	IPlayerPlatform* playerPlatform;
public:
	HumanPlayer(std::string name, IPlayerPlatform* playerPlatform);

	void SetFlotilla() override;
	Point Shot() override { return Point{}; }
};

class ComputerPlayer : public Player
{
public:
	void SetFlotilla() override {}
	Point Shot() override { return Point{}; }
};

