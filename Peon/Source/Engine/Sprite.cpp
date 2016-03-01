#include "PCH.hpp"
#include "Sprite.hpp"

namespace grim
{

Sprite::Sprite(grim::Texture* texture, grim::ShaderProgram* shaderProgram) :
    m_texture(texture),
    m_shaderProgram(shaderProgram),
    m_modelMatrix(1.0),
    m_VAOHandle(0),
    m_VBOHandle(0),
    m_EBOHandle(0)
{
    CreateMesh();
}

Sprite::~Sprite()
{
    // Delete buffers
    glDeleteBuffers(1, &m_EBOHandle);
    glDeleteBuffers(1, &m_VBOHandle);
    glDeleteVertexArrays(1, &m_VAOHandle);
}

void Sprite::Render(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
    // Bind the vertex array for this mesh
    glBindVertexArray(m_VAOHandle);

    // Transform the mesh
    m_modelMatrix = glm::mat4(1.0);
    m_modelMatrix = glm::translate(m_modelMatrix, position);
    m_modelMatrix = glm::scale(m_modelMatrix, scale);
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));

    // Enable our ShaderProgram
    m_shaderProgram->Use();

    // Bind our Texture
    m_texture->Bind();

    // Upload our model matrix
    GLuint modelMatrixLocation = glGetUniformLocation(m_shaderProgram->GetHandle(), "model");
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));

    // Render the mesh
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind the vertex array
    glBindVertexArray(0);
}

void Sprite::CreateMesh()
{
    // Create a VAO
    glGenVertexArrays(1, &m_VAOHandle);
    glBindVertexArray(m_VAOHandle);

    // Create a VBO
    glGenBuffers(1, &m_VBOHandle);

    // Create an EBO
    glGenBuffers(1, &m_EBOHandle);

    GLfloat vertices[] = {
        -0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,    // Top left
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // Top right
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,      // Bottom left
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f        // Bottom right
    };

    GLuint elements[] = {
        2, 3, 0,
        0, 1, 3
    };

    // Bind the vertex data to the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VAOHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the element data to the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    GLint positionAttribute = glGetAttribLocation(m_shaderProgram->GetHandle(), "inPosition");
    GLint colorAttribute = glGetAttribLocation(m_shaderProgram->GetHandle(), "inColor");
    GLint uvAttribute = glGetAttribLocation(m_shaderProgram->GetHandle(), "inTexCoord");

    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(colorAttribute);
    glEnableVertexAttribArray(uvAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}