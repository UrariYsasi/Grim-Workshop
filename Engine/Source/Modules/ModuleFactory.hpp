/*
    ModuleFactory.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016

    Utility class used by the Engine for creating modules.
*/

#pragma once

namespace grim
{

class ModuleFactory
{
public:
    static std::unique_ptr<IWindowModule> CreateWindowModule(Engine* const engine);
    static std::unique_ptr<ITimeModule> CreateTimeModule();
};

}