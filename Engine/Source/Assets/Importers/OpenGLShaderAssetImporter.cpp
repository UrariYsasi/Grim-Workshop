/*
    OpenGLShaderAssetImporter.cpp
    Peon Engine

    Declan Hopkins
    8/7/2016
*/

#include "PCH.hpp"
#include "OpenGLShaderAssetImporter.hpp"

namespace grim
{

OpenGLShaderAssetImporter::OpenGLShaderAssetImporter()
{
}

OpenGLShaderAssetImporter::~OpenGLShaderAssetImporter()
{
}

std::unique_ptr<IAsset> OpenGLShaderAssetImporter::Import(const std::string& path)
{
    LOG() << "Importing Shader " << path;

    std::ifstream input(path);
    if (!input.is_open())
    {
        LOG_ERROR() << "Failed to open file " << path;
        return nullptr;
    }

    std::ostringstream ss;
    ss << input.rdbuf();

    // Figure out of it's a vertex or fragment shader
    GLenum shaderType;
    if (path.find_last_of("_") != std::string::npos)
    {
        std::string typeExtension = path.substr(path.find_last_of("_") + 1, 4);
        if (typeExtension == "vert")
        {
            shaderType = GL_VERTEX_SHADER;
        }
        else if (typeExtension == "frag")
        {
            shaderType = GL_FRAGMENT_SHADER;
        }
        else
        {
            LOG_ERROR() << "Couldn't figure out of the Shader was a vertex or fragment shader!";
            return nullptr;
        }
    }

    // Get the raw source
    const GLchar* data = ss.str().c_str();

    // Create the shader and get a handle
    GLuint handle = glCreateShader(shaderType);
    if (handle == 0)
    {
        LOG_ERROR() << "Shader creation failed! Path: " << path;
        return nullptr;
    }

    // Upload the shader source
    glShaderSource(handle, // OpenGL shader handle.
        1,                 // Number of elements in the data. In our case, this is just one string.
        &data,             // Shader source string, in Glchar* format.
        NULL);             // Lengths for each source string. If NULL, assume null terimination.

    // Compile the shader
    glCompileShader(handle);

    // Check for compilation errors
    GLint status;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLchar buffer[512];

        // Retrieve the shader info log
        glGetShaderInfoLog(handle, // OpenGL shader handle.
            ARRAYSIZE(buffer),     // Size of error string
            NULL,                  // Returns the length of the info log. In our case, this is irrelevant.
            buffer);               // Returns the info log

        LOG_ERROR() << "Shader compilation failed! " << buffer << " Path: " << path;
        return nullptr;
    }

    // Create and return the Shader asset
    return std::make_unique<OpenGLShaderAsset>(handle, shaderType);
}

bool OpenGLShaderAssetImporter::CanImport(const std::string& path)
{
    // Get the file extension
    if (path.find_last_of(".") != std::string::npos)
    {
        std::string extension = path.substr(path.find_last_of(".") + 1);
        if (extension == "glsl")
        {
            return true;
        }
    }

    return false;
}

std::string GetFileExtension(const std::string& FileName)
{
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".") + 1);
    return "";
}

}