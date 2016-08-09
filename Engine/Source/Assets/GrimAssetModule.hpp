/*
    GrimAssetModule.hpp
    Peon Engine

    Declan Hopkins
    8/6/2016
*/

#pragma once

namespace grim
{

class GrimAssetModule : public IAssetModule
{
public:
    GrimAssetModule(Engine* const engine);
    ~GrimAssetModule();

    std::string GetFileName(const std::string& path) const;

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IAssetModule Interface
    */
    virtual void ImportAssets() override;
    virtual void AddAsset(const std::string& ID, std::unique_ptr<IAsset> asset) override;
    virtual IAsset* FindAsset(const std::string& ID) override;

private:
    Engine* m_engine;
    IFileModule* m_fileModule;
    std::map<std::string, std::unique_ptr<IAsset>> m_assetMap;
    std::vector<std::unique_ptr<AssetImporter>> m_importers;
};

}
