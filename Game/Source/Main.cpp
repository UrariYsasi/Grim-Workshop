#include "PCH.hpp"

int main(int argc, char** argv)
{
    Game game;
    if (!game.Initialize())
    {
        std::cout << "Game initialization failed!" << std::endl;

        return 0;
    }
    else
    {
        game.Run();
    }

    return 0;
}