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
#include <cstdint>
#include <functional>

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
#include "GrimWorkshop.hpp"

// Game Includes
#include "Item/ItemType.hpp"
#include "Entity/EntityID.hpp"
#include "Entity/Action/ActionID.hpp"

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
