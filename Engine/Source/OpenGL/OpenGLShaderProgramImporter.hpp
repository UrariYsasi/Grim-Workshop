/*
    OpenGLShaderProgramImporter.hpp
    Peon Engine

    Declan Hopkins
    8/8/2016

    A ShaderProgram Asset Importer that imports OpenGL shader programs.
*/

#pragma once

namespace grim
{

class OpenGLShaderProgramImporter : public AssetImporter
{
public:
    OpenGLShaderProgramImporter(IAssetModule* const assetModule, IFileModule* const fileModule);
    virtual ~OpenGLShaderProgramImporter();

    /*
        AssetImporter Interface
    */

    virtual std::unique_ptr<IAsset> Import(const std::string& path) override;
    virtual bool CanImport(const std::string& path) override;
};

}