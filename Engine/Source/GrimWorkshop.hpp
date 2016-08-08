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
#include "Assets/IAsset.hpp"
#include "Assets/IShaderAsset.hpp"
#include "Assets/Importers/IAssetImporter.hpp"
#include "Assets/Importers/IShaderAssetImporter.hpp"
#include "Assets/Importers/OpenGLShaderAssetImporter.hpp"
#include "Modules/IModule.hpp"
#include "Modules/IFileModule.hpp"
#include "Modules/IWindowModule.hpp"
#include "Modules/ITimeModule.hpp"
#include "Modules/IRendererModule.hpp"
#include "Modules/IAssetModule.hpp"
#include "Utilities/GrimTimeModule.hpp"
#include "Utilities/WindowsFileModule.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/OpenGLWindowModule.hpp"
#include "Graphics/OpenGLRendererModule.hpp"
#include "Assets/GrimAssetModule.hpp"
#include "Modules/ModuleFactory.hpp"
#include "Engine.hpp"

/*
    Constants
*/

#define WINDOW_TITLE "Project Peon"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800
#define WINDOW_IS_FULLSCREEN false
#define ASSET_DIRECTORY_PATH "Assets/"
#define LOG_FILE_NAME "game.log"