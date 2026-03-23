#pragma once
#include "Cell.h"

enum class DirectionShip
{
	Horizontal,
	Vertical
};

class Ship
{
	Point point;
	DirectionShip direction;
	int size;
	int damage;
public:
	Ship(Point point, int size, DirectionShip direction);
	Ship(int row, int column, int size, DirectionShip direction);

	Point& Start();
	int& Row();
	int& Column();

	int Size();
	DirectionShip& Direction();
	int& Damage();

	bool IsDead();
	bool IsPoint(Point point);
};

