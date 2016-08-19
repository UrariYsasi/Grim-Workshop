/*
    OpenGLShaderProgramImporter.cpp
    Peon Engine

    Declan Hopkins
    8/8/2016
*/

#include "PCH.hpp"
#include "OpenGLShaderProgramImporter.hpp"

namespace grim
{

OpenGLShaderProgramImporter::OpenGLShaderProgramImporter(IAssetModule* const assetModule, IFileModule* const fileModule) :
    AssetImporter(assetModule, fileModule)
{
}

OpenGLShaderProgramImporter::~OpenGLShaderProgramImporter()
{
}

std::unique_ptr<IAsset> OpenGLShaderProgramImporter::Import(const std::string& path)
{
    LOG() << "Importing ShaderProgram " << path;

    std::ifstream input(path);
    if (!input.is_open())
    {
        LOG_ERROR() << "Failed to open file " << path;
        return nullptr;
    }

    std::string vertexShaderAssetID;
    std::string fragmentShaderAssetID;

    std::string propertyName;
    std::string propertyValue;
    while (input >> propertyName >> propertyValue)
    {
        if (propertyName == "VERTEX")
        {
            vertexShaderAssetID = propertyValue;
        }
        else if (propertyName == "FRAGMENT")
        {
            fragmentShaderAssetID = propertyValue;
        }
    }

    LOG() << "vertex: " << vertexShaderAssetID << ", fragment: " << fragmentShaderAssetID;

    return nullptr;
}

bool OpenGLShaderProgramImporter::CanImport(const std::string& path)
{
    // Get the file extension
    if (path.find_last_of(".") != std::string::npos)
    {
        std::string extension = path.substr(path.find_last_of(".") + 1);
        if (extension == "shader")
        {
            return true;
        }
    }

    return false;
}

}