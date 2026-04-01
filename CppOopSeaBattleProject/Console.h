#pragma once
#include <Windows.h>
#include <string>
#include <conio.h>

struct Position
{
	int row{};
	int column{};
};

struct Size
{
	int width{};
	int height{};
};

enum class Colors
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	LightGray,
	Gray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

enum class Key
{
	ArrawLeft = 75,
	ArrawRight = 77,
	ArrawUp = 72,
	ArrawDown = 80,

	Enter = 13,
	Space = 32,
	Esc = 27
};

class Console
{
	HANDLE descriptor;
	COORD coordinate{};
	std::string title;
public:
	Console(std::string title = "");

	HANDLE& Descriptor();

	std::string& Title();

	void Clear();

	void CursorPosition(Position position);
	void Write(std::string message);
	void Write(char symbol);
	void WritePosition(Position position, std::string message);
	void WritePosition(Position position, char symbol);

	void WriteWidthPosition(Position position, int width, std::string message);

	int GetChar();
	int KeyPressed();

	void Foreground(Colors color);
	void Background(Colors color);
};

