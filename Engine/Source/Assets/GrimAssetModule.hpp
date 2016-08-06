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
    GrimAssetModule();
    ~GrimAssetModule();

    /*
        IModule Interface
    */

    virtual bool Initialize() override;
    virtual void Terminate() override;

    /*
        IAssetModule Interface
    */
    virtual void LoadAssets() override;
    virtual IAsset* FindAsset(const std::string& ID) override;

private:
    std::map<std::string, std::unique_ptr<IAsset>> m_assetMap;
};

}
