#pragma once

#include <iostream>
#include <array>
#include <numeric>

#include "Console.h"
#include "View.h"
#include "Platform.h"

enum class GameChar
{
	Water = 177,
	Deck = 219
};

class GameConsolePlatform : public IGamePlatform
{
	const int cellSize{ 2 };
	const int fieldSize{ 10 };
	const int margin{ 2 };
	const int widthRate{ 2 };
	const int rowStart{ 3 };
	const int columnStart{ 5 };
public:
	std::string SetupGame() override;
	void ViewGame() override {};
	void GameOver() override {};
};

class PlayerConsolePlatform : public IPlayerPlatform
{
	const int cellSize{ 2 };
	const int fieldSize{ 10 };
	const int margin{ 2 };
	const int widthRate{ 2 };
	const int rowStart{ 3 };
	const int columnStart{ 5 };

	std::vector<Ship*> flotilla;
	std::array<View*, 4> shipViews;
	std::array<int, 4> shipCounts{ 4, 3, 2, 1 };

	void FieldShow(std::string name);
	void ShipsShow();

	int SelectShip();
	Ship* SetShip(int size);
	bool IsSetShip(Ship* ship);

public:
	PlayerConsolePlatform();

	std::vector<Ship*> SetFlotilla(std::string name) override;
	Point Shot() override { return Point(); };
};

