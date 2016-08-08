/*
    OpenGLShaderAsset.hpp
    Peon Engine

    Declan Hopkins
    8/8/2016

    An OpenGL Shader. This needs to be linked to an OpenGLShaderProgramAsset.
*/

#pragma once

namespace grim
{

class OpenGLShaderAsset : public IShaderAsset
{
public:
    OpenGLShaderAsset(const GLuint& handle, const GLenum& type);
    ~OpenGLShaderAsset();

    GLuint GetHandle() const;
    GLenum GetType() const;

private:
    /*
        The OpenGL handle for the shader.
    */

    GLuint m_handle;

    /*
        The OpenGL shader type of this shader, such as GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
    */

    GLenum m_type;
};

}