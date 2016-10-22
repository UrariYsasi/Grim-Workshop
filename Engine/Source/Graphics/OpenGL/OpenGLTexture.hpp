/*
    OpenGLTexture.hpp
    Engine

    Declan Hopkins
    10/11/2016

    An OpenGL texture, containing an OpenGL texture handle and an implementation necessary to upload
    texture data to the GPU.
*/

#pragma once

namespace grim::graphics
{

class OpenGLTexture : public assets::Texture
{
public:
    OpenGLTexture(std::string const& id, uint32_t const& width, uint32_t const& height, unsigned char const* data);
    virtual ~OpenGLTexture();

    GLuint GetHandle() const;

private:
    GLuint m_handle;

};

}
