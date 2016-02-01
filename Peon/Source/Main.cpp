#include "PCH.hpp"
#include "Game/Game.hpp"

int main(int argc, char** argv)
{
    Game game;
    if (game.Initialize() == SUCCESS)
    {
        game.Run();
    }
    else
    {
        Debug::LogError("Game initialization failed.");
    }

    return 0;
}
