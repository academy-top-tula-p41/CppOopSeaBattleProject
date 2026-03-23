#include "Field.h"
#include "Player.h"

Field::Field()
{
	for (int row{}; row < this->size; row++)
	{
		std::vector<Cell*> line;
		for (int column{}; column < this->size; column++)
			line.push_back(new Cell(row, column));
		this->cells.push_back(line);
	}
}

void Field::SetCellType(Point point, CellType type)
{
	cells[point.row][point.column]->Type() = type;
}

void Field::SetCellType(int row, int column, CellType type)
{
	this->SetCellType(Point{ row, column }, type);
}

void Field::SetCellShot(Point point)
{
	this->cells[point.row][point.column]->IsShot() = true;
}

void Field::SetCellShot(int row, int column)
{
	this->SetCellShot(Point{ row, column });
}

Cell*& Field::GetCell(Point point)
{
	return cells[point.row][point.column];
}

Cell*& Field::GetCell(int row, int column)
{
	return this->GetCell(Point{ row, column });
}

void Field::SetShips(std::vector<Ship*> flotilla)
{
	for (Ship* ship : flotilla)
	{
		int row{ ship->Row() };
		int column{ ship->Column() };
		for (int s{}; s < ship->Size(); s++)
		{
			this->SetCellType(Point{ row, column });
			(ship->Direction() == DirectionShip::Horizontal) ? column++ : row++;
		}
	}
}

HitType Field::CheckShot(Point point)
{
	if (cells[point.row][point.column]->IsShot())
		return HitType::Beside;
	if (cells[point.row][point.column]->Type() == CellType::Water)
		return HitType::Beside;
	if (cells[point.row][point.column]->Type() == CellType::Deck)
		return HitType::Reach;
}
