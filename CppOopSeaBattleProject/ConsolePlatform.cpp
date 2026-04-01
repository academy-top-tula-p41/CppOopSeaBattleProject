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

void PlayerConsolePlatform::ShipsShow()
{
    int top{ rowStart + margin + 1 };
    int left{ columnStart + margin * cellSize };

    for (Ship* ship : this->flotilla)
    {
        int row{ top + ship->Row() * cellSize };
        int column{ left + ship->Column() * cellSize * widthRate };
        int width{ ship->Size() * cellSize * widthRate };
        int height{ cellSize };

        if (ship->Direction() == DirectionShip::Vertical)
        {
            int w{ width };
            width = height * 2;
            height = w / 2;
        }

        View* shipView = new View(
            { row, column },
            { width, height },
            Colors::Green,
            Colors::White);
        shipView->Show();
    }
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
        if (!shipCounts[size])
            backColor = Colors::Magenta;
        
        shipViews[size]->Background() = backColor;
        shipViews[size]->Show();

        View::GetConsole()->Background(Colors::Black);
        View::GetConsole()->WritePosition(
            { rowStart + size * 2 * cellSize , columnStart + fieldWidth + 2 * margin * cellSize },
            std::to_string(shipCounts[size]));
    }

    Key key;
    bool isSelect{ false };

    while (true)
    {
        if (View::GetConsole()->KeyPressed())
        {
            key = (Key)View::GetConsole()->GetChar();

            switch (key)
            {
            case Key::ArrawUp:
            case Key::ArrawLeft:
                isNotOk = true;
                for(index = currentShip - 1; index >= 0; index-- )
                    if (shipCounts[index])
                    {
                        isNotOk = false;
                        break;
                    }
                if (!isNotOk)
                    currentShip = index;
                break;

            case Key::ArrawRight:
            case Key::ArrawDown:
                isNotOk = true;
                for (index = currentShip + 1; index < shipViews.size(); index++)
                    if (shipCounts[index])
                    {
                        isNotOk = false;
                        break;
                    }
                if (!isNotOk)
                    currentShip = index;
                break;

            case Key::Enter:
            case Key::Space:
                isSelect = true;
                break;

            case Key::Esc:
                break;
            default:
                break;
            }

            if (isSelect) break;

            for (int size{}; size < shipCounts.size(); size++)
            {
                Colors backColor = (size == currentShip) ? Colors::Blue : Colors::Green;
                if (!shipCounts[size])
                    backColor = Colors::Magenta;

                shipViews[size]->Background() = backColor;
                shipViews[size]->Show();
            }
        }
    }

    return currentShip;
}

Ship* PlayerConsolePlatform::SetShip(int size)
{
    int top{ rowStart + margin + 1 };
    int left{ columnStart + margin * cellSize };
    int right{ left + fieldSize * cellSize * widthRate };
    int bottom{ top + fieldSize * cellSize };

    int width{ size * cellSize * widthRate };
    int height{ cellSize };

    int row{ top };
    int column{ left };
    bool direction{ false };

    int rowShip{}, columnShip{};

    Ship* ship{ nullptr };
    

    View* shipView = new View({ row, column },
        { width, height },
        Colors::Magenta, 
        Colors::White);

    shipView->Show();

    Key key;
    bool isSet{ false };

    while (true)
    {
        isSet = false;
        if (View::GetConsole()->KeyPressed())
        {
            key = (Key)View::GetConsole()->GetChar();

            shipView->Hide();

            switch (key)
            {
            case Key::ArrawLeft:
                if (column > left)
                {
                    column -= cellSize * widthRate;
                    columnShip--;
                }
                break;
            case Key::ArrawRight:
                if (direction)
                {
                    if (column + cellSize * widthRate < right)
                    {
                        column += cellSize * widthRate;
                        columnShip++;
                    }
                }
                else
                {
                    if (column + size * cellSize * widthRate < right)
                    {
                        column += cellSize * widthRate;
                        columnShip++;
                    }
                }
                break;
            case Key::ArrawUp:
                if (row > top)
                {
                    row -= cellSize;
                    rowShip--;
                }
                break;

            case Key::ArrawDown:
                if (direction)
                {
                    if (row + size * cellSize < bottom)
                    {
                        row += cellSize;
                        rowShip++;
                    }
                }
                else
                {
                    if (row + cellSize < bottom)
                    {
                        row += cellSize;
                        rowShip++;
                    }
                }
                break;

            case Key::Space:
                if (direction)
                {
                    if (column + size * cellSize * widthRate > right)
                        break;
                }
                else
                {
                    if (row + size * cellSize > bottom)
                        break;
                }

                direction = !direction;

                {
                    int w = width;
                    width = height * 2;
                    height = w / 2;
                }

                shipView->Resize({ width, height });

                break;

            case Key::Enter:
                isSet = true;

                {
                    DirectionShip shipDirection = (direction) ?
                        DirectionShip::Vertical : DirectionShip::Horizontal;
                    ship = new Ship({ rowShip, columnShip }, size, shipDirection);
                }

                break;

            case Key::Esc:
                isSet = true;
                break;
            default:
                break;
            }

            if (isSet)
                break;

            shipView->Move({ row, column });
            shipView->Show();
        }
    }

    return ship;
}

PlayerConsolePlatform::PlayerConsolePlatform()
{
    int fieldWidth{ (fieldSize + margin) * cellSize * widthRate };

    for (int size{}; size < shipCounts.size(); size++)
    {
        View* shipView = new View(
            { rowStart + size * 2 * cellSize , columnStart + fieldWidth + 3 * margin * cellSize },
            { (size + 1) * cellSize * widthRate, cellSize },
            Colors::Green, Colors::White);

        shipViews[size] = shipView;
    }
}

std::vector<Ship*> PlayerConsolePlatform::SetFlotilla(std::string name)
{
    this->FieldShow(name);

    Ship* ship;
    int selectShip;

    while (true)
    {
        selectShip = this->SelectShip();
        ship = this->SetShip(selectShip + 1);

        if (ship)
        {
            this->flotilla.push_back(ship);
            this->shipCounts[selectShip]--;
        }

        this->ShipsShow();

        int countAll = std::accumulate(shipCounts.begin(), shipCounts.end(), 0);
        if (!countAll)
            break;
    }
    

    View::GetConsole()->GetChar();
    


    return std::vector<Ship*>();
}
