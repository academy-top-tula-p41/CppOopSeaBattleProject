#include "ConsolePlatform.h"

std::string GameConsolePlatform::SetupGame()
{
    View* welcomeView = new View({ rowStart, columnStart },
        { fieldSize * cellSize * widthRate, cellSize * 4 },
        Colors::Blue, Colors::White);
    
    welcomeView->Show();

    welcomeView->GetConsole()->WritePosition(
        { rowStart + margin, columnStart + margin }, "Input Player's name:");

    View* textBlock = new View({ rowStart + 2 * margin, columnStart + margin },
        { fieldSize * cellSize * widthRate - 2 * margin, 1 },
        Colors::Black, Colors::White);
    textBlock->Show();

    textBlock->GetConsole()->CursorPosition({ rowStart + 2 * margin, columnStart + margin });
    std::string name;
    std::getline(std::cin, name);

    textBlock->Hide();

    //welcomeView->GetConsole()->GetChar();

    return name;
}

void PlayerConsolePlatform::FieldShow(std::string name)
{
    int fieldWidth{ (fieldSize + margin) * cellSize * widthRate };
    int fieldHeight{ (fieldSize + margin) * cellSize };

    View* fieldView = new View({ rowStart, columnStart },
        { fieldWidth, fieldHeight },
        Colors::Blue, Colors::White);
    fieldView->Show();


    fieldView->GetConsole()->WritePosition(
        Position{ rowStart, columnStart + (fieldWidth - (int)name.length()) / 2 },
        name);

    int row{ rowStart + cellSize };
    for (int i{}; i < fieldSize; i++)
    {
        fieldView->GetConsole()->WriteWidthPosition(
            { row, columnStart + (i + 1) * cellSize * widthRate + margin },
            cellSize,
            std::string(1, (char)('A' + i)));
    }

    int column{ columnStart + cellSize };
    for (int i{}; i < fieldSize; i++)
    {
        fieldView->GetConsole()->WriteWidthPosition(
            { rowStart + (i + 1) * cellSize + margin, column },
            cellSize,
            std::to_string(i + 1));
    }

    for (int line{}; line < fieldSize * cellSize; line++)
        fieldView->GetConsole()->WritePosition(
            { rowStart + margin + line + 1, columnStart + margin * cellSize },
            std::string(fieldSize * cellSize * widthRate, (char)GameChar::Water));
}

int PlayerConsolePlatform::SelectShip()
{
    int fieldWidth{ (fieldSize + margin) * cellSize * widthRate };
    int currentShip{ 0 };
    bool isNotOk;
    int index{};

    if (!shipCounts[currentShip])
    {
        isNotOk = true;
        for (index = currentShip + 1; index < shipCounts.size(); index++)
        {
            if (shipCounts[index])
            {
                isNotOk = false;
                break;
            }
        }
        if (!isNotOk)
            currentShip = index;
    }

    for (int size{}; size < shipCounts.size(); size++)
    {
        Colors backColor = (size == currentShip) ? Colors::Blue : Colors::Green;

        View* shipSelect = new View(
            { rowStart + size * 2 * cellSize , columnStart + fieldWidth + 3 * margin * cellSize },
            { (size + 1) * cellSize * widthRate, cellSize },
            backColor, Colors::White);
        shipSelect->Show();
        shipSelect->GetConsole()->WritePosition(
            { rowStart + size * 2 * cellSize , columnStart + fieldWidth + 2 * margin * cellSize },
            std::to_string(shipCounts[size]));
    }

    return 0;
}

std::vector<Ship*> PlayerConsolePlatform::SetFlotilla(std::string name)
{
    this->FieldShow(name);

    this->SelectShip();


    return std::vector<Ship*>();
}
