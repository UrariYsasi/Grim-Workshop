/*
    IAssetModule.hpp
    Peon Engine

    Declan Hopkins
    8/6/2016

    An Engine Module responsible for importing game assets and storing them for later usage. This
    module depends on Asset importers to load assets properly.
*/

#pragma once

namespace grim
{

class IAssetModule : public IModule
{
public:
    /*
        Import all the game assets and store them for later use.

        Assets will be imported from the default asset directory. This function should be called 
        before the game starts.
    */
    virtual void ImportAssets() = 0;

    /*
        Add an Asset to storage.

        If an Asset with the given ID is already stored, that Asset will be overriden.
    */
    virtual void AddAsset(const std::string& ID, std::unique_ptr<IAsset> asset) = 0;

    /*
        Find the Asset with the given ID.

        Returns nullptr if the requested Asset could not be found.
    */
    virtual IAsset* FindAsset(const std::string& ID) = 0;
};

}