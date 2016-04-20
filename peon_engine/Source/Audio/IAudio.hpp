#pragma once

namespace grim
{

namespace audio
{

class IAudio
{
public:
    virtual bool Initialize() = 0;
    virtual void Terminate() = 0;
    virtual bool LoadSound(const std::string& path, const std::string& id) = 0;
    virtual bool PlaySound(const std::string& id) = 0;
};

}

}