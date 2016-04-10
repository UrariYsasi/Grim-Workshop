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
    for (auto it = m_soundDatabase.begin(); it != m_soundDatabase.end(); it++)
    {
        Mix_FreeChunk(it->second);
    }
}

uint8_t SDLAudio::LoadSound(const std::string& path, const std::string& id)
{
    Mix_Chunk* mixChunk = Mix_LoadWAV(path.c_str());
    if (mixChunk == nullptr)
    {
        grim::utility::Debug::LogError("SDLAudio failed to load WAV from %s! SDL_mixer error: %s", path.c_str(), Mix_GetError());
        return FAILURE;
    }

    m_soundDatabase.emplace(std::make_pair(id, mixChunk));

    return SUCCESS;
}

uint8_t SDLAudio::PlaySound(const std::string& id)
{
    Mix_Chunk* mixChunk = (m_soundDatabase.find(id))->second;
    if (mixChunk == nullptr)
    {
        grim::utility::Debug::LogError("SDLAudio failed to play sound %s! The sound does not exist!", id.c_str());
        return FAILURE;
    }

    Mix_PlayChannel(-1, mixChunk, 0);

    return SUCCESS;
}

}

}