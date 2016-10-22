/*
    MaterialImporter.hpp
    Engine

    Declan Hopkins
    10/22/2016

    An asset importer responsible for importing materials.
*/

#pragma once

namespace grim::assets
{

class MaterialImporter : public Importer
{
public:
    MaterialImporter(IAssetModule* const assetModule);
    virtual ~MaterialImporter();

    /*
        Importer interface
    */

    virtual std::unique_ptr<Asset> Import(std::string const& filePath) override;
    virtual bool CanImport(std::string const& filePath) override;
};

}