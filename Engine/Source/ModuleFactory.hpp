/*
    ModuleFactory.hpp
    Engine

    Declan Hopkins
    9/6/2016

    Utility class used by the Engine for creating modules.
*/

#pragma once

namespace grim
{

class ModuleFactory
{
public:
    static std::unique_ptr<utility::ITimeModule> CreateTimeModule();
    static std::unique_ptr<platform::IPlatformModule> CreatePlatformModule();
    static std::unique_ptr<assets::IAssetModule> CreateAssetModule(Engine* const engine);
    static std::unique_ptr<ui::IInputModule> CreateInputModule();
    static std::unique_ptr<graphics::IWindowModule> CreateWindowModule(Engine* const engine);
    //static std::unique_ptr<IRendererModule> CreateRendererModule();
};

}