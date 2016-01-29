#include "PCH.hpp"
#include "Game/Game.hpp"

int main(int argc, char** argv)
{
    std::srand(std::time(0));

    Game game;
    if (game.Initialize() == SUCCESS)
    {
        game.Run();
    }

    return 0;
}
