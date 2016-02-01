#include "PCH.hpp"
#include "Game/Game.hpp"

int main(int argc, char** argv)
{
    // Tyren Review: Fix the cast issue here:
    std::srand((unsigned int)std::time(0));
    // Why? Because std::time returns a 64 bit integer, but srand only takes a 32 bit integer
    // In this case it is not important since you KNOW it is just using it to seed the RNG.
    // However, in some cases, it can be REALLY bad and cause hard to find bugs).
    // So this is a "warning", but you should consider each case and decide the correct thing to do.

    Game game;
    if (game.Initialize() == SUCCESS)
    {
        game.Run();
    }

    return 0;
}
