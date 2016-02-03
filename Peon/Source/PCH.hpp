#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <algorithm>

#if WINDOWS
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
    #include <SDL2_mixer/SDL_mixer.h>
#endif

#include "Engine/Debug.hpp"
#include "Engine/Random.hpp"
#include "Engine/Vector2D.hpp"
#include "Engine/Rectangle.hpp"
#include "Engine/Timer.hpp"

#include "Game/Item/ItemType.hpp"

const int SUCCESS = 1;
const int FAILURE = 0;