#pragma once

/*
    A shader program that consists of a vertex shader and a fragment shader.
*/
class ShaderProgram
{
public:
    ShaderProgram(grim::Shader* vertexShader, grim::Shader* fragmentShader);
    ~ShaderProgram();
    
    /*
        Returns the OpenGL ID for this ShaderProgram.
    */
    GLuint GetID() const;

    /*
        Activate the ShaderProgram for usage in the rendering pipeline.
    */
    void Use();

private:
    /*
        Links the given vertex and fragment shaders into the complete shader program.

        Returns the OpenGL ID for the new shader program.
    */
    void LinkShaders(grim::Shader* vertexShader, grim::Shader* fragmentShader);

private:
    /*
        The OpenGL ID for the shader program.
    */
    GLuint m_ID;
};