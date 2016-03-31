#include "PCH.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

namespace grim
{

namespace graphics
{

ShaderProgram::ShaderProgram(grim::graphics::Renderer* renderer, grim::graphics::Shader* vertexShader, grim::graphics::Shader* fragmentShader) :
    m_renderer(renderer)
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

void ShaderProgram::Bind()
{
    // Tell OpenGL to use this shader
    glUseProgram(m_handle);

    // Upload the view and projection matrices from the currently active camera
    graphics::Camera* activeCamera = m_renderer->GetActiveCamera();
    glm::mat4 viewMatrix = activeCamera->GetViewMatrix();
    glm::mat4 projectionMatrix = activeCamera->GetProjectionMatrix();

    GLint uniView = glGetUniformLocation(m_handle, "view");
    GLint uniProjection = glGetUniformLocation(m_handle, "proj");

    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::LinkShaders(grim::graphics::Shader* vertexShader, grim::graphics::Shader* fragmentShader)
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

}
