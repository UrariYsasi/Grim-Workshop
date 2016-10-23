/*
    MaterialImporter.cpp
    Engine

    Declan Hopkins
    10/22/2016
*/

#include "PCH.hpp"
#include "MaterialImporter.hpp"


namespace grim::assets
{

MaterialImporter::MaterialImporter(IAssetModule* const assetModule) :
    Importer(assetModule)
{
}

MaterialImporter::~MaterialImporter()
{
}

std::unique_ptr<Asset> MaterialImporter::Import(std::string const& filePath)
{
    utility::Metadata metadata = ParseMetadata(filePath);
    LOG() << metadata.ToString();
    //std::unique_ptr<Material> material;

    //return std::move(material);
    return nullptr;
}

bool MaterialImporter::CanImport(std::string const& filePath)
{
    return (m_assetModule->GetEngine()->GetPlatformModule()->FindFileExtension(filePath) == "mat");
}

}