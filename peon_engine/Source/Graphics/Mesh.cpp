#include "PCH.hpp"
#include "Mesh.hpp"

namespace grim
{

namespace graphics
{

Mesh::Mesh(const PrimitiveType& primitiveType) :
    m_primitiveType(primitiveType)
{
}

Mesh::~Mesh()
{
    m_vertexData.clear();
    m_indexData.clear();
}

void Mesh::AddVertex(const Vertex& vertex)
{
    m_vertexData.push_back(vertex);
}

void Mesh::AddIndex(const uint32_t& index)
{
    m_indexData.push_back(index);
}

void Mesh::ClearData()
{
    m_vertexData.clear();
    m_indexData.clear();
}

PrimitiveType Mesh::GetPrimitiveType() const
{
    return m_primitiveType;
}

std::vector<Vertex> Mesh::GetVertexData() const
{
    return m_vertexData;
}

std::vector<uint32_t> Mesh::GetIndexData() const
{
    return m_indexData;
}

uint32_t Mesh::GetVertexCount() const
{
    return m_vertexData.size();
}

uint32_t Mesh::GetIndexCount() const
{
    return m_indexData.size();
}

}

}