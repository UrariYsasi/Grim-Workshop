#include "PCH.hpp"
#include "Texture.hpp"

namespace grim
{

namespace graphics
{

Texture::Texture(const std::string& path, const bool& isOpaque, const GLenum& wrapMode, const GLenum& scaleMode) :
    m_isOpaque(isOpaque),
    m_handle(-1),
    m_width(0),
    m_height(0),
    m_data(nullptr)
{
    // Generate the OpenGL handle
    glGenTextures(1, &m_handle);

    // Bind the texture
    Bind();

    // Upload the image data to the texture
    m_data = SOIL_load_image(path.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    SOIL_free_image_data(m_data);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, scaleMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // We can unbind the texture now.
    Unbind();
}

Texture::~Texture()
{
    // Delete the OpenGL texture
    glDeleteTextures(1, &m_handle);
}

GLuint Texture::GetHandle() const
{
    return m_handle;
}

int Texture::GetWidth() const
{
    return m_width;
}

int Texture::GetHeight() const
{
    return m_height;
}

void Texture::SetWidth(int width)
{
    m_width = width;
}

void Texture::SetHeight(int height)
{
    m_height = height;
}

void Texture::SetData(void* data, GLuint internalFormat, GLuint format, int width, int height)
{
    SetWidth(width);
    SetHeight(height);

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    Unbind();
}

bool Texture::IsOpaque() const
{
    return m_isOpaque;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

}

}