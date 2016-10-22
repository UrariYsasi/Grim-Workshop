/*
    ModuleFactory.cpp
    Engine

    Declan Hopkins
    8/2/2016
*/

#include "PCH.hpp"
#include "ModuleFactory.hpp"

namespace grim
{

std::unique_ptr<utility::ITimeModule> ModuleFactory::CreateTimeModule()
{
    return std::make_unique<utility::GrimTimeModule>();
}

std::unique_ptr<platform::IPlatformModule> ModuleFactory::CreatePlatformModule()
{
    return std::make_unique<platform::WindowsPlatformModule>();
}

std::unique_ptr<assets::IAssetModule> ModuleFactory::CreateAssetModule(Engine* const engine)
{
    return std::make_unique<assets::GrimAssetModule>(engine);
}

std::unique_ptr<ui::IInputModule> ModuleFactory::CreateInputModule()
{
    return std::make_unique<ui::GrimInputModule>();
}

std::unique_ptr<graphics::IWindowModule> ModuleFactory::CreateWindowModule(Engine* const engine)
{
    return std::make_unique<graphics::OpenGLWindowModule>(engine, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_IS_FULLSCREEN);
}

/*
std::unique_ptr<IRendererModule> ModuleFactory::CreateRendererModule()
{
    return std::make_unique<OpenGLRendererModule>();
}
*/

}
