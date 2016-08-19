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
#include "Graphics/IShader.hpp"
#include "Graphics/IShaderProgram.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "Graphics/OpenGL/OpenGLShaderProgram.hpp"
#include "Assets/AssetImporter.hpp"
#include "Graphics/OpenGL/OpenGLShaderImporter.hpp"
#include "Graphics/OpenGL/OpenGLShaderProgramImporter.hpp"
#include "IModule.hpp"
#include "Platform/IFileModule.hpp"
#include "Graphics/IWindowModule.hpp"
#include "Utilities/ITimeModule.hpp"
#include "Graphics/IRendererModule.hpp"
#include "Assets/IAssetModule.hpp"
#include "Utilities/GrimTimeModule.hpp"
#include "Platform/Windows/WindowsFileModule.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/OpenGL/OpenGLWindowModule.hpp"
#include "Graphics/OpenGL/OpenGLRendererModule.hpp"
#include "Assets/GrimAssetModule.hpp"
#include "ModuleFactory.hpp"
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