/*
    Material.cpp
    Engine

    Declan Hopkins
    10/22/2016
*/

#include "PCH.hpp"
#include "Material.hpp"

namespace grim::assets
{

Material::Material(std::string const& id, Texture* const texture, Texture::WrapMode const& textureWrapMode, Texture::FilterMode const& textureFilterMode, Texture::TransparencyMode const& textureTransparencyMode, graphics::ShaderProgram* const shaderProgram) :
    Asset(id),
    m_texture(texture),
    m_textureWrapMode(textureWrapMode),
    m_textureFilterMode(textureFilterMode),
    m_textureTransparencyMode(textureTransparencyMode),
    m_shaderProgram(shaderProgram)
{
}

Material::~Material()
{
}

Texture* Material::GetTexture() const
{
    return m_texture;
}

Texture::WrapMode Material::GetTextureWrapMode() const
{
    return m_textureWrapMode;
}

Texture::FilterMode Material::GetTextureFilterMode() const
{
    return m_textureFilterMode;
}

Texture::TransparencyMode Material::GetTextureTransparencyMode() const
{
    return m_textureTransparencyMode;
}

graphics::ShaderProgram* Material::GetShaderProgram() const
{
    return m_shaderProgram;
}

}