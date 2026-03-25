#pragma once
#include <string>
#include "Field.h"

class Player
{
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
public:
	void SetFlotilla() override {}
	Point Shot() override { return Point{}; }
};

class ComputerPlayer : public Player
{
public:
	void SetFlotilla() override {}
	Point Shot() override { return Point{}; }
};

