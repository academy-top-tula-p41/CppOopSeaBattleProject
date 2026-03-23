#include "Cell.h"

Cell::Cell(Point point)
	: point{ point },
	type{ CellType::Water },
	isShot{ false } {}

Cell::Cell(int row, int column)
	: Cell(Point{ row, column }){ }

Cell::Cell()
	: Cell(Point{}){ }

CellType& Cell::Type()
{
	return type;
}

bool& Cell::IsShot()
{
	return isShot;
}


