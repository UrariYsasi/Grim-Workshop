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
    GrimAssetModule(grim::Engine* const engine);
    ~GrimAssetModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IAssetModule Interface
    */
    virtual void ImportAssets() override;
    virtual void AddAsset(std::unique_ptr<Asset> asset) override;
    virtual Asset* FindAsset(const std::string& ID) const override;
    virtual Texture* FindTexture(std::string const& id) const override;
    virtual Engine* GetEngine() const override;

    /*
        GrimAssetModule
    */

    std::string GetFileName(const std::string& path) const;

private:
    grim::Engine* m_engine;
    std::map<std::string, std::unique_ptr<Asset>> m_assetMap;
    std::vector<std::unique_ptr<Importer>> m_importers;
};

}
