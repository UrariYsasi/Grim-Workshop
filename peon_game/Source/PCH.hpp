#pragma once

/*
    Standard Library
*/

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

/*
    GL3W
*/

#include <GL/gl3w.h>

/*
    SOIL
*/

#include <SOIL.h>

/*
    GLM
*/

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/*
    SDL2
*/

#if WINDOWS
    #include <SDL.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_opengl.h>
#endif

/*
    Grim Workshop
*/

#include "GrimWorkshop.hpp"

/*
    Project Peon
*/
#include "Item/ItemType.hpp"
#include "Entity/EntityID.hpp"
#include "Entity/Action/ActionID.hpp"

/*
    glm::vec2 Hash
*/
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
