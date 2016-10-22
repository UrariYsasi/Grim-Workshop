#pragma once

namespace grim
{

namespace graphics
{

class Mesh
{
public:
    Mesh();
    Mesh(const PrimitiveType& primitiveType);
    ~Mesh();

    void AddVertex(const Vertex vertex);
    void AddIndex(const uint32_t index);
    void ClearData();

    PrimitiveType GetPrimitiveType() const;
    std::vector<Vertex> GetVertexData() const;
    std::vector<uint32_t> GetIndexData() const;
    uint32_t GetVertexCount() const;
    uint32_t GetIndexCount() const;

private:
    PrimitiveType m_primitiveType;
    std::vector<Vertex> m_vertexData;
    std::vector<uint32_t> m_indexData;
};

}

}