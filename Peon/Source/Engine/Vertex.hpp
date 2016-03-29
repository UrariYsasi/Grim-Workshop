#pragma once

namespace grim
{

/*
    A data structure that describes the attributes of a vertex in 3D space.
*/
struct Vertex
{
    double x;
    double y;
    double z;
    double r;
    double g;
    double b;
    double a;
    double u;
    double v;

    Vertex(const glm::vec3& position, const grim::Color& color, const glm::vec2& textureCoordinate) :
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