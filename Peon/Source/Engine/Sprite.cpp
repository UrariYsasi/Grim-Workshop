#include "PCH.hpp"
#include "Sprite.hpp"

namespace grim
{

Sprite::Sprite(grim::Texture* spriteSheet, grim::ShaderProgram* shaderProgram, int frame) :
    m_spriteSheet(spriteSheet),
    m_shaderProgram(shaderProgram),
    m_frame(frame),
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
    // Bind the VAO for this mesh
    glBindVertexArray(m_VAOHandle);

    // Bind the EBO for this mesh
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);

    // Bind our ShaderProgram
    m_shaderProgram->Bind();

    // Transform the mesh
    m_modelMatrix = glm::mat4(1.0);
    m_modelMatrix = glm::translate(m_modelMatrix, position);
    m_modelMatrix = glm::scale(m_modelMatrix, scale);
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    m_modelMatrix = glm::rotate(m_modelMatrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));

    // Upload our model matrix
    GLuint uniModel = glGetUniformLocation(m_shaderProgram->GetHandle(), "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));

    // Bind our Texture
    m_spriteSheet->Bind();

    // Render the mesh
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unbind our Texture
    m_spriteSheet->Unbind();

    // Unbind our ShaderProgram
    m_shaderProgram->Unbind();

    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the vertex array
    glBindVertexArray(0);
}

void Sprite::CreateMesh()
{
    // Create a VAO
    glGenVertexArrays(1, &m_VAOHandle);

    // Create a VBO
    glGenBuffers(1, &m_VBOHandle);

    // Create an EBO
    glGenBuffers(1, &m_EBOHandle);

    // (m_width / m_spriteSheet->GetWidth());
    double spriteTexelWidth = 32.0 / m_spriteSheet->GetWidth();
    double spriteTexelHeight = 32.0 / m_spriteSheet->GetHeight();
    double spriteTexelX = m_frame * spriteTexelWidth;
    double spriteTexelY = m_frame * spriteTexelHeight;

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, spriteTexelX, spriteTexelY,                                       // Top left
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, spriteTexelX + spriteTexelWidth, spriteTexelY,                     // Top right
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, spriteTexelX, spriteTexelY + spriteTexelHeight,                    // Bottom left
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, spriteTexelX + spriteTexelWidth, spriteTexelY + spriteTexelHeight   // Bottom right
    };

    GLuint elements[] = {
        2, 3, 0,
        0, 1, 3
    };

    // Bind the VAO
    glBindVertexArray(m_VAOHandle);

    // Bind the VBO and upload the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO and upload the vertex data
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

    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO
    glBindVertexArray(0);
}

}