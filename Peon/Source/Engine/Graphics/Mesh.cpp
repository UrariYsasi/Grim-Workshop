#include "PCH.hpp"
#include "Mesh.hpp"

namespace grim
{

namespace graphics
{

Mesh::Mesh(grim::graphics::ShaderProgram* shaderProgram, grim::graphics::Texture* texture) :
    m_shaderProgram(shaderProgram),
    m_texture(texture),
    m_modelMatrix(1.0),
    m_VAOHandle(0),
    m_VBOHandle(0),
    m_EBOHandle(0),
    m_mode(GL_TRIANGLES)
{
    // Create a VAO
    glGenVertexArrays(1, &m_VAOHandle);

    // Create a VBO
    glGenBuffers(1, &m_VBOHandle);

    // Create an EBO
    glGenBuffers(1, &m_EBOHandle);
}

Mesh::~Mesh()
{
    // Delete buffers
    glDeleteBuffers(1, &m_EBOHandle);
    glDeleteBuffers(1, &m_VBOHandle);
    glDeleteVertexArrays(1, &m_VAOHandle);
}

void Mesh::Render(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
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
    if (m_texture != nullptr)
    {
        m_texture->Bind();
    }

    // Render the mesh
    glDrawElements(m_mode, 4, GL_UNSIGNED_INT, 0);

    // Unbind our Texture
    if (m_texture != nullptr)
    {
        m_texture->Unbind();
    }

    // Unbind our ShaderProgram
    m_shaderProgram->Unbind();

    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the vertex array
    glBindVertexArray(0);
}

void Mesh::UploadVertexData(GLfloat* vertices, unsigned int verticesSize)
{
    // Bind the VAO
    glBindVertexArray(m_VAOHandle);

    // Bind the VBO and upload the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

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

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::UploadElementData(GLuint* elements, unsigned int elementsSize)
{
    // Bind the VAO
    glBindVertexArray(m_VAOHandle);

    // Bind the EBO and upload the vertex data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsSize, elements, GL_STATIC_DRAW);

    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::SetRenderMode(GLenum mode)
{
    m_mode = mode;
}

}

}