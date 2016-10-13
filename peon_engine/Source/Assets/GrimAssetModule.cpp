/*
    GrimAssetModule.cpp
    Peon Engine

    Declan Hopkins
    10/11/2016
*/

#include "PCH.hpp"
#include "GrimAssetModule.hpp"
#include "Engine.hpp"

namespace grim::assets
{

GrimAssetModule::GrimAssetModule(grim::Engine* const engine) :
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

    m_importers.push_back(std::make_unique<TextureImporter>(this));
    //m_importers.push_back(std::make_unique<OpenGLShaderImporter>(this, m_fileModule));
    //m_importers.push_back(std::make_unique<OpenGLShaderProgramImporter>(this, m_fileModule));

    LOG() << "Asset Module GrimAssetModule initialized.";
    return true;
}

void GrimAssetModule::Terminate()
{
    LOG() << "Asset Module GrimAssetModule terminating...";

    //m_importers.clear();
    m_assetMap.clear();

    LOG() << "Asset Module GrimAssetModule terminated.";
}

void GrimAssetModule::ImportAssets()
{
    LOG() << "Loading Assets...";

    std::vector<std::string> files = m_engine->GetFileModule()->FindAllFiles(ASSET_DIRECTORY_PATH);
    for (auto filePath : files)
    {
        std::string ID = GetFileName(filePath);

        for (auto& importer : m_importers)
        {
            if (importer->CanImport(filePath))
            {
                std::unique_ptr<Asset> asset = importer->Import(filePath);
                if (asset == nullptr)
                {
                    LOG_ERROR() << "Asset " << ID << " failed to import!";
                    continue;
                }

                AddAsset(ID, std::move(asset));
                LOG() << "Imported asset " << ID;
                break;
            }
        }
    }

    LOG() << "Loaded Assets.";
}

void GrimAssetModule::AddAsset(const std::string& ID, std::unique_ptr<Asset> asset)
{
    if (asset == nullptr)
    {
        LOG_ERROR() << "Asset " << ID << " could not be added, as it was nullptr!";
        return;
    }

    // TODO:
    // Add check for an already existing Asset.

    m_assetMap[ID] = std::move(asset);
}

Asset* GrimAssetModule::FindAsset(const std::string& ID) const
{
    auto assetIterator = m_assetMap.find(ID);
    if (assetIterator != m_assetMap.end())
    {
        return assetIterator->second.get();
    }

    LOG_ERROR() << "Asset \'" << ID << "\' couldn't be found!";
    return nullptr;
}

Texture* GrimAssetModule::FindTexture(std::string const& id) const
{
    Texture* texture = dynamic_cast<Texture*>(FindAsset(id));
    if (texture == nullptr)
    {
        //LOG_ERROR() << "Asset " << id << " isn't a Texture!";
    }

    return texture;
}

std::string GrimAssetModule::GetFileName(const std::string& path) const
{
    std::string fileName = path;

    auto slash = path.find_last_of("\\/");
    if (slash != std::string::npos)
    {
        fileName = path.substr(slash + 1, path.size() - slash - 1);
    }

    auto period = fileName.find_last_of(".");
    if (period != std::string::npos)
    {
        fileName = fileName.substr(0, period);
    }

    return fileName;
}

Engine* GrimAssetModule::GetEngine() const
{
    return m_engine;
}

}