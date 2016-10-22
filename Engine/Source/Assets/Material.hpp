/*
    Material.hpp
    Engine

    Declan Hopkins
    10/22/2016

    A material asset ties together textures, shaders, and other attributes to be used for rendering.
*/

#pragma once

namespace grim::assets
{

class Material : public Asset
{
public:
    Material(std::string const& id, Texture* const texture, Texture::WrapMode const& textureWrapMode, Texture::FilterMode const& textureFilterMode, Texture::TransparencyMode const& textureTransparencyMode, graphics::ShaderProgram* const shaderProgram);
    virtual ~Material();

    Texture* GetTexture() const;
    Texture::WrapMode GetTextureWrapMode() const;
    Texture::FilterMode GetTextureFilterMode() const;
    Texture::TransparencyMode GetTextureTransparencyMode() const;
    graphics::ShaderProgram* GetShaderProgram() const;

private:
    Texture* m_texture;
    Texture::WrapMode m_textureWrapMode;
    Texture::FilterMode m_textureFilterMode;
    Texture::TransparencyMode m_textureTransparencyMode;
    graphics::ShaderProgram* m_shaderProgram;
};

}