#include "PCH.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Engine.hpp"

namespace grim
{

namespace graphics
{

ShaderProgram::ShaderProgram(grim::Engine* engine, grim::graphics::Shader* vertexShader, grim::graphics::Shader* fragmentShader) :
    m_handle(-1),
    m_engine(engine),
    m_renderer(engine->GetRenderer())
{
    // Link the given Shaders into the complete shader program
    LinkShaders(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    // Delete the shader program.
    // This will silently fail if you try to delete a nonexistent program.
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
    float time = m_engine->GetTime() / 1000.0f;

    GLint uniView = glGetUniformLocation(m_handle, "view");
    GLint uniProjection = glGetUniformLocation(m_handle, "proj");
    GLint uniTime = glGetUniformLocation(m_handle, "time");

    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform1f(uniTime, time);
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

    // Detach the shaders from the program
    glDetachShader(m_handle, vertID);
    glDetachShader(m_handle, fragID);
}

}

}
