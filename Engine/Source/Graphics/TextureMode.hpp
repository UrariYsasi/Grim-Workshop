/*
    TextureMode.hpp
    Engine

    Declan Hopkins
    10/13/2016
*/

#pragma once

namespace grim::graphics
{

enum class TextureWrapMode
{
    ClampToEdge,
    ClampToBorder,
    ClampMirrored,
    Repeat,
    RepeatMirrored,
};

enum class TextureFilter
{
    Nearest,
    Linear,
    NearestMipmap,
    LinearMipmap,
    LinearNearestMipmap,
    NearestLinearMipmap,
    MirroredClamp
};

}