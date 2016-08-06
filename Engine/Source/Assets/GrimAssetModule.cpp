/*
    GrimAssetModule.cpp
    Peon Engine

    Declan Hopkins
    8/6/2016
*/

#include "PCH.hpp"
#include "GrimAssetModule.hpp"

namespace grim
{

GrimAssetModule::GrimAssetModule()
{
}

GrimAssetModule::~GrimAssetModule()
{
}

bool GrimAssetModule::Initialize()
{
    LOG() << "Asset Module GrimAssetModule initializing...";

    LoadAssets();

    LOG() << "Asset Module GrimAssetModule initialized.";
    return true;
}

void GrimAssetModule::Terminate()
{
    LOG() << "Asset Module GrimAssetModule terminating...";

    m_assetMap.clear();

    LOG() << "Asset Module GrimAssetModule terminated.";
}

void GrimAssetModule::LoadAssets()
{
    LOG() << "Loading Assets...";

    LOG() << "Loaded Assets.";
}

IAsset* GrimAssetModule::FindAsset(const std::string& ID)
{
    auto assetIterator = m_assetMap.find(ID);
    if (assetIterator != m_assetMap.end())
    {
        return assetIterator->second.get();
    }
    
    LOG_ERROR() << "Asset \'" << ID << "\' couldn't be found!";
    return nullptr;
}


}