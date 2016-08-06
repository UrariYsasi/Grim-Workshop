/*
    Mesh.cpp
    Peon Engine

    Declan Hopkins
    8/5/2016

    A collection of vertices that define the representation of a 3D object.
*/

#pragma once

namespace grim
{

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void AddVertex(const Vertex& vertex);
    void AddIndex(const uint32_t& index);

    const std::vector<Vertex>& GetVertices() const;
    const std::vector<uint32_t>& GetIndices() const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
};

}