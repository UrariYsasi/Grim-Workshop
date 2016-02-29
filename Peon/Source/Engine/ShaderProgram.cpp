#include "PCH.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"

ShaderProgram::ShaderProgram(grim::Shader* vertexShader, grim::Shader* fragmentShader)
{
    // Link the given Shaders into the complete shader program
    LinkShaders(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    // Delete the shader program
    glDeleteProgram(m_ID);
}

GLuint ShaderProgram::GetID() const
{
    return m_ID;
}

void ShaderProgram::Use()
{
    glUseProgram(m_ID);
}

void ShaderProgram::LinkShaders(grim::Shader* vertexShader, grim::Shader* fragmentShader)
{
    // Create the shader program and get an ID
    m_ID = glCreateProgram();

    // Attach the shaders to the program
    GLuint vertID = vertexShader->GetID();
    GLuint fragID = fragmentShader->GetID();
    glAttachShader(m_ID, vertID);
    glAttachShader(m_ID, fragID);

    // Link the program
    glLinkProgram(m_ID);
}
