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

uint8_t Shader::Compile(const std::string& source)
{
    // Convert the source into character data
    const GLchar* data = source.c_str();

    // Create the shader and get an ID
    m_handle = glCreateShader(m_type);
    if (m_handle == 0)
    {
        grim::utility::Debug::LogError("Shader created failed! OpenGL handle: %d", m_handle);
        return FAILURE;
    }

    // Upload the shader source
    glShaderSource(m_handle, // OpenGL shader handle.
                   1,        // Number of elements in the data. In our case, this is just one string.
                   &data,    // Shader source string, in Glchar* format.
                   NULL);    // Lengths for each source string. If NULL, assume null terimination.

    // Compile the shader
    glCompileShader(m_handle);

    // Check for compilation errors
    GLint status;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLchar buffer[512];

        // Retrieve the shader info log
        glGetShaderInfoLog(m_handle,          // OpenGL shader handle.
                           ARRAYSIZE(buffer), // Size of error string
                           NULL,              // Returns the length of the info log. In our case, this is irrelevant.
                           buffer);           // Returns the info log

        grim::utility::Debug::LogError("Shader compilation failed! OpenGL handle: %d \n %s", m_handle, buffer);
        return FAILURE;
    }

    return SUCCESS;
}

}

}