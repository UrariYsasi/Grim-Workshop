/*
    GrimAssetModule.hpp
    Peon Engine

    Declan Hopkins
    10/11/2016

    The default Asset Module.
*/

#pragma once

namespace grim::assets
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
    virtual void AddAsset(const std::string& ID, std::unique_ptr<Asset> asset) override;
    virtual Asset* FindAsset(const std::string& ID) override;

private:
    Engine* m_engine;
    std::map<std::string, std::unique_ptr<Asset>> m_assetMap;
    std::vector<std::unique_ptr<Importer>> m_importers;
};

}
