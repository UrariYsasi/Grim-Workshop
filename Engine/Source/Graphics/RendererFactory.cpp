#include "PCH.hpp"
#include "RendererFactory.hpp"
#include "OpenGLRenderer.hpp"

namespace grim
{

namespace graphics
{

std::unique_ptr<IRenderer> CreateRendererService()
{
    return std::make_unique<OpenGLRenderer>();
}

}

}