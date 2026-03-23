#include "Ship.h"

Ship::Ship(Point point, int size, DirectionShip direction)
	: point{ point },
	size{ size },
	direction{ direction },
	damage{}{ }

Ship::Ship(int row, int column, int size, DirectionShip direction)
	: Ship(Point{ row, column }, size, direction){ }

Point& Ship::Start()
{
	return this->point;
}

int& Ship::Row()
{
	return this->point.row;
}

int& Ship::Column()
{
	return this->point.column;
}

int Ship::Size()
{
	return this->size;
}

DirectionShip& Ship::Direction()
{
	return this->direction;
}

int& Ship::Damage()
{
	return this->damage;
}

bool Ship::IsDead()
{
	return this->damage == this->size;
}

bool Ship::IsPoint(Point point)
{
	int row = this->point.row;
	int column = this->point.column;

	for (int s{}; s < this->size; s++)
	{
		if (point.row == row && point.column == column)
			return true;
		(direction == DirectionShip::Horizontal) ? column++ : row++;
	}

	return false;
}
