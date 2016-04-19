#pragma once
#include "IAudio.hpp"

namespace grim
{

namespace audio
{

class SDLAudio : public IAudio
{
public:
    SDLAudio();
    ~SDLAudio();

    virtual bool Initialize();
    virtual bool LoadSound(const std::string& path, const std::string& id);
    virtual bool PlaySound(const std::string& id);

public:
    std::map<std::string, Mix_Chunk*> m_soundDatabase;
};

}

}