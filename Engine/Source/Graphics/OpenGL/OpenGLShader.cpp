/*
    OpenGLShader.cpp
    Peon Engine

    Declan Hopkins
    8/8/2016
*/

#include "PCH.hpp"
#include "OpenGLShader.hpp"

namespace grim
{

OpenGLShader::OpenGLShader(const GLuint& handle, const GLenum& type) :
    m_handle(handle),
    m_type(type)
{
}

OpenGLShader::~OpenGLShader()
{
    glDeleteShader(m_handle);
}

GLuint OpenGLShader::GetHandle() const
{
    return m_handle;
}

GLenum OpenGLShader::GetType() const
{
    return m_type;
}

}