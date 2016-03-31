#include "PCH.hpp"
#include "Shader.hpp"

namespace grim
{

namespace graphics
{

Shader::Shader(const std::string& source, const GLenum& type, const std::string& ID) :
    m_handle(-1),
    m_type(type)
{
    // Compile the shader from the given source.
    Compile(source);
}

Shader::~Shader()
{
    // Delete the shader.
    glDeleteShader(m_handle);
}

GLuint Shader::GetHandle() const
{
    return m_handle;
}

void Shader::Compile(const std::string& source)
{
    // Convert the source into character data
    const GLchar* data = source.c_str();

    // Create the shader and get an ID
    m_handle = glCreateShader(m_type);

    // Upload the shader source
    glShaderSource(m_handle, 1, &data, NULL);

    // Compile the shader
    glCompileShader(m_handle);

    // Monitor compilation
    GLint status;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(m_handle, 512, NULL, buffer);
        grim::utility::Debug::LogError("Shader failed to compile!");
        grim::utility::Debug::LogError(buffer);
    }
}

}

}