#include "PCH.hpp"
#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    // Compile the shaders
    GLuint vertID = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragID = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    // Link them into the complete shader program
    m_ID = LinkShaders(vertID, fragID);
}

ShaderProgram::~ShaderProgram()
{
    // Delete the shader program
    glDeleteProgram(m_ID);
}

GLuint ShaderProgram::GetID()
{
    return m_ID;
}

void ShaderProgram::Use()
{
    glUseProgram(m_ID);
}

GLuint ShaderProgram::CompileShader(const std::string& source, GLenum shaderType)
{
    Debug::Log("Compiling shader...");

    // Convert the source into data
    const GLchar* data = source.c_str();

    // Create the shader and get an ID
    GLuint ID = glCreateShader(shaderType);

    // Upload the shader source
    glShaderSource(ID, 1, &data, NULL);

    // Compile the shader
    glCompileShader(ID);

    // Monitor compilation
    GLint status;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(ID, 512, NULL, buffer);
        Debug::LogError(buffer);
        Debug::LogError("Shader failed to compile!");
    }

    return ID;
}

GLuint ShaderProgram::LinkShaders(GLuint vertID, GLuint fragID)
{
    Debug::Log("Linking shader program...");

    // Create the shader program and get an ID
    GLuint ID = glCreateProgram();

    // Attach the shaders to the program
    glAttachShader(ID, vertID);
    glAttachShader(ID, fragID);

    // Link the program
    glLinkProgram(ID);

    // Delete the individual shaders; we don't need them anymore.
    glDeleteShader(vertID);
    glDeleteShader(fragID);

    return ID;
}