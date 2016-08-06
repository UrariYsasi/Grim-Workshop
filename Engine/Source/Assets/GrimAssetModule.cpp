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

GrimAssetModule::GrimAssetModule(Engine* const engine) :
    m_engine(engine)
{
}

GrimAssetModule::~GrimAssetModule()
{
}

bool GrimAssetModule::Initialize()
{
    LOG() << "Asset Module GrimAssetModule initializing...";

    if (m_engine == nullptr)
    {
        LOG_ERROR() << "No engine was provided for Asset Module!";
        return false;
    }

    m_fileModule = m_engine->GetFileModule();
    if (m_fileModule == nullptr)
    {
        LOG_ERROR() << "The File Module could not be retrieved!";
        return false;
    }

    ImportAssets();

    LOG() << "Asset Module GrimAssetModule initialized.";
    return true;
}

void GrimAssetModule::Terminate()
{
    LOG() << "Asset Module GrimAssetModule terminating...";

    m_assetMap.clear();

    LOG() << "Asset Module GrimAssetModule terminated.";
}

void GrimAssetModule::ImportAssets()
{
    LOG() << "Loading Assets...";

    std::vector<std::string> files = m_fileModule->FindAllFiles(ASSETS_DIRECTORY_PATH);
    for (auto it = files.begin(); it != files.end(); it++)
    {
        LOG() << "Importing " << *(it);
    }

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