#include "PCH.hpp"
#include "SDLAudio.hpp"

namespace grim
{

namespace audio
{

SDLAudio::SDLAudio()
{
}

SDLAudio::~SDLAudio()
{
}

bool SDLAudio::Initialize()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != SUCCESS)
    {
        grim::utility::Debug::LogError("SDLAudio failed to initialize! SDL_mixer error: %s", Mix_GetError());
        return false;
    }

    grim::utility::Debug::LogError("Audio module SDLAudio initialized.");
    return true;
}

void SDLAudio::Terminate()
{
    for (auto it = m_soundDatabase.begin(); it != m_soundDatabase.end(); it++)
    {
        Mix_FreeChunk(it->second);
    }

    Mix_CloseAudio();
    Mix_Quit();

    grim::utility::Debug::LogError("Audio module SDLAudio terminated.");
}

bool SDLAudio::LoadSound(const std::string& path, const std::string& id)
{
    Mix_Chunk* mixChunk = Mix_LoadWAV(path.c_str());
    if (mixChunk == nullptr)
    {
        grim::utility::Debug::LogError("SDLAudio failed to load WAV from %s! SDL_mixer error: %s", path.c_str(), Mix_GetError());
        return false;
    }

    m_soundDatabase.emplace(std::make_pair(id, mixChunk));

    return true;
}

bool SDLAudio::PlaySound(const std::string& id)
{
    Mix_Chunk* mixChunk = (m_soundDatabase.find(id))->second;
    if (mixChunk == nullptr)
    {
        grim::utility::Debug::LogError("SDLAudio failed to play sound %s! The sound does not exist!", id.c_str());
        return false;
    }

    Mix_PlayChannel(-1, mixChunk, 0);

    return true;
}

}

}