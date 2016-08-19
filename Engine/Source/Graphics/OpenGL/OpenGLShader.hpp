/*
    OpenGLShader.hpp
    Peon Engine

    Declan Hopkins
    8/8/2016

    An OpenGL Shader. This needs to be linked to an OpenGLShaderProgram.
*/

#pragma once

namespace grim
{

class OpenGLShader : public IShader
{
public:
    OpenGLShader(const GLuint& handle, const GLenum& type);
    ~OpenGLShader();

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