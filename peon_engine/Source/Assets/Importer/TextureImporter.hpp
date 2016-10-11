/*
    TextureImporter.hpp
    Engine

    Declan Hopkins
    10/11/2016

    An asset importer responsible for importing textures. The specific type of texture that is created
    is dependent on the type of texture that the renderer supports.
*/

#pragma once

namespace grim::assets
{

class TextureImporter : public Importer
{
public:
    TextureImporter(IAssetModule* const assetModule);
    virtual ~TextureImporter();

    /*
        Importer interface
    */

    virtual std::unique_ptr<Asset> Import(std::string const& filePath) override;
    virtual bool CanImport(std::string const& filePath) override;
};

}