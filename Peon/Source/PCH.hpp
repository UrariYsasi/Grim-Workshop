#pragma once

// Standard Library Includes
#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>

// GL3W Includes
#include <GL/gl3w.h>

// SOIL Incluces
#include <SOIL.h>

// GLM Includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// SDL2 Includes
#if WINDOWS
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_opengl.h>
#endif

// Engine Includes
#include "Engine/Debug.hpp"
#include "Engine/Random.hpp"
#include "Engine/Color.hpp"
#include "Engine/Rect.hpp"
#include "Engine/Timer.hpp"
#include "Engine/Shader.hpp"
#include "Engine/ShaderProgram.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Sprite.hpp"

// Game Includes
#include "Game/Item/ItemType.hpp"
#include "Game/Entity/EntityID.hpp"
#include "Game/Entity/Action/ActionID.hpp"

// Constants
const int SUCCESS = 1;
const int FAILURE = 0;

// Typedefs
typedef unsigned char byte;

// glm::vec2 Hash
namespace std {

template <>
struct hash<glm::vec2>
{
    inline std::size_t operator()(const glm::vec2& vec) const
    {
        return ((hash<float>()(vec.x)
            ^ (hash<float>()(vec.y) << 1)) >> 1);
    }
};

}
