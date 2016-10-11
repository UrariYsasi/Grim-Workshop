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
#include "ModuleFactory.hpp"
#include "IGame.hpp"
#include "Engine.hpp"

/*
    Constants
*/

const uint8_t SUCCESS = 0;
const uint8_t FAILURE = 1;
const uint16_t WINDOW_WIDTH = 1600;
const uint16_t WINDOW_HEIGHT = 900;
const bool IS_WINDOW_FULLSCREEN = false;
const bool IS_WINDOW_OPENGL = true;
const std::string WINDOW_TITLE = "Grim Workshop";
const grim::graphics::Color RED(1.0f, 0.0f, 0.0f, 1.0f);
#define LOG_FILE_NAME "game.log"

/*
    Typedefs
*/

typedef unsigned char byte;
