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

    // Initialize and run the game
    Game game;
    if (!game.Initialize())
    {
        LOG_ERROR() << "Game initialization failed!";
    }
    else
    {
        game.Run();
    }

    return 0;
}