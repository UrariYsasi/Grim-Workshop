/*
    OpenGLShaderProgram.cpp
    Peon Engine

    Declan Hopkins
    8/8/2016
*/

#include "PCH.hpp"
#include "OpenGLShaderProgram.hpp"

namespace grim
{

OpenGLShaderProgram::OpenGLShaderProgram()
{
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
}

GLuint OpenGLShaderProgram::GetHandle() const
{
    return m_handle;
}

}