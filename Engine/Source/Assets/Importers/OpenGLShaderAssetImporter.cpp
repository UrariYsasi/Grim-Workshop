/*
    OpenGLShaderAssetImporter.cpp
    Peon Engine

    Declan Hopkins
    8/7/2016
*/

#include "PCH.hpp"
#include "OpenGLShaderAssetImporter.hpp"

namespace grim
{

OpenGLShaderAssetImporter::OpenGLShaderAssetImporter()
{
}

OpenGLShaderAssetImporter::~OpenGLShaderAssetImporter()
{
}

std::unique_ptr<IAsset> OpenGLShaderAssetImporter::Import(const std::string& path)
{
    LOG() << "Importing Shader " << path;

    return nullptr;
}

bool OpenGLShaderAssetImporter::CanImport(const std::string& path)
{
    // Get the file extension
    if (path.find_last_of(".") != std::string::npos)
    {
        std::string extension = path.substr(path.find_last_of(".") + 1);
        if (extension == "glsl")
        {
            return true;
        }
    }

    return false;
}

std::string GetFileExtension(const std::string& FileName)
{
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".") + 1);
    return "";
}

}