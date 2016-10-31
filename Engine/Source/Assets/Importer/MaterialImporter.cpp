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
    //LOG() << metadata.ToString();

    return DeserializeMaterial(CreateId(filePath), metadata);
}

bool MaterialImporter::CanImport(std::string const& filePath)
{
    return (m_assetModule->GetEngine()->GetPlatformModule()->FindFileExtension(filePath) == "mat");
}

std::unique_ptr<Material> MaterialImporter::DeserializeMaterial(std::string const& id, utility::Metadata const& metaData) const
{
    std::string textureId = "Textures.Terrain";
    Texture* texture = dynamic_cast<Texture*>(m_assetModule->FindAsset(textureId));

    return std::make_unique<Material>(id, texture, Texture::WrapMode::ClampToEdge, Texture::FilterMode::Linear, Texture::TransparencyMode::Opaque, nullptr);
}

}