#pragma once

/*
    Standard Library
*/

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <list>
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