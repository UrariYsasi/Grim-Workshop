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
    m_engine(engine),
    m_shaderImporter(nullptr)
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

    m_shaderImporter = std::make_unique<OpenGLShaderAssetImporter>();

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

    std::vector<std::string> files = m_fileModule->FindAllFiles(ASSET_DIRECTORY_PATH);
    for (auto it = files.begin(); it != files.end(); it++)
    {
        std::string path = *(it);
        std::string ID = path;
        IAssetImporter* importer = nullptr;

        if (m_shaderImporter->CanImport(path))
        {
            importer = m_shaderImporter.get();
        }

        if (importer == nullptr)
        {
            continue;
        }

        std::unique_ptr<IAsset> asset = importer->Import(path);
        if (asset == nullptr)
        {
            LOG_ERROR() << "Asset " << ID << " failed to import!";
            continue;
        }

        AddAsset(ID, std::move(asset));
    }

    LOG() << "Loaded Assets.";
}

void GrimAssetModule::AddAsset(const std::string& ID, std::unique_ptr<IAsset> asset)
{
    if (asset == nullptr)
    {
        LOG_ERROR() << "Asset " << ID << " could not be added, as it was nullptr!";
        return;
    }

    m_assetMap[ID] = std::move(asset);
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