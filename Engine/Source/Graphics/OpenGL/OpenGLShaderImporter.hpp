/*
    OpenGLShaderImporter.hpp
    Peon Engine

    Declan Hopkins
    8/7/2016

    A Shader Asset Importer that imports OpenGL shaders.
*/

#pragma once

namespace grim
{

class OpenGLShaderImporter : public AssetImporter
{
public:
    OpenGLShaderImporter(IAssetModule* const assetModule, IFileModule* const fileModule);
    virtual ~OpenGLShaderImporter();

    /*
        AssetImporter Interface
    */

    virtual std::unique_ptr<IAsset> Import(const std::string& path) override;
    virtual bool CanImport(const std::string& path) override;
};

}