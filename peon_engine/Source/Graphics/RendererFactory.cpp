#include "PCH.hpp"
#include "RendererFactory.hpp"
#include "SDLRenderer.hpp"

namespace grim
{

namespace graphics
{

std::unique_ptr<IRenderer> CreateRendererService()
{
    return std::make_unique<SDLRenderer>();
}

}

}