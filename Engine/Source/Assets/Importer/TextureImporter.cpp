/*
    TextureImporter.cpp
    Engine

    Declan Hopkins
    10/11/2016
*/

#include "PCH.hpp"
#include "TextureImporter.hpp"

namespace grim::assets
{

TextureImporter::TextureImporter(IAssetModule* const assetModule) :
    Importer(assetModule)
{
}

TextureImporter::~TextureImporter()
{
}

std::unique_ptr<Asset> TextureImporter::Import(std::string const& filePath)
{
    int width = 0;
    int height = 0;
    unsigned char* data = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    if (data == nullptr)
    {
        LOG_ERROR() << "Failed to import asset file " << filePath;
        return false;
    }
    
    graphics::IRenderer* renderModule = m_assetModule->GetEngine()->GetRenderer();
    std::unique_ptr<Texture> texture = renderModule->CreateTexture(CreateId(filePath), width, height, data);
    if (texture == nullptr)
    {
        LOG_ERROR() << "Failed to create texture asset from file " << filePath;
    }

    SOIL_free_image_data(data);

    return std::move(texture);
}

bool TextureImporter::CanImport(std::string const& filePath)
{
    return (m_assetModule->GetEngine()->GetPlatformModule()->FindFileExtension(filePath) == "png");
}

}