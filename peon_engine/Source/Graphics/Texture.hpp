#pragma once

namespace grim
{

namespace graphics
{

/*
    A texture that can be used in rendering.
*/
class Texture
{
public:
    Texture(const std::string& textureFileName);
    ~Texture();

    /*
        Returns the OpenGL handle for this Texture.
    */
    GLuint GetHandle() const;

    int GetWidth() const;
    int GetHeight() const;

    void SetData(void* data, GLuint internalFormat, GLuint format, int width, int height);
    void SetWidth(int width);
    void SetHeight(int height);

    /*
        Bind the Texture for rendering.
    */
    void Bind();

    /*
        Unbind the Texture.
    */
    void Unbind();

private:
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

}