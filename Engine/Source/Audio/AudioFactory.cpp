#include "PCH.hpp"
#include "AudioFactory.hpp"
#include "SDLAudio.hpp"

namespace grim
{

namespace audio
{

std::unique_ptr<IAudio> CreateAudioService()
{
    // For now, just create an SDLAudio service.
    // TODO make this take some flags and junk
    return std::make_unique<SDLAudio>();
}

}

}