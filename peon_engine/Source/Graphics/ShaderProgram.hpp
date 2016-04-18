#pragma once

namespace grim
{

class Engine;

namespace graphics
{

class IRenderer;

/*
    A shader program that consists of a vertex shader and a fragment shader.
*/
class ShaderProgram
{
public:
    ShaderProgram(grim::Engine* engine, grim::graphics::Shader* vertexShader, grim::graphics::Shader* fragmentShader);
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
    void LinkShaders(grim::graphics::Shader* vertexShader, grim::graphics::Shader* fragmentShader);

private:
    /*
        The OpenGL handle for the shader program.
    */
    GLuint m_handle;

    grim::Engine* m_engine;

    /*
        The Renderer that will manage this ShaderProgram.
    */
    grim::graphics::IRenderer* m_renderer;
};

}

}