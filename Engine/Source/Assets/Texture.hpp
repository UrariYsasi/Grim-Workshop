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

class Texture : public Asset
{
public:
    Texture(std::string const& id, uint32_t const& width, uint32_t const& height);
    virtual ~Texture();

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

protected:
    uint32_t m_width;
    uint32_t m_height;

public:
    enum class WrapMode
    {
        ClampToEdge,
        ClampToBorder,
        ClampMirrored,
        Repeat,
        RepeatMirrored,
    };

    enum class FilterMode
    {
        Nearest,
        Linear,
        NearestMipmap,
        LinearMipmap,
        LinearNearestMipmap,
        NearestLinearMipmap,
        MirroredClamp
    };

    enum class TransparencyMode
    {
        Opaque,
        Transparent,
    };
};

}