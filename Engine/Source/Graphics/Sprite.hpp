#pragma once

namespace grim
{

namespace graphics
{

class Sprite
{
public:
    Sprite(assets::Material* material, uint32_t width, uint32_t height, uint32_t frame);
    Sprite(assets::Material* material);
    Sprite();

    void SetWidth(const uint32_t& width);
    void SetHeight(const uint32_t& height);
    void SetMeshWidth(const float& meshWidth);
    void SetMeshHeight(const float& meshHeight);
    void SetFrame(const uint32_t& frame);

    Mesh* GetMesh();
    assets::Material* GetMaterial() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    float GetMeshWidth() const;
    float GetMeshHeight() const;
    uint32_t GetFrame() const;

private:
    void Construct();

private:
    Mesh m_mesh;
    assets::Material* m_material;
    uint32_t m_width;
    uint32_t m_height;
    float m_meshWidth;
    float m_meshHeight;
    uint32_t m_frame;

};

}

}