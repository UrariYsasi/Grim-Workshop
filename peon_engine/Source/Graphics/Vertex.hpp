#pragma once

namespace grim
{

namespace graphics
{

/*
    A data structure that describes the attributes of a vertex in 3D space.
*/
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

    Vertex(const glm::vec3& position, const graphics::Color& color, const glm::vec2& textureCoordinate) :
        x(position.x),
        y(position.y),
        z(position.z),
        r(color.r),
        g(color.g),
        b(color.b),
        a(color.a),
        u(textureCoordinate.x),
        v(textureCoordinate.y)
    {
    }
};

}

}