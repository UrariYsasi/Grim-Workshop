#include "PCH.hpp"
#include "Sprite.hpp"

namespace grim
{

namespace graphics
{

Sprite::Sprite(assets::Material* material, uint32_t width, uint32_t height, uint32_t frame) :
    m_mesh(PrimitiveType::TRIANGLES),
    m_material(material),
    m_width(width),
    m_height(height),
    m_frame(frame),
    m_meshWidth(width),
    m_meshHeight(height)
{
    Construct();
}

Sprite::Sprite(assets::Material* material) :
    Sprite(material, material->GetTexture()->GetWidth(), material->GetTexture()->GetHeight(), 0)
{
}

Sprite::Sprite() :
    Sprite(nullptr, 0, 0, 0)
{
}

void Sprite::Construct()
{
    if (m_material == nullptr || m_width == 0 || m_height == 0)
    {
        return;
    }

    // TODO origin points

    // Calculate texture region
    uint32_t spriteSheetWidth = m_material->GetTexture()->GetWidth();
    uint32_t spriteSheetHeight = m_material->GetTexture()->GetHeight();
    uint32_t spriteSheetRows = spriteSheetHeight / m_height;
    uint32_t spriteSheetCols = spriteSheetWidth / m_width;
    m_frame = m_frame % (spriteSheetRows * spriteSheetCols);
    uint32_t col = static_cast<uint32_t>(m_frame / spriteSheetCols);
    uint32_t row = m_frame % spriteSheetCols;
    float spriteTexelWidth = (float)m_width / spriteSheetWidth;
    float spriteTexelHeight = (float)m_height / spriteSheetHeight;
    float spriteTexelX = row * spriteTexelWidth;
    float spriteTexelY = col * spriteTexelHeight;

    // Take texture repeating into consideration
    if (m_meshWidth > m_width)
    {
        spriteTexelWidth = 1.0f * (m_meshWidth / m_width);
    }

    if (m_meshHeight > m_height)
    {
        spriteTexelHeight = 1.0f * (m_meshHeight / m_height);
    }

    // Calculate vertex positions
    glm::vec3 topLeft(-(m_meshWidth / 2), -(m_meshHeight / 2), 0.0f);
    glm::vec3 topRight((m_meshWidth / 2), -(m_meshHeight / 2), 0.0f);
    glm::vec3 bottomLeft(-(m_meshWidth / 2), (m_meshHeight / 2), 0.0f);
    glm::vec3 bottomRight((m_meshWidth / 2), (m_meshHeight / 2), 0.0f);

    // Clear current mesh
    m_mesh.ClearData();

    // Create vertices
    Color color(1.0f, 1.0f, 1.0f, 1.0f);
    m_mesh.AddVertex(grim::graphics::Vertex(glm::vec3(topLeft.x, topLeft.y, topLeft.z), color, glm::vec2(spriteTexelX, spriteTexelY)));
    m_mesh.AddVertex(grim::graphics::Vertex(glm::vec3(topRight.x, topRight.y, topRight.z), color, glm::vec2(spriteTexelX + spriteTexelWidth, spriteTexelY)));
    m_mesh.AddVertex(grim::graphics::Vertex(glm::vec3(bottomLeft.x, bottomLeft.y, bottomLeft.z), color, glm::vec2(spriteTexelX, spriteTexelY + spriteTexelHeight)));
    m_mesh.AddVertex(grim::graphics::Vertex(glm::vec3(bottomRight.x, bottomRight.y, bottomRight.z), color, glm::vec2(spriteTexelX + spriteTexelWidth, spriteTexelY + spriteTexelHeight)));

    // Create indices
    m_mesh.AddIndex(0);
    m_mesh.AddIndex(1);
    m_mesh.AddIndex(2);
    m_mesh.AddIndex(2);
    m_mesh.AddIndex(3);
    m_mesh.AddIndex(1);
}

void Sprite::SetWidth(const uint32_t& width)
{
    m_width = width;
    Construct();
}

void Sprite::SetHeight(const uint32_t& height)
{
    m_height = height;
    Construct();
}

void Sprite::SetMeshWidth(const float& meshWidth)
{
    m_meshWidth = meshWidth;
    Construct();
}

void Sprite::SetMeshHeight(const float& meshHeight)
{
    m_meshHeight = meshHeight;
    Construct();
}

void Sprite::SetFrame(const uint32_t& frame)
{
    m_frame = frame;
    Construct();
}

Mesh* Sprite::GetMesh()
{
    return &m_mesh;
}

assets::Material* Sprite::GetMaterial() const
{
    return m_material;
}

uint32_t Sprite::GetWidth() const
{
    return m_width;
}

uint32_t Sprite::GetHeight() const
{
    return m_height;
}

float Sprite::GetMeshWidth() const
{
    return m_meshWidth;
}

float Sprite::GetMeshHeight() const
{
    return m_meshHeight;
}

uint32_t Sprite::GetFrame() const
{
    return m_frame;
}

}

}