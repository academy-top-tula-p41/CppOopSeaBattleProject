#include "ConsolePlatform.h"

void GameConsolePlatform::SetGame(Game* game)
{
    this->game = game;
}

void GameConsolePlatform::ViewFlottilla()
{
    Player* humanPlayer{ this->game->Players()[0] };

    int top{ rowStart + margin + 1 };
    int left{ columnStart + margin * cellSize };
    
    for (Ship* ship : humanPlayer->Flotilla())
    {
        int shipRow{ top + ship->Row() * cellSize };
        int shipColumn{ left + ship->Column() * cellSize * widthRate };
        int shipWidth{ ship->Size() * cellSize * widthRate };
        int shipHeight{ cellSize };

        if (ship->Direction() == DirectionShip::Vertical)
        {
            int w = shipWidth;
            shipWidth = shipHeight * 2;
            shipHeight = w / 2;
        }

        View* shipView = new View({ shipRow, shipColumn },
            { shipWidth, shipHeight },
            Colors::Green, Colors::White);
        shipView->Show();
    }
}

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

void GameConsolePlatform::ViewGame()
{
    int fieldWidth{ (fieldSize + margin) * cellSize * widthRate };
    int fieldHeight{ (fieldSize + margin) * cellSize };

    // Human FieldView
    View* humanFieldView = new View({ rowStart, columnStart },
        { fieldWidth, fieldHeight },
        Colors::Blue, Colors::White);
    humanFieldView->Show();

    std::string name{ game->Players()[0]->Name() };
    humanFieldView->GetConsole()->WritePosition(
        Position{ rowStart, columnStart + (fieldWidth - (int)name.length()) / 2 },
        name);

    int row{ rowStart + cellSize };
    for (int i{}; i < fieldSize; i++)
    {
        humanFieldView->GetConsole()->WriteWidthPosition(
            { row, columnStart + (i + 1) * cellSize * widthRate + margin },
            cellSize,
            std::string(1, (char)('A' + i)));
    }

    int column{ columnStart + cellSize };
    for (int i{}; i < fieldSize; i++)
    {
        humanFieldView->GetConsole()->WriteWidthPosition(
            { rowStart + (i + 1) * cellSize + margin, column },
            cellSize,
            std::to_string(i + 1));
    }

    for (int line{}; line < fieldSize * cellSize; line++)
        humanFieldView->GetConsole()->WritePosition(
            { rowStart + margin + line + 1, columnStart + margin * cellSize },
            std::string(fieldSize * cellSize * widthRate, (char)GameChar::Water));


    // Computer FieldView

    int compRowStart{ rowStart };
    int compColumnStart{ columnStart + fieldWidth + margin * cellSize * widthRate };

    View* compFieldView = new View({ compRowStart, compColumnStart },
        { fieldWidth, fieldHeight },
        Colors::Blue, Colors::White);
    compFieldView->Show();

    name = game->Players()[1]->Name();
    compFieldView->GetConsole()->WritePosition(
        Position{ compRowStart, compColumnStart + (fieldWidth - (int)name.length()) / 2 },
        name);

    row = compRowStart + cellSize;
    for (int i{}; i < fieldSize; i++)
    {
        compFieldView->GetConsole()->WriteWidthPosition(
            { row, compColumnStart + (i + 1) * cellSize * widthRate + margin },
            cellSize,
            std::string(1, (char)('A' + i)));
    }

    column = compColumnStart + cellSize;
    for (int i{}; i < fieldSize; i++)
    {
        compFieldView->GetConsole()->WriteWidthPosition(
            { compRowStart + (i + 1) * cellSize + margin, column },
            cellSize,
            std::to_string(i + 1));
    }

    for (int line{}; line < fieldSize * cellSize; line++)
        compFieldView->GetConsole()->WritePosition(
            { compRowStart + margin + line + 1, compColumnStart + margin * cellSize },
            std::string(fieldSize * cellSize * widthRate, (char)GameChar::Water));


    this->ViewFlottilla();
}

void GameConsolePlatform::ViewShot(Point point, bool currentPlayer)
{
    Field* field = this->game->Players()[!currentPlayer]->BattleField();

    int fieldWidth{ (fieldSize + margin) * cellSize * widthRate };
    int fieldHeight{ (fieldSize + margin) * cellSize };

    int row{ rowStart + margin + 1 };
    int column{};

    if (currentPlayer)
        column = columnStart + margin * cellSize;
    else
        column = columnStart + fieldWidth + margin * cellSize * widthRate;

    char shotChar = (char)((field->GetCell(point)->Type() == CellType::Water) ?
                    GameChar::Water : GameChar::Deck);
    View::GetConsole()->Foreground(Colors::Red);
    View::GetConsole()->Background(Colors::White);
    for (int l{}; l < cellSize; l++)
        View::GetConsole()->WritePosition({ row + l, column },
            std::string(cellSize * widthRate, shotChar));
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
                {
                    DirectionShip shipDirection = (direction) ?
                        DirectionShip::Vertical : DirectionShip::Horizontal;
                    ship = new Ship({ rowShip, columnShip }, size, shipDirection);
                    
                    isSet = this->IsSetShip(ship);

                    if (!isSet)
                    {
                        delete ship;
                        ship = nullptr;
                    }
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

bool PlayerConsolePlatform::IsSetShip(Ship* ship)
{
    bool isNotSet{ false };
    for (Ship* s : flotilla)
    {
        int row{ ship->Row() };
        int column{ ship->Column() };
        for (int d{}; d < ship->Size(); d++)
        {
            for (int rowDx{ -1 }; rowDx < 2; rowDx++)
            {
                for (int columnDx{ -1 }; columnDx < 2; columnDx++)
                {
                    isNotSet = s->IsPoint({ row + rowDx, column + columnDx });
                    if (isNotSet) break;
                }
                if (isNotSet) break;
            }
            if (isNotSet) break;

            (ship->Direction() == DirectionShip::Horizontal) ? column++ : row++;
        }
        if (isNotSet) break;
    }
    return !isNotSet;
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

    //View::GetConsole()->GetChar();

    return this->flotilla;
}

Point PlayerConsolePlatform::Shot()
{
    int fieldWidth{ (fieldSize + margin) * cellSize * widthRate };
    int fieldHeight{ (fieldSize + margin) * cellSize };
    
    int compRowStart{ rowStart };
    int compColumnStart{ columnStart + fieldWidth + margin * cellSize * widthRate };

    int top{ compRowStart + margin + 1 };
    int left{ compColumnStart + margin * cellSize };
    int bottom{ top + fieldSize * cellSize };
    int right{ left + fieldSize * cellSize * widthRate };

    View* cursorView = new View({ top, left },
        { cellSize * widthRate, cellSize },
        Colors::Cyan, Colors::Cyan);
    cursorView->Show();

    Key key;
    bool isShot;

    int row{};
    int column{};

    while (true)
    {
        if (View::GetConsole()->KeyPressed())
        {
            key = (Key)View::GetConsole()->GetChar();
            isShot = false;
            switch (key)
            {
            case Key::ArrawLeft:
                if (column > 0)
                    column--;
                else
                    column = fieldSize - 1;
                break;
            case Key::ArrawRight:
                if (column < fieldSize - 1)
                    column++;
                else
                    column = 0;
                break;
            case Key::ArrawUp:
                if (row > 0)
                    row--;
                else
                    row = fieldSize - 1;
                break;
            case Key::ArrawDown:
                if (row < fieldSize - 1)
                    row++;
                else
                    row = 0;
                break;
            case Key::Enter:
            case Key::Space:
                isShot = true;
                break;
            case Key::Esc:
                break;
            default:
                break;
            }
            if (isShot)
                break;

            cursorView->Move({ top + row * cellSize,
                               left + column * cellSize * widthRate });
        }
    }

    cursorView->Hide();
    delete cursorView;

    return Point{ row, column };
}
