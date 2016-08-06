/*
    IAssetModule.hpp
    Peon Engine

    Declan Hopkins
    8/6/2016

    An Engine Module responsible for loading game assets and storing them for later usage. This
    module depends on Asset Loaders to load assets properly.
*/

#pragma once

namespace grim
{

class IAssetModule : public IModule
{
public:
    /*
        Load all the game assets and store them for later use.

        This should be called before the game starts.
    */
    virtual void LoadAssets() = 0;

    /*
        Find the Asset with the given ID.

        Returns nullptr if the requested Asset could not be found.
    */
    virtual IAsset* FindAsset(const std::string& ID) = 0;
};

}