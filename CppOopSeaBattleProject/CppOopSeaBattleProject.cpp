#include <iostream>

#include "Game.h"
#include "ConsolePlatform.h"

int main()
{
    GameConsolePlatform* gamePlatform = new GameConsolePlatform();
    Game* game = new Game(new Platform(
        gamePlatform,
        new PlayerConsolePlatform()));
    gamePlatform->SetGame(game);

    game->Setup();
    game->Process();
}
