#pragma once

namespace grim
{

namespace audio
{

class IAudio
{
public:
    virtual uint8_t LoadSound(const std::string& path, const std::string& id) = 0;
    virtual uint8_t PlaySound(const std::string& id) = 0;
};

}

}