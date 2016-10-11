/*
    Texture.hpp
    Engine

    Declan Hopkins
    10/6/2016

    The base class for a texture asset.
*/

#pragma once

namespace grim::assets
{

class Texture : Asset
{
public:
    Texture(std::string const& id, uint32_t const& width, uint32_t const& height);
    virtual ~Texture();

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

private:
    uint32_t m_width;
    uint32_t m_height;

    // TODO:
    // Add scale mode and texture wrap variables
};

}