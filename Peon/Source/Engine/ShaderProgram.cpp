#include "PCH.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"

namespace grim
{

ShaderProgram::ShaderProgram(grim::Shader* vertexShader, grim::Shader* fragmentShader)
{
    // Link the given Shaders into the complete shader program
    LinkShaders(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    // Delete the shader program
    glDeleteProgram(m_handle);
}

GLuint ShaderProgram::GetHandle() const
{
    return m_handle;
}

void ShaderProgram::Use()
{
    glUseProgram(m_handle);
}

void ShaderProgram::LinkShaders(grim::Shader* vertexShader, grim::Shader* fragmentShader)
{
    // Create the shader program and get an ID
    m_handle = glCreateProgram();

    // Attach the shaders to the program
    GLuint vertID = vertexShader->GetHandle();
    GLuint fragID = fragmentShader->GetHandle();
    glAttachShader(m_handle, vertID);
    glAttachShader(m_handle, fragID);

    // Link the program
    glLinkProgram(m_handle);
}

}
