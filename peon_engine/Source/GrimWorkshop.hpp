#pragma once

/*
    Engine Includes
*/

#include "Utility/Logger.hpp"
#include "IModule.hpp"
#include "Audio/IAudio.hpp"
#include "Audio/SDLAudio.hpp"
#include "Audio/AudioFactory.hpp"
#include "Video/Color.hpp"
#include "Video/Camera.hpp"
#include "Video/Shader.hpp"
#include "Video/ShaderProgram.hpp"
#include "Video/Rect.hpp"
#include "Video/Vertex.hpp"
#include "Video/Transform.hpp"
#include "Video/Texture.hpp"
#include "Video/PrimitiveType.hpp"
#include "Video/Mesh.hpp"
#include "Video/Material.hpp"
#include "Video/Sprite.hpp"
#include "Video/RenderCommand.hpp"
#include "Video/IWindowModule.hpp"
#include "Video/OpenGL/OpenGLWindowModule.hpp"
#include "Video/IRenderer.hpp"
#include "Video/OpenGLRenderer.hpp"
#include "Video/RendererFactory.hpp"
#include "Utility/PoissonDiskGenerator.hpp"
#include "Utility/Random.hpp"
#include "Utility/Timer.hpp"
#include "Utility/ITimeModule.hpp"
#include "Utility/GrimTimeModule.hpp"
#include "UI/InputConstants.hpp"
#include "UI/IInputModule.hpp"
#include "UI/GrimInputModule.hpp"
#include "Platform/IFileModule.hpp"
#include "Platform/Windows/WindowsFileModule.hpp"
#include "Assets/Asset.hpp"
#include "Assets/IAssetModule.hpp"
#include "Assets/Importer.hpp"
#include "Assets/GrimAssetModule.hpp"
#include "ModuleFactory.hpp"
#include "IGame.hpp"
#include "Engine.hpp"

/*
    Constants
*/

const std::string WINDOW_TITLE = "Project Peon";
const uint32_t WINDOW_WIDTH = 1280;
const uint32_t WINDOW_HEIGHT = 800;
const bool WINDOW_IS_FULLSCREEN = false;
const std::string ASSET_DIRECTORY_PATH = "Assets/";
const std::string LOG_FILE_NAME = "game.log";