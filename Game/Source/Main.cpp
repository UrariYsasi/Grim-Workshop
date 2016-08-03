/*
    Main.cpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#include "PCH.hpp"

int main(int argc, char** argv)
{
    Game game;
    if (!game.Initialize())
    {
        std::cout << "Game initialization failed!" << std::endl;
    }
    else
    {
        game.Run();
    }

    return 0;
}