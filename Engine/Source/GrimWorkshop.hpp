/*
    GrimWorkshop.hpp
    Peon Engine

    Declan Hopkins
    8/2/2016
*/

#pragma once

/*
    Engine Includes
*/

#include "IGame.hpp"
#include "Utilities/Log.hpp"
#include "Modules/IModule.hpp"
#include "Modules/IWindowModule.hpp"
#include "Modules/ITimeModule.hpp"
#include "Utilities/GrimTimeModule.hpp"
#include "Graphics/OpenGLWindowModule.hpp"
#include "Modules/ModuleFactory.hpp"
#include "Engine.hpp"

/*
    Constants
*/

#define WINDOW_TITLE "Project Peon"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800
#define WINDOW_IS_FULLSCREEN false
#define LOG_FILE_NAME "game.log"