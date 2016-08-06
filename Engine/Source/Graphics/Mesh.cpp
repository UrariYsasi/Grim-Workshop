/*
    Mesh.cpp
    Peon Engine

    Declan Hopkins
    8/5/2016
*/

#include "PCH.hpp"
#include "Mesh.hpp"

namespace grim
{

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::AddVertex(const Vertex& vertex)
{
    m_vertices.push_back(vertex);
}

void Mesh::AddIndex(const uint32_t& index)
{
    m_indices.push_back(index);
}

const std::vector<Vertex>& Mesh::GetVertices() const
{
    return m_vertices;
}

const std::vector<uint32_t>& Mesh::GetIndices() const
{
    return m_indices;
}

}