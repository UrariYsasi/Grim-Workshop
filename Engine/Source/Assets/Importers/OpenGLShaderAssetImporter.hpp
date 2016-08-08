/*
    OpenGLShaderAssetImporter.hpp
    Peon Engine

    Declan Hopkins
    8/7/2016

    A Shader Asset Importer that imports OpenGL shaders.
*/

#pragma once

namespace grim
{

class OpenGLShaderAssetImporter : public IShaderAssetImporter
{
public:
    OpenGLShaderAssetImporter();
    ~OpenGLShaderAssetImporter();

    /*
        IShaderAssetImporter Interface
    */

    virtual std::unique_ptr<IAsset> Import(const std::string& path) override;
    virtual bool CanImport(const std::string& path) override;
};

}