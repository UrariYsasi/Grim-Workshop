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
    const static uint16_t SIZE = 9;

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

    Vertex(const glm::vec3& position, const graphics::Color& color) :
        x(position.x),
        y(position.y),
        z(position.z),
        r(color.r),
        g(color.g),
        b(color.b),
        a(color.a),
        u(0.0f),
        v(0.0f)
    {
    }

    Vertex(const glm::vec3& position) :
        x(position.x),
        y(position.y),
        z(position.z),
        r(1.0f),
        g(1.0f),
        b(1.0f),
        a(1.0f),
        u(0.0f),
        v(0.0f)
    {
    }
};

}

}