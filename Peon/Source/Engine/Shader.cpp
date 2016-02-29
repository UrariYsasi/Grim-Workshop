#include "PCH.hpp"
#include "Shader.hpp"

namespace grim
{

Shader::Shader(const std::string& source, const GLenum& type, const std::string& ID) :
    m_ID(-1),
    m_type(type)
{
    // Compile the shader from the given source.
    Compile(source);
}

Shader::~Shader()
{
    // Delete the shader.
    glDeleteShader(m_ID);
}

GLuint Shader::GetID() const
{
    return m_ID;
}

void Shader::Compile(const std::string& source)
{
    // Convert the source into character data
    const GLchar* data = source.c_str();

    // Create the shader and get an ID
    m_ID = glCreateShader(m_type);

    // Upload the shader source
    glShaderSource(m_ID, 1, &data, NULL);

    // Compile the shader
    glCompileShader(m_ID);

    // Monitor compilation
    GLint status;
    glGetShaderiv(m_ID, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(m_ID, 512, NULL, buffer);
        Debug::LogError("Shader failed to compile!");
        Debug::LogError(buffer);
    }
}

}