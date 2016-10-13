/*
    Texture.cpp
    Engine

    Declan Hopkins
    10/11/2016
*/

#include "PCH.hpp"
#include "Texture.hpp"

namespace grim::assets
{

Texture::Texture(std::string const& id, uint32_t const& width, uint32_t const& height) :
    Asset(id),
    m_width(width),
    m_height(height)
{
}

Texture::~Texture()
{
}

uint32_t Texture::GetWidth() const
{
    return m_width;
}

uint32_t Texture::GetHeight() const
{
    return m_height;
}

}