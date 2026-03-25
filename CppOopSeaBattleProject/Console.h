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

	int GetChar();
	int KeyPressed();

	void Foreground(Colors color);
	void Background(Colors color);
};

