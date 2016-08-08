/*
    OpenGLShaderAsset.cpp
    Peon Engine

    Declan Hopkins
    8/8/2016
*/

#include "PCH.hpp"
#include "OpenGLShaderAsset.hpp"

namespace grim
{

OpenGLShaderAsset::OpenGLShaderAsset(const GLuint& handle, const GLenum& type) :
    m_handle(handle),
    m_type(type)
{
}

OpenGLShaderAsset::~OpenGLShaderAsset()
{
    glDeleteShader(m_handle);
}

GLuint OpenGLShaderAsset::GetHandle() const
{
    return m_handle;
}

GLenum OpenGLShaderAsset::GetType() const
{
    return m_type;
}

}