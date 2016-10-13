/*
    OpenGLTexture.cpp
    Engine

    Declan Hopkins
    10/11/2016
*/

#include "PCH.hpp"
#include "OpenGLTexture.hpp"

namespace grim::graphics
{

OpenGLTexture::OpenGLTexture(std::string const& id, uint32_t const& width, uint32_t const& height, unsigned char const* data) :
    Texture(id, width, height),
    m_handle(0)
{
    glGenTextures(1, &m_handle);

    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(width), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &m_handle);
}

GLuint OpenGLTexture::GetHandle() const
{
    return m_handle;
}

}