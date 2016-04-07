#include "PCH.hpp"
#include "SpriteBatch.hpp"

namespace grim
{

namespace graphics
{

SpriteBatch::SpriteBatch() :
    m_shaderProgram(nullptr),
    m_texture(nullptr),
    m_spriteCount(0),
    m_vertexCount(0),
    m_modelMatrix(1.0),
    m_VAOHandle(0),
    m_VBOHandle(0),
    m_EBOHandle(0),
    m_primitiveType(GL_TRIANGLES)
{
    // Create VAO
    glGenVertexArrays(1, &m_VAOHandle);

    // Create VBO
    glGenBuffers(1, &m_VBOHandle);

    // Create EBO
    glGenBuffers(1, &m_EBOHandle);
}

SpriteBatch::~SpriteBatch()
{
    // Delete EBO
    glDeleteBuffers(1, &m_EBOHandle);

    // Delete VBO
    glDeleteBuffers(1, &m_VBOHandle);

    // Delete VAO
    glDeleteVertexArrays(1, &m_VAOHandle);
}

void SpriteBatch::AddSprite(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, grim::graphics::Sprite* sprite)
{
    grim::graphics::Texture* texture = sprite->spriteSheet;
    grim::graphics::ShaderProgram* shaderProgram = sprite->shaderProgram;

    // If the Texture or ShaderProgram changes, we have to end this batch and begin a new one.
    if (m_texture != texture || m_shaderProgram != shaderProgram)
    {
        End();
        Begin();
    }

    m_texture = texture;
    m_shaderProgram = shaderProgram;

    // Calculate texture region
    uint16_t spriteSheetWidth = texture->GetWidth();
    uint16_t spriteSheetHeight = texture->GetHeight();
    uint16_t spriteSheetRows = spriteSheetHeight / sprite->height;
    uint16_t spriteSheetCols = spriteSheetWidth / sprite->width;
    uint16_t col = static_cast<uint16_t>(sprite->frame / spriteSheetCols);
    uint16_t row = sprite->frame % spriteSheetCols;
    double spriteTexelWidth = (double)sprite->width / spriteSheetWidth;
    double spriteTexelHeight = (double)sprite->height / spriteSheetHeight;
    double spriteTexelX = row * spriteTexelWidth;
    double spriteTexelY = col * spriteTexelHeight;

    // Create rotation matrix
    glm::mat4 rotationMatrix(1.0f);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Calculate vertex positions
    glm::vec4 pos(position, 0.0f);
    glm::vec4 topLeft = (glm::vec4(-(scale.x / 2), -(scale.y / 2), 0.0f, 1.0f) * rotationMatrix) + pos;
    glm::vec4 topRight = (glm::vec4((scale.x / 2), -(scale.y / 2), 0.0f, 1.0f) * rotationMatrix) + pos;
    glm::vec4 bottomLeft = (glm::vec4(-(scale.x / 2), (scale.y / 2), 0.0f, 1.0f) * rotationMatrix) + pos;
    glm::vec4 bottomRight = (glm::vec4((scale.x / 2), (scale.y / 2), 0.0f, 1.0f) * rotationMatrix) + pos;

    // Vertices
    AddVertex(grim::graphics::Vertex(glm::vec3(topLeft.x, topLeft.y, topLeft.z), sprite->color, glm::vec2(spriteTexelX, spriteTexelY)));
    AddVertex(grim::graphics::Vertex(glm::vec3(topRight.x, topRight.y, topRight.z), sprite->color, glm::vec2(spriteTexelX + spriteTexelWidth, spriteTexelY)));
    AddVertex(grim::graphics::Vertex(glm::vec3(bottomLeft.x, bottomLeft.y, bottomLeft.z), sprite->color, glm::vec2(spriteTexelX, spriteTexelY + spriteTexelHeight)));
    AddVertex(grim::graphics::Vertex(glm::vec3(bottomRight.x, bottomRight.y, bottomRight.z), sprite->color, glm::vec2(spriteTexelX + spriteTexelWidth, spriteTexelY + spriteTexelHeight)));

    // Element indices
    AddElementIndex(m_vertexCount + 0);
    AddElementIndex(m_vertexCount + 1);
    AddElementIndex(m_vertexCount + 2);
    AddElementIndex(m_vertexCount + 2);
    AddElementIndex(m_vertexCount + 3);
    AddElementIndex(m_vertexCount + 1);

    m_spriteCount++;
    m_vertexCount += 4;
}

void SpriteBatch::Begin()
{
    Clear();
}

void SpriteBatch::End()
{
    if (m_vertexDataBuffer.size() == 0)
    {
        return;
    }

    Upload();
    Render();
}

void SpriteBatch::AddVertex(const grim::graphics::Vertex& vertex)
{
    m_vertexDataBuffer.push_back(vertex);
}

void SpriteBatch::AddElementIndex(int index)
{
    m_elementDataBuffer.push_back(index);
}

void SpriteBatch::Clear()
{
    m_spriteCount = 0;
    m_vertexCount = 0;
    m_vertexDataBuffer.clear();
    m_elementDataBuffer.clear();
    m_texture = nullptr;
    m_shaderProgram = nullptr;
    m_primitiveType = GL_TRIANGLES;
}

void SpriteBatch::Upload()
{
    // Get raw vertex data
    GLfloat* vertices = reinterpret_cast<GLfloat*>(m_vertexDataBuffer.data());

    // Get raw element data
    int* elements = m_elementDataBuffer.data();

    // Bind the VAO
    glBindVertexArray(m_VAOHandle);

    // Bind the VBO and upload the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * (m_vertexCount * 9), vertices, GL_DYNAMIC_DRAW);

    // Bind the EBO and upload the element data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements[0]) * (m_spriteCount * 6), elements, GL_DYNAMIC_DRAW);

    GLint positionAttribute = glGetAttribLocation(m_shaderProgram->GetHandle(), "inPosition");
    GLint colorAttribute = glGetAttribLocation(m_shaderProgram->GetHandle(), "inColor");
    GLint uvAttribute = glGetAttribLocation(m_shaderProgram->GetHandle(), "inTexCoord");

    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(colorAttribute);
    glEnableVertexAttribArray(uvAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Delete raw vertex data
    //delete[] vertices;
}

void SpriteBatch::Render()
{
    // Bind the VAO for this mesh
    glBindVertexArray(m_VAOHandle);

    // Bind the EBO for this mesh
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOHandle);

    // Bind our ShaderProgram
    m_shaderProgram->Bind();

    // Upload our model matrix
    GLuint uniModel = glGetUniformLocation(m_shaderProgram->GetHandle(), "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));

    // Bind our Texture
    m_texture->Bind();

    // Render the mesh
    glDrawElements(GL_TRIANGLES, m_spriteCount * 6, GL_UNSIGNED_INT, 0);

    // Unbind our Texture
    m_texture->Unbind();

    // Unbind our ShaderProgram
    m_shaderProgram->Unbind();

    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Unbind the vertex array
    glBindVertexArray(0);
}

}

}