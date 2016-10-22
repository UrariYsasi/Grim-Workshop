#pragma once

/*
    Engine Includes
*/

#include "Utility/Logger.hpp"
#include "IModule.hpp"
#include "Audio/IAudio.hpp"
#include "Audio/SDLAudio.hpp"
#include "Audio/AudioFactory.hpp"
#include "Platform/IFileModule.hpp"
#include "Platform/Windows/WindowsFileModule.hpp"
#include "Assets/Asset.hpp"
#include "Assets/IAssetModule.hpp"
#include "Assets/Importer/Importer.hpp"
#include "Assets/Importer/TextureImporter.hpp"
#include "Assets/Texture.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Assets/GrimAssetModule.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Transform.hpp"
#include "Graphics/PrimitiveType.hpp"
#include "Graphics/Mesh.hpp"
#include "Assets/Material.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/IWindowModule.hpp"
#include "Graphics/OpenGL/OpenGLWindowModule.hpp"
#include "Graphics/IRenderer.hpp"
#include "Graphics/OpenGLRenderer.hpp"
#include "Graphics/RendererFactory.hpp"
#include "Utility/PoissonDiskGenerator.hpp"
#include "Utility/Random.hpp"
#include "Utility/Timer.hpp"
#include "Utility/ITimeModule.hpp"
#include "Utility/GrimTimeModule.hpp"
#include "UI/InputConstants.hpp"
#include "UI/IInputModule.hpp"
#include "UI/GrimInputModule.hpp"
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