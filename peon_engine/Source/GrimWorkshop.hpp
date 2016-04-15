#pragma once

/*
    Engine Includes
*/

#include "Audio/IAudio.hpp"
#include "Audio/SDLAudio.hpp"
#include "Audio/AudioFactory.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/IWindow.hpp"
#include "Graphics/SDLWindow.hpp"
#include "Graphics/WindowFactory.hpp"
#include "Graphics/IRenderer.hpp"
#include "Graphics/OpenGLRenderer.hpp"
#include "Graphics/RendererFactory.hpp"
#include "Utility/Debug.hpp"
#include "Utility/PoissonDiskGenerator.hpp"
#include "Utility/Random.hpp"
#include "Utility/Timer.hpp"
#include "UI/IInput.hpp"
#include "UI/SDLInput.hpp"
#include "UI/InputFactory.hpp"
#include "UI/Widgets/Widget.hpp"
#include "UI/Widgets/TextView.hpp"
#include "UI/Widgets/SpriteView.hpp"
#include "UI/Widgets/ButtonView.hpp"
#include "UI/IUserInterface.hpp"
#include "UI/GrimUI.hpp"
#include "UI/UIFactory.hpp"
#include "Engine.hpp"

/*
    Constants
*/

const uint8_t SUCCESS = 0;
const uint8_t FAILURE = 1;
const uint16_t WINDOW_WIDTH = 1600;
const uint16_t WINDOW_HEIGHT = 900;
const bool IS_WINDOW_FULLSCREEN = false;
const std::string WINDOW_TITLE = "Grim Workshop";

/*
    Typedefs
*/

typedef unsigned char byte;
