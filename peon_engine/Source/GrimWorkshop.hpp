#pragma once

/*
    Engine Includes
*/

#include "Utility/Logger.hpp"
#include "IModule.hpp"
#include "Audio/IAudio.hpp"
#include "Audio/SDLAudio.hpp"
#include "Audio/AudioFactory.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Transform.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/IWindowModule.hpp"
#include "Graphics/OpenGL/OpenGLWindowModule.hpp"
#include "Graphics/IRenderer.hpp"
#include "Graphics/OpenGLRenderer.hpp"
#include "Graphics/RendererFactory.hpp"
#include "Utility/Debug.hpp"
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
