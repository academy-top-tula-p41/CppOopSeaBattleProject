#pragma once
#include "Console.h"

class View
{
protected:
	static Console* console;

	Position position;
	Size size;
	Colors background;
	Colors foreground;

	bool isVisible;

	CHAR_INFO* bufferViewed;
	CHAR_INFO* bufferSaved;

	virtual void BufferViewedInit();
	virtual void BufferSavedInit();

public:
	View(Position position,
		Size size,
		Colors background,
		Colors foreground);
	View(Position position, Size size);
	View();

	virtual ~View();

	static Console* GetConsole();

	Position GetPosition();
	int Row();
	int Column();

	Size GetSize();
	int Width();
	int Height();

	Colors& Background();
	Colors& Foreground();

	bool IsVisible();

	virtual void Move(Position position);
	virtual void Move(int rowDiff, int columnDiff);

	virtual void Resize(Size size);
	virtual void Resize(double widthScale, double heightScale);

	virtual void Show();
	virtual void Hide();

};

