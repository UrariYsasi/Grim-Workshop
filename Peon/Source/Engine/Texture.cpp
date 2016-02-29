#include "PCH.hpp"
#include "Texture.hpp"

namespace grim
{

Texture::Texture(const std::string& textureFileName) :
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
    std::string path = "Resources/Textures/" + textureFileName;
    m_data = SOIL_load_image(path.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
    SOIL_free_image_data(m_data);

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

}