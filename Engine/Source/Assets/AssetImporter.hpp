/*
    AssetImporter.hpp
    Peon Engine

    Declan Hopkins
    8/7/2016

    The base Asset Importer interface. Provides a common interface for importing game assets from
    the disk.
*/

#pragma once

namespace grim
{

class IAssetModule;
class IFileModule;

class AssetImporter
{
public:
    AssetImporter(IAssetModule* const assetModule, IFileModule* const fileModule);
    virtual ~AssetImporter();

    /*
        Import an Asset.

        Importing will read the file at the given path and create the corresponding Asset object. A
        smart pointer to the Asset will be returned, which can then be stored (preferably in the
        Asset Module).
    */
    virtual std::unique_ptr<IAsset> Import(const std::string& path) = 0;

    /*
        Check if this importer knows how to import a certain Asset.
    */
    virtual bool CanImport(const std::string& path) = 0;

protected:
    IAssetModule* m_assetModule;
    IFileModule* m_fileModule;
};

}