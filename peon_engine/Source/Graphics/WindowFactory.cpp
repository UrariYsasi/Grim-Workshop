#include "PCH.hpp"
#include "WindowFactory.hpp"

namespace grim
{

namespace graphics
{

std::unique_ptr<IWindow> CreateWindowService(const uint16_t& width, const uint16_t& height, const std::string& title, bool isFullScreen, bool isOpenGL)
{
    return std::make_unique<SDLWindow>(width, height, title, isFullScreen, isOpenGL);
}

}

}