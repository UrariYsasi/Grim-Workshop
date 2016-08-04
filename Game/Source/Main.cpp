/*
    Main.cpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#include "PCH.hpp"

int main(int argc, char** argv)
{
    // Clear the log file
    grim::Log::Clear();

    Game game;
    if (!game.Initialize())
    {
        LOG_ERROR() << "Game initialization failed!";
    }

    game.Run();
    game.Terminate();

    return 0;
}