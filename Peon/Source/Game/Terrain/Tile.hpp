#pragma once

class Game;

class Tile
{
public:
    Tile(Game* game, const Vector2D& position, const int& spriteColumn, const int& spriteRow);
    virtual ~Tile();

    void SetPosition(const Vector2D& position);
    Vector2D GetPosition() const;

    virtual void Render() = 0;

protected:
    const static int TILE_SIZE = 32;

    Game* m_game;
    Vector2D m_origin;
    Vector2D m_position;
    std::string m_spritesheet;
    int m_spriteColumn;
    int m_spriteRow;
};