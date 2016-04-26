#pragma once

class Region;

class TerrainTile
{
public:
    TerrainTile(Region* region, const glm::vec2& position);
    ~TerrainTile();

    void Render();

public:
    const static int SIZE = 32;

private:
    Region* m_region;
    grim::graphics::Transform m_transform;
    glm::vec2 m_origin;
    int m_spriteColumn;
    int m_spriteRow;

    grim::graphics::Sprite m_sprite;
};
