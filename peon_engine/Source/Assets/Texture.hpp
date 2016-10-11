/*
    Asset.hpp
    Engine

    Declan Hopkins
    10/6/2016

    The base class for a game asset.
*/

#pragma once

namespace grim::assets
{

class Texture
{
public:
    Texture();
    Texture(const bool& isOpaque);
    Texture(const bool& isOpaque, const GLenum& wrapMode, const GLenum& scaleMode);
    ~Texture();

    bool LoadFromFile(const std::string& path);

    /*
        Returns the OpenGL handle for this Texture.
    */
    GLuint GetHandle() const;

    int GetWidth() const;
    int GetHeight() const;

    void SetWidth(int width);
    void SetHeight(int height);

    bool IsOpaque() const;

    /*
        Bind the Texture for rendering.
    */
    void Bind();

    /*
        Unbind the Texture.
    */
    void Unbind();

private:
    bool m_isOpaque;
    bool m_isBound;

    /*
        The OpenGL handle for the texture.
    */
    GLuint m_handle;

    /*
        The width, in pixels, of the texture.
    */
    int m_width;

    /*
        The height, in pixels, of the texture.
    */
    int m_height;

    /*
        The texture data.
    */
    unsigned char* m_data;
};

}