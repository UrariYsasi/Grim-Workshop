/*
    Vertex.hpp
    Peon Engine

    Declan Hopkins
    8/5/2016

    A vertex with a position in 3D space, as well as a color and a UV  coordinate. Vertices are 
    used to construct Meshes.
*/

#pragma once

namespace grim
{

struct Vertex
{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float a;
    float u;
    float v;

    Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v) :
        x(x),
        y(y),
        z(z),
        r(r),
        g(g),
        b(b),
        a(a),
        u(u),
        v(v)
    {
    }

    Vertex(float x, float y, float z, float r, float g, float b, float a) :
        Vertex(x, y, z, r, g, b, a, 0.0f, 0.0f)
    {
    }

    Vertex(float x, float y, float z) :
        Vertex(x, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f)
    {
    }
};

}
