#include "PCH.hpp"
#include "Game/Game.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        if (std::string(argv[1]) == "-noAudio")
        {
            //Debug::DisableFlag(MIX_AUDIO);
            grim::utility::Debug::LogError("-noAudio flag observed.");
        }
    }
    else
    {
        grim::utility::Debug::EnableFlag(grim::utility::MIX_AUDIO);
    }

    Game game;
    if (game.Initialize() == SUCCESS)
    {
        game.Run();
    }
    else
    {
        grim::utility::Debug::LogError("Game initialization failed.");
    }

    return 0;
}
