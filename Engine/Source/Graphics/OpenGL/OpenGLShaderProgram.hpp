/*
    OpenGLShaderProgram.hpp
    Peon Engine

    Declan Hopkins
    8/8/2016

    An OpenGL Shader Program.
*/

#pragma once

namespace grim
{

class OpenGLShaderProgram : public IShaderProgram
{
public:
    OpenGLShaderProgram();
    ~OpenGLShaderProgram();

    GLuint GetHandle() const;

private:
    /*
        The OpenGL handle for the shader program.
    */

    GLuint m_handle;
};

}