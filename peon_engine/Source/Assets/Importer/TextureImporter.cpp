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
    unsigned char const* data = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    if (data == nullptr)
    {
        LOG_ERROR() << "Failed to import asset file " << filePath;
        return false;
    }

    graphics::IRenderer* renderModule = m_assetModule->GetEngine()->GetRenderer();
    std::unique_ptr<Texture> texture = renderModule->CreateTexture(width, height, data);
    if (texture == nullptr)
    {
        LOG_ERROR() << "Failed to create texture asset from file " << filePath;
    }

    /*
    Bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    SOIL_free_image_data(m_data);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    Unbind();
    */

    LOG() << "Imported Texture " << filePath;
    return texture;
}

bool TextureImporter::CanImport(std::string const& filePath)
{
    // TODO:
    // Refactor file extension checking into the File Module, for portability.

    if (filePath.find_last_of(".") != std::string::npos)
    {
        std::string extension = filePath.substr(filePath.find_last_of(".") + 1);
        if (extension == "png")
        {
            return true;
        }
    }

    return false;
}


}