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

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IAssetModule Interface
    */
    virtual void ImportAssets() override;
    virtual IAsset* FindAsset(const std::string& ID) override;

private:
    Engine* m_engine;
    IFileModule* m_fileModule;
    std::map<std::string, std::unique_ptr<IAsset>> m_assetMap;
};

}
