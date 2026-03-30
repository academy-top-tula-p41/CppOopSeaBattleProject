#include "Console.h"

Console::Console(std::string title)
{
	this->descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA(title.c_str());
}

HANDLE& Console::Descriptor()
{
	return this->descriptor;
}

std::string& Console::Title()
{
	return this->title;
}

void Console::Clear()
{
	system("cls");
}

void Console::CursorPosition(Position position)
{
	coordinate.X = position.column;
	coordinate.Y = position.row;
	SetConsoleCursorPosition(descriptor, coordinate);
}

void Console::Write(std::string message)
{
	LPDWORD writted{};
	WriteConsoleA(descriptor, 
				message.c_str(), 
				message.length(), 
				writted, 
				nullptr);
}

void Console::Write(char symbol)
{
	this->Write(std::string(1, symbol));
}

void Console::WritePosition(Position position, std::string message)
{
	this->CursorPosition(position);
	this->Write(message);
}

void Console::WritePosition(Position position, char symbol)
{
	this->WritePosition(position, std::string(1, symbol));
}

void Console::WriteWidthPosition(Position position, int width, std::string message)
{
	CursorPosition(position);
	Write(std::string(width - message.length(), ' '));
	Write(message);
}

int Console::GetChar()
{
	int key{ _getch() };
	if (key == 0 || key == 0xE0)
		key = _getch();
	return key;
}

int Console::KeyPressed()
{
	return _kbhit();
}

void Console::Foreground(Colors color)
{
	CONSOLE_SCREEN_BUFFER_INFO info{};
	GetConsoleScreenBufferInfo(this->descriptor, &info);
	byte backColor = info.wAttributes & (0b1111 << 4);
	byte foreColor = (int)color;
	SetConsoleTextAttribute(this->descriptor, foreColor | backColor);
}

void Console::Background(Colors color)
{
	CONSOLE_SCREEN_BUFFER_INFO info{};
	GetConsoleScreenBufferInfo(this->descriptor, &info);
	byte foreColor = info.wAttributes & 0b1111;
	byte backColor = (int)color << 4;
	SetConsoleTextAttribute(this->descriptor, foreColor | backColor);
}
