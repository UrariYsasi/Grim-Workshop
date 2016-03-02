#pragma once

namespace grim
{

class Renderer;

/*
    A shader program that consists of a vertex shader and a fragment shader.
*/
class ShaderProgram
{
public:
    ShaderProgram(grim::Renderer* renderer, grim::Shader* vertexShader, grim::Shader* fragmentShader);
    ~ShaderProgram();

    /*
        Returns the OpenGL handle for this ShaderProgram.
    */
    GLuint GetHandle() const;

    /*
        Bind the ShaderProgram for usage in the rendering pipeline.
    */
    void Bind();

    /*
        Unbind the ShaderProgram.
    */
    void Unbind();

private:
    /*
        Links the given vertex and fragment shaders into the complete shader program.

        Returns the OpenGL ID for the new shader program.
    */
    void LinkShaders(grim::Shader* vertexShader, grim::Shader* fragmentShader);

private:
    /*
        The OpenGL handle for the shader program.
    */
    GLuint m_handle;

    /*
        The Renderer that will manage this ShaderProgram.
    */
    grim::Renderer* m_renderer;
};

}