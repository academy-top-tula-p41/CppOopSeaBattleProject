#include <iostream>

#include "Game.h"
#include "ConsolePlatform.h"

int main()
{
    Game* game = new Game(new Platform(
        new GameConsolePlatform(),
        new PlayerConsolePlatform()));

    game->Setup();
}
