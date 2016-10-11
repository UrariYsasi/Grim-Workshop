/*
    Importer.hpp
    Peon Engine

    Declan Hopkins
    10/11/2016

    The base Importer class, which provides some common functionalities for importing game assets
    from the computer.
*/

#pragma once

namespace grim::assets
{

class Importer
{
public:
    Importer(IAssetModule* const assetModule);
    virtual ~Importer();

    /*
        Import an Asset.

        Importing will read the file at the given path and create the corresponding Asset object. A
        smart pointer to the Asset will be returned, which can then be stored (preferably in the
        Asset Module).
    */
    virtual std::unique_ptr<Asset> Import(std::string const& filePath) = 0;
    virtual bool CanImport(std::string const& filePath) = 0;

protected:
    IAssetModule* m_assetModule;
};

}