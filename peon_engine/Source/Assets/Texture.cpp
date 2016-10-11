#include "PCH.hpp"
#include "Texture.hpp"

namespace grim::assets
{

Texture::Texture() :
    Texture(true, GL_CLAMP_TO_EDGE, GL_NEAREST)
{
}

Texture::Texture(const bool& isOpaque) :
    Texture(isOpaque, GL_CLAMP_TO_EDGE, GL_NEAREST)
{
}

Texture::Texture(const bool& isOpaque, const GLenum& wrapMode, const GLenum& scaleMode) :
    m_isOpaque(isOpaque),
    m_isBound(false),
    m_handle(-1),
    m_width(0),
    m_height(0),
    m_data(nullptr)
{
    // Generate the OpenGL handle
    glGenTextures(1, &m_handle);

    // Bind the texture
    Bind();

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

bool Texture::LoadFromFile(const std::string& path)
{
    // Upload the image data to the texture
    m_data = SOIL_load_image(path.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
    if (m_data == nullptr)
    {
        return false;
    }
    
    Bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    SOIL_free_image_data(m_data);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    Unbind();

    return true;
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

bool Texture::IsOpaque() const
{
    return m_isOpaque;
}

void Texture::Bind()
{
    if (m_isBound)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_handle);
    m_isBound = true;
}

void Texture::Unbind()
{
    if (!m_isBound)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    m_isBound = false;
}

}