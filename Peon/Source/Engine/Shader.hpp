#pragma once

namespace grim
{

/*
    A shader that can be linked into a shader program.
*/
class Shader
{
public:
    Shader(const std::string& source, const GLenum& type, const std::string& ID);
    ~Shader();

    /*
        Returns the OpenGL ID for this Shader.
    */
    GLuint GetID() const;

private:

    /*
        Compiles the shader, given the source.
    */
    void Compile(const std::string& source);

private:
    /*
        The OpenGL ID for the shader.
    */
    GLuint m_ID;

    /*
        The OpenGL shader type of this shader, such as GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
    */
    GLenum m_type;
};

}