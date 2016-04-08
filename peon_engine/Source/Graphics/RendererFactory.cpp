#include "PCH.hpp"
#include "RendererFactory.hpp"
#include "SDLRenderer.hpp"

namespace grim
{

namespace graphics
{

std::unique_ptr<IRenderer> CreateRendererService()
{
    // For now, just create an SDLAudio service.
    // TODO make this take some flags and junk
    return std::make_unique<SDLRenderer>();
}

}

}