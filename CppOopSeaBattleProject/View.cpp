#include "View.h"

Console* View::console = new Console();

void View::BufferViewedInit()
{
	if (this->bufferViewed)
		delete[] this->bufferViewed;
	this->bufferViewed = new CHAR_INFO[this->size.width * this->size.height];

	WORD attributes = (WORD)this->background << 4 | (WORD)this->foreground;

	for (int i{}; i < this->size.width * this->size.height; i++)
	{
		this->bufferViewed[i].Char.AsciiChar = ' ';
		this->bufferViewed[i].Attributes = attributes;
	}
}


void View::BufferSavedInit()
{
	if (this->bufferSaved)
		delete[] this->bufferSaved;
	this->bufferSaved = new CHAR_INFO[this->size.width * this->size.height];

	COORD bufferSize{ this->size.width, this->size.height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT screenPosition{
		this->position.column,
		this->position.row,
		this->position.column + this->size.width,
		this->position.row + this->size.height };

	bool succes = ReadConsoleOutputA(
		console->Descriptor(),
		this->bufferSaved,
		bufferSize,
		bufferPosition,
		&screenPosition);
}


View::View(Position position,
	Size size,
	Colors background,
	Colors foreground)
	: position{ position },
	size{ size },
	background{ background },
	foreground{ foreground },
	isVisible{ false },
	bufferViewed{ nullptr },
	bufferSaved{ nullptr }{}

View::View(Position position, Size size)
	: View(position, size, Colors::Blue, Colors::White){}

View::View() : View(Position{}, Size{}){}

View::~View()
{
	delete[] bufferViewed;
	delete[] bufferSaved;
}

Console* View::GetConsole()
{
	return console;
}

Position View::GetPosition()
{
	return this->position;
}

int View::Row()
{
	return this->position.row;
}

int View::Column()
{
	return this->position.column;
}

Size View::GetSize()
{
	return this->size;
}

int View::Width()
{
	return this->size.width;
}

int View::Height()
{
	return this->size.height;
}

Colors& View::Background()
{
	return this->background;
}

Colors& View::Foreground()
{
	return this->foreground;
}

bool View::IsVisible()
{
	return this->isVisible;
}

void View::Move(Position position)
{
	bool currentVisible{ this->isVisible };
	if (currentVisible)
		this->Hide();

	this->position = position;

	this->BufferSavedInit();

	if (currentVisible)
		this->Show();
}

void View::Move(int rowDiff, int columnDiff)
{
	int row{ this->position.row + rowDiff };
	int column{ this->position.column + columnDiff };
	this->Move({ row, column });
}

void View::Resize(Size size)
{
	bool currentVisible{ this->isVisible };
	if (currentVisible)
		this->Hide();

	this->size = size;

	this->BufferSavedInit();
	this->BufferViewedInit();

	if (currentVisible)
		this->Show();
}

void View::Resize(double widthScale, double heightScale)
{
	int width = (double)this->size.width * widthScale;
	int height = (double)this->size.height * heightScale;
	this->Resize({ width, height });
}

void View::Show()
{
	COORD bufferSize{ this->size.width, this->size.height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT screenPosition{
		this->position.column,
		this->position.row,
		this->position.column + this->size.width,
		this->position.row + this->size.height };

	this->BufferSavedInit();
	this->BufferViewedInit();

	WriteConsoleOutputA(
		console->Descriptor(),
		this->bufferViewed,
		bufferSize,
		bufferPosition,
		&screenPosition);

	this->isVisible = true;
}

void View::Hide()
{
	COORD bufferSize{ this->size.width, this->size.height };
	COORD bufferPosition{ 0, 0 };
	SMALL_RECT screenPosition{
		this->position.column,
		this->position.row,
		this->position.column + this->size.width,
		this->position.row + this->size.height };

	WriteConsoleOutputA(
		console->Descriptor(),
		this->bufferSaved,
		bufferSize,
		bufferPosition,
		&screenPosition);

	this->isVisible = false;
}


