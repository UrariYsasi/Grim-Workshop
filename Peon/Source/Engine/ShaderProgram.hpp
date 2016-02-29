#pragma once

/*
    A shader program that consists of a vertex shader and a fragment shader.
*/
class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
    ~ShaderProgram();
    
    /*
        Returns the OpenGL ID for this ShaderProgram.
    */
    GLuint GetID();

    /*
        Activate the ShaderProgram for usage in the rendering pipeline.
    */
    void Use();

private:

    /*
        Compiles a shader, given the source and the type.

        Returns the OpenGL ID for that shader.
    */
    GLuint CompileShader(const std::string& source, GLenum shaderType);

    /*
        Links the given vertex and fragment shaders into the complete shader program.

        Returns the OpenGL ID for the new shader program.
    */
    GLuint LinkShaders(GLuint vertID, GLuint fragID);

private:
    /*
        The OpenGL ID for the shader program.
    */
    GLuint m_ID;
};