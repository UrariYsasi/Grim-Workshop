#pragma once

/*
    Engine Includes
*/

#include "Engine.hpp"
#include "Audio/IAudio.hpp"
#include "Audio/SDLAudio.hpp"
#include "Audio/AudioFactory.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Window.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/SpriteBatch.hpp"
#include "Graphics/Mesh.hpp"
#include "Utility/Debug.hpp"
#include "Utility/PoissonDiskGenerator.hpp"
#include "Utility/Random.hpp"
#include "Utility/Timer.hpp"
#include "UI/Input.hpp"
#include "UI/UserInterface.hpp"
#include "UI/Widgets/Widget.hpp"
#include "UI/Widgets/Text.hpp"

/*
    Constants
*/

const uint8_t SUCCESS = 0;
const uint8_t FAILURE = 1;

/*
    Typedefs
*/

typedef unsigned char byte;