/*
    PCH.hpp
    Peon Game

    Declan Hopkins
    8/1/2016
*/

#pragma once

/*
    Standard Library
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
#include <map>

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

#ifdef _WIN32
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
    Game
*/

#include "Game.hpp"