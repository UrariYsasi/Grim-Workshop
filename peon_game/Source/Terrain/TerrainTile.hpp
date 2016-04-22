#pragma once

class Region;

class TerrainTile
{
public:
    TerrainTile(Region* region, const glm::vec2& position);
    ~TerrainTile();

    void SetPosition(const glm::vec2& position);
    glm::vec2 GetPosition() const;

    void Render(grim::graphics::SpriteBatch& spriteBatch);

public:
    const static int SIZE = 32;

private:
    Region* m_region;
    glm::vec2 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    glm::vec2 m_origin;
    int m_spriteColumn;
    int m_spriteRow;

    std::unique_ptr<grim::graphics::Sprite> m_sprite;
};
