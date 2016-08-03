/*
    ModuleFactory.cpp
    Peon Engine

    Declan Hopkins
    8/2/2016
*/

#include "PCH.hpp"
#include "ModuleFactory.hpp"

namespace grim
{

std::unique_ptr<IWindowModule> ModuleFactory::CreateWindowModule(Engine* const engine)
{
    return std::make_unique<OpenGLWindow>(engine, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_IS_FULLSCREEN);
}

}